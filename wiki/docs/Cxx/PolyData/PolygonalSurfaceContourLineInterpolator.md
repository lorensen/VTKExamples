[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/PolygonalSurfaceContourLineInterpolator

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestPolygonalSurfaceContourLineInterpolator.png?raw=true" width="256" />

**PolygonalSurfaceContourLineInterpolator.cxx**
```c++
#include <vtkVersion.h>
#include "vtkSmartPointer.h"

#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkCellArray.h"
#include "vtkImageDataGeometryFilter.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataCollection.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSphereSource.h"
#include "vtkTriangleFilter.h"
#include "vtkXMLPolyDataReader.h"

#include "vtkContourWidget.h"
#include "vtkOrientedGlyphContourRepresentation.h"
#include "vtkPolygonalSurfacePointPlacer.h"
#include "vtkPolygonalSurfaceContourLineInterpolator.h"


int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData;
  if (argc < 2)
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(40);
    sphereSource->SetPhiResolution(20);
    sphereSource->Update();

    polyData = sphereSource->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    polyData = reader->GetOutput();
  }

  // The Dijkistra interpolator will not accept cells that aren't triangles
  vtkSmartPointer<vtkTriangleFilter> triangleFilter =
    vtkSmartPointer<vtkTriangleFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  triangleFilter->SetInput( polyData );
#else
  triangleFilter->SetInputData( polyData );
#endif
  triangleFilter->Update();

  vtkSmartPointer<vtkPolyData> pd = triangleFilter->GetOutput();

  //Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(triangleFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetInterpolationToFlat();

  // Create the render window, renderer and interactor.

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Add the actors to the renderer, set the background and size

  renderer->AddActor(actor);
  renderer->SetBackground (.3, .4, .5);

  // Here comes the contour widget stuff...

  vtkSmartPointer<vtkContourWidget> contourWidget =
    vtkSmartPointer<vtkContourWidget>::New();
  contourWidget->SetInteractor(interactor);
  vtkSmartPointer<vtkOrientedGlyphContourRepresentation> rep =
    vtkOrientedGlyphContourRepresentation::SafeDownCast(
      contourWidget->GetRepresentation());
  rep->GetLinesProperty()->SetColor(1, 0.2, 0);
  rep->GetLinesProperty()->SetLineWidth(3.0);

  vtkSmartPointer<vtkPolygonalSurfacePointPlacer> pointPlacer =
    vtkSmartPointer<vtkPolygonalSurfacePointPlacer>::New();
  pointPlacer->AddProp(actor);
  pointPlacer->GetPolys()->AddItem( pd );
  rep->SetPointPlacer(pointPlacer);

  vtkSmartPointer<vtkPolygonalSurfaceContourLineInterpolator> interpolator =
    vtkSmartPointer<vtkPolygonalSurfaceContourLineInterpolator>::New();
  interpolator->GetPolys()->AddItem( pd );
  rep->SetLineInterpolator(interpolator);

  renderWindow->Render();
  interactor->Initialize();

  contourWidget->EnabledOn();

  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PolygonalSurfaceContourLineInterpolator)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PolygonalSurfaceContourLineInterpolator MACOSX_BUNDLE PolygonalSurfaceContourLineInterpolator.cxx)
 
target_link_libraries(PolygonalSurfaceContourLineInterpolator ${VTK_LIBRARIES})
```

**Download and Build PolygonalSurfaceContourLineInterpolator**

Click [here to download PolygonalSurfaceContourLineInterpolator](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PolygonalSurfaceContourLineInterpolator.tar) and its *CMakeLists.txt* file.
Once the *tarball PolygonalSurfaceContourLineInterpolator.tar* has been downloaded and extracted,
```
cd PolygonalSurfaceContourLineInterpolator/build 
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
./PolygonalSurfaceContourLineInterpolator
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

