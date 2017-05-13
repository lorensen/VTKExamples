[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/ImplicitPolyDataDistance

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestImplicitPolyDataDistance.png?raw=true" width="256" />

### Description
NOTE: This example requires version 5.9.20111206 or higher. 

**ImplicitPolyDataDistance.cxx**
```c++
#include <vtkVersion.h>
#include <vtkImplicitPolyDataDistance.h>

#include <vtkActor.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkVertexGlyphFilter.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(1.0f);
  sphereSource->Update();
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection( sphereSource->GetOutputPort() );
  sphereMapper->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper( sphereMapper );
  sphereActor->GetProperty()->SetOpacity(.3);
  sphereActor->GetProperty()->SetColor(1,0,0);

  vtkSmartPointer<vtkImplicitPolyDataDistance> implicitPolyDataDistance =
    vtkSmartPointer<vtkImplicitPolyDataDistance>::New();
  implicitPolyDataDistance->SetInput(sphereSource->GetOutput());

  // Setup a grid
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  float step = 0.1;
  for(float x = - 2.0; x <= 2.0; x += step)
  {
    for(float y = - 2.0; y <= 2.0; y += step)
    {
      for(float z = - 2.0; z <= 2.0; z += step)
      {
        points->InsertNextPoint(x,y,z);
      }
    }
  }

  // Add distances to each point
  vtkSmartPointer<vtkFloatArray> signedDistances =
    vtkSmartPointer<vtkFloatArray>::New();
  signedDistances->SetNumberOfComponents(1);
  signedDistances->SetName("SignedDistances");

  // Evaluate the signed distance function at all of the grid points
  for(vtkIdType pointId = 0; pointId < points->GetNumberOfPoints(); ++pointId)
  {
    double p[3];
    points->GetPoint(pointId, p);
    float signedDistance = implicitPolyDataDistance->EvaluateFunction(p);
    signedDistances->InsertNextValue(signedDistance);
  }

  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();
  polyData->SetPoints(points);
  polyData->GetPointData()->SetScalars(signedDistances);

  vtkSmartPointer<vtkVertexGlyphFilter> vertexGlyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  vertexGlyphFilter->SetInputConnection(polyData->GetProducerPort());
#else
  vertexGlyphFilter->SetInputData(polyData);
#endif
  vertexGlyphFilter->Update();

  vtkSmartPointer<vtkPolyDataMapper> signedDistanceMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  signedDistanceMapper->SetInputConnection(vertexGlyphFilter->GetOutputPort());
  signedDistanceMapper->ScalarVisibilityOn();

  vtkSmartPointer<vtkActor> signedDistanceActor =
    vtkSmartPointer<vtkActor>::New();
  signedDistanceActor->SetMapper( signedDistanceMapper );

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddViewProp(sphereActor);
  renderer->AddViewProp(signedDistanceActor);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> renWinInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renWinInteractor->SetRenderWindow( renderWindow );

  renderWindow->Render();
  renWinInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImplicitPolyDataDistance)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImplicitPolyDataDistance MACOSX_BUNDLE ImplicitPolyDataDistance.cxx)
 
target_link_libraries(ImplicitPolyDataDistance ${VTK_LIBRARIES})
```

**Download and Build ImplicitPolyDataDistance**

Click [here to download ImplicitPolyDataDistance](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImplicitPolyDataDistance.tar) and its *CMakeLists.txt* file.
Once the *tarball ImplicitPolyDataDistance.tar* has been downloaded and extracted,
```
cd ImplicitPolyDataDistance/build 
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
./ImplicitPolyDataDistance
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

