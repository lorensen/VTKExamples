[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/ContoursToSurface

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestContoursToSurface.png?raw=true" width="256" />

### Description
This example creates a stack of 21 circles and creates a closed surface from them.

**ContoursToSurface.cxx**
```c++
#include <vtkVersion.h>
#include <vtkActor.h>
#include <vtkAppendPolyData.h>
#include <vtkCellArray.h>
#include <vtkMath.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkVoxelContoursToSurfaceFilter.h>

void CreateCircle(const double& z, const double& radius, const int& resolution, vtkPolyData* polyData);

int main(int, char *[])
{
  // Create the data: a series of discs representing the intersections of x-y planes through a unit sphere
  // centered at 0, 0, 0
  //
  int numDivisions = 20;
  int resolution = 100;
  double lastz = 0.;
  double z = 0.;
  double radius = 0.;
  double sphereRadius = 1.;
  double zmin = -0.9*sphereRadius;
  double zmax = 0.9*sphereRadius;

  // Append all the discs into one polydata
  //
  vtkSmartPointer<vtkAppendPolyData> appendFilter = vtkSmartPointer<vtkAppendPolyData>::New();

  for( int i = 0; i <= numDivisions; ++i )
  {
    lastz = z;
    double u = i / double(numDivisions);
    z = ( 1. - u )*zmin + u*zmax;
    radius = sqrt( sphereRadius*sphereRadius - z*z );
    vtkSmartPointer<vtkPolyData> circle = vtkSmartPointer<vtkPolyData>::New();
    CreateCircle( z, radius, resolution, circle );
#if VTK_MAJOR_VERSION <= 5
    appendFilter->AddInput( circle );
#else
    appendFilter->AddInputData( circle );
#endif
  }

  double deltaz = z - lastz;

  if( !appendFilter->GetNumberOfInputConnections(0) )
  {
    cerr << "error, no contours!" << endl;
    return EXIT_FAILURE;
  }

  appendFilter->Update();

  // Convert to ijk coordinates for the contour to surface filter
  //
  double bounds[6];
  vtkPolyData* contours = appendFilter->GetOutput();
  contours->GetBounds( bounds );
  double origin[3]  = { bounds[0], bounds[2], bounds[4] };
  double spacing[3] = { (bounds[1] - bounds[0]) / 40,
                        (bounds[3] - bounds[2]) / 40,
                         deltaz };

  vtkSmartPointer<vtkPolyData> poly = vtkSmartPointer<vtkPolyData>::New();
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  vtkPoints* contourPoints = contours->GetPoints();
  int numPoints = contourPoints->GetNumberOfPoints();
  points->SetNumberOfPoints( numPoints );
  for( int i = 0; i < numPoints; ++i )
  {
    double pt[3];
    contourPoints->GetPoint( i, pt );
    pt[0] = static_cast<int>( (pt[0] - origin[0]) / spacing[0] + 0.5 );
    pt[1] = static_cast<int>( (pt[1] - origin[1]) / spacing[1] + 0.5 );
    pt[2] = static_cast<int>( (pt[2] - origin[2]) / spacing[2] + 0.5 );
    points->SetPoint( i, pt );
  }
  poly->SetPolys( contours->GetPolys() );
  poly->SetPoints( points );

  // Create the contour to surface filter
  //
  vtkSmartPointer<vtkVoxelContoursToSurfaceFilter> contoursToSurface = vtkSmartPointer<vtkVoxelContoursToSurfaceFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  contoursToSurface->SetInput( poly );
#else
  contoursToSurface->SetInputData( poly );
#endif
  contoursToSurface->SetSpacing( spacing[0], spacing[1], spacing[2] );
  contoursToSurface->Update();

  // Rescale the output back into world coordinates and center it
  //
  double scaleCenter[3];
  contoursToSurface->GetOutput()->GetCenter( scaleCenter );
  double scaleBounds[6];
  contoursToSurface->GetOutput()->GetBounds( scaleBounds );
  double center[3];
  contours->GetCenter( center );

  vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformFilter->SetInputConnection( contoursToSurface->GetOutputPort() );
  vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
  transformFilter->SetTransform( transform );
  transform->Translate( -scaleCenter[0], -scaleCenter[1], -scaleCenter[2] );
  transform->Scale(
    (bounds[1] - bounds[0])/(scaleBounds[1] - scaleBounds[0]),
    (bounds[3] - bounds[2])/(scaleBounds[3] - scaleBounds[2]),
    (bounds[5] - bounds[4])/(scaleBounds[5] - scaleBounds[4]) );
  transform->Translate( center[0], center[1], center[2] );

  // Visualize the contours
  //
  vtkSmartPointer<vtkPolyDataMapper> contoursMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  contoursMapper->SetInput( contours );
#else
  contoursMapper->SetInputData( contours );
#endif
  contoursMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> contoursActor = vtkSmartPointer<vtkActor>::New();
  contoursActor->SetMapper( contoursMapper );
  contoursActor->GetProperty()->SetRepresentationToWireframe();
  contoursActor->GetProperty()->ShadingOff();

  // Visualize the surface
  //
  vtkSmartPointer<vtkPolyDataMapper> surfaceMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  surfaceMapper->SetInputConnection( transformFilter->GetOutputPort() );
  surfaceMapper->ScalarVisibilityOff();
  surfaceMapper->ImmediateModeRenderingOn();

  vtkSmartPointer<vtkActor> surfaceActor = vtkSmartPointer<vtkActor>::New();
  surfaceActor->SetMapper( surfaceMapper );
  surfaceActor->GetProperty()->SetRepresentationToWireframe();
  surfaceActor->GetProperty()->ShadingOff();

  // Create two renderers side by side to show the contours and the surface separately
  //
  // Press 't' for trackball interaction
  // Press 'r' to reset the camera
  // Press 'w' for wireframe representation
  // Press 's' for surface representation
  //
  vtkSmartPointer<vtkRenderer> renderer1 = vtkSmartPointer<vtkRenderer>::New();
  renderer1->SetViewport( 0., 0., 0.5, 1. );
  renderer1->SetBackground( 0.2, 0.2, 0.8 );

  vtkSmartPointer<vtkRenderer> renderer2 = vtkSmartPointer<vtkRenderer>::New();
  renderer2->SetViewport( 0.5, 0., 1., 1. );
  renderer2->SetBackground( 0.8, 0.2, 0.2 );

  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize( 800, 400 );

  renderWindow->AddRenderer( renderer1 );
  renderWindow->AddRenderer( renderer2 );

  vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow( renderWindow );

  renderer1->AddViewProp( surfaceActor );
  renderer2->AddViewProp( contoursActor );
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}

void CreateCircle( const double& z, const double& radius, const int& resolution, vtkPolyData* polyData )
{
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();

  points->SetNumberOfPoints( resolution );
  cells->Allocate( 1, resolution );
  cells->InsertNextCell( resolution );

  for( int i = 0 ; i < resolution; ++i )
  {
    double theta = vtkMath::RadiansFromDegrees(360.*i/double(resolution));
    double x = radius*cos(theta);
    double y = radius*sin(theta);
    points->SetPoint( i, x, y, z );
    cells->InsertCellPoint( i );
  }

  polyData->Initialize();
  polyData->SetPolys( cells );
  polyData->SetPoints( points );
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ContoursToSurface)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ContoursToSurface MACOSX_BUNDLE ContoursToSurface.cxx)
 
target_link_libraries(ContoursToSurface ${VTK_LIBRARIES})
```

**Download and Build ContoursToSurface**

Click [here to download ContoursToSurface](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ContoursToSurface.tar) and its *CMakeLists.txt* file.
Once the *tarball ContoursToSurface.tar* has been downloaded and extracted,
```
cd ContoursToSurface/build 
```
If VTK is installed:
```
cmake ..
```
If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build:
```
cmake -DVTK_DIR:PATH=/home/me/vtk_build ..
```
Build the project:
```
make
```
and run it:
```
./ContoursToSurface
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

