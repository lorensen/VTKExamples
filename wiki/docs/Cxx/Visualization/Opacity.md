[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/Opacity

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestOpacity.png?raw=true" width="256" />

**Opacity.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{ 
  // Cube
  vtkSmartPointer<vtkCubeSource> cubeSource = 
    vtkSmartPointer<vtkCubeSource>::New();
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> cubeActor = 
    vtkSmartPointer<vtkActor>::New();
  cubeActor->GetProperty()->SetOpacity(0.5);
  cubeActor->SetMapper(cubeMapper);
  
  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> sphereActor = 
    vtkSmartPointer<vtkActor>::New();
  sphereActor->GetProperty()->SetColor(0.5,1,0.5);
  sphereActor->GetProperty()->SetOpacity(0.5);
  sphereActor->SetMapper(sphereMapper);
  
  // Create renderers and add actors of plane and cube
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(cubeActor);
  renderer->AddActor(sphereActor);
  
  // Add renderer to renderwindow and render
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  renderer->SetBackground(0,0,0);
  renderWindow->Render();

  interactor->Start();
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Opacity)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Opacity MACOSX_BUNDLE Opacity.cxx)
 
target_link_libraries(Opacity ${VTK_LIBRARIES})
```

**Download and Build Opacity**

Click [here to download Opacity](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Opacity.tar) and its *CMakeLists.txt* file.
Once the *tarball Opacity.tar* has been downloaded and extracted,
```
cd Opacity/build 
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
./Opacity
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

