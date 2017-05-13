[VTKExamples](/home/)/[Cxx](/Cxx)/GeometricObjects/Cylinder

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestCylinder.png?raw=true" width="256" />

### Description
This example displays a cylinder on the screen.

**Cylinder.cxx**
```c++
#include <vtkCylinderSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
 
int main(int, char *argv[])
{
  // Create a sphere
  vtkSmartPointer<vtkCylinderSource> cylinderSource =
    vtkSmartPointer<vtkCylinderSource>::New();
  cylinderSource->SetCenter(0.0, 0.0, 0.0);
  cylinderSource->SetRadius(5.0);
  cylinderSource->SetHeight(7.0);
  cylinderSource->SetResolution(100);
 
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cylinderSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.1, .3,.2); // Background color dark green
 
  // Render and interact
  renderWindow->SetWindowName(argv[0]);
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Cylinder)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Cylinder MACOSX_BUNDLE Cylinder.cxx)
 
target_link_libraries(Cylinder ${VTK_LIBRARIES})
```

**Download and Build Cylinder**

Click [here to download Cylinder](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Cylinder.tar) and its *CMakeLists.txt* file.
Once the *tarball Cylinder.tar* has been downloaded and extracted,
```
cd Cylinder/build 
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
./Cylinder
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

