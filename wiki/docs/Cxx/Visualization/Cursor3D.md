[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/Cursor3D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestCursor3D.png?raw=true" width="256" />

**Cursor3D.cxx**
```c++
#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCursor3D.h>
 
int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  // Create a renderer, render window, and interactor
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
  renderer->SetBackground(1,1,1); // Background color white
 
  vtkSmartPointer<vtkCursor3D> cursor = 
    vtkSmartPointer<vtkCursor3D>::New();
  cursor->SetModelBounds(-10,10,-10,10,-10,10);
  cursor->AllOn();
  cursor->OutlineOff();
  cursor->Update();

  vtkSmartPointer<vtkPolyDataMapper> cursorMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cursorMapper->SetInputConnection(cursor->GetOutputPort());
  vtkSmartPointer<vtkActor> cursorActor = 
    vtkSmartPointer<vtkActor>::New();
  cursorActor->GetProperty()->SetColor(1,0,0);
  cursorActor->SetMapper(cursorMapper);
  renderer->AddActor(cursorActor);
  
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Cursor3D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Cursor3D MACOSX_BUNDLE Cursor3D.cxx)
 
target_link_libraries(Cursor3D ${VTK_LIBRARIES})
```

**Download and Build Cursor3D**

Click [here to download Cursor3D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Cursor3D.tar) and its *CMakeLists.txt* file.
Once the *tarball Cursor3D.tar* has been downloaded and extracted,
```
cd Cursor3D/build 
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
./Cursor3D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

