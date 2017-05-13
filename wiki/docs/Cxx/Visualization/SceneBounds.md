[VTKExamples](/index/)/[Cxx](/Cxx)/Visualization/SceneBounds

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestSceneBounds.png?raw=true" width="256" />

**SceneBounds.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkCubeSource.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkAssembly.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>
#include <vtkPropAssembly.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);

  // Create a cube
  vtkSmartPointer<vtkCubeSource> cubeSource =
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->SetCenter(5.0, 0.0, 0.0);
  cubeSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
  vtkSmartPointer<vtkActor> cubeActor =
    vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);

  // Visualization
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(sphereActor);
  renderer->AddActor(cubeActor);
  renderer->SetBackground(.3, .4, .5);

  renderer->ResetCamera();
  double bounds[6];
  renderer->ComputeVisiblePropBounds(bounds);
  std::cout << bounds[0] << " "
            << bounds[1] << " "
            << bounds[2] << " "
            << bounds[3] << " "
            << bounds[4] << " "
            << bounds[5] << std::endl;
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SceneBounds)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SceneBounds MACOSX_BUNDLE SceneBounds.cxx)
 
target_link_libraries(SceneBounds ${VTK_LIBRARIES})
```

**Download and Build SceneBounds**

Click [here to download SceneBounds](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SceneBounds.tar) and its *CMakeLists.txt* file.
Once the *tarball SceneBounds.tar* has been downloaded and extracted,
```
cd SceneBounds/build 
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
./SceneBounds
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

