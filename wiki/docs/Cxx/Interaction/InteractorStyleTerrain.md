[VTKExamples](/home/)/[Cxx](/Cxx)/Interaction/InteractorStyleTerrain

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Interaction/TestInteractorStyleTerrain.png?raw=true" width="256" />

**InteractorStyleTerrain.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTerrain.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  // Create an actor
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  // Render
  renderWindow->Render();

  vtkSmartPointer<vtkInteractorStyleTerrain> style = 
    vtkSmartPointer<vtkInteractorStyleTerrain>::New();
  
  renderWindowInteractor->SetInteractorStyle( style );
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(InteractorStyleTerrain)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(InteractorStyleTerrain MACOSX_BUNDLE InteractorStyleTerrain.cxx)
 
target_link_libraries(InteractorStyleTerrain ${VTK_LIBRARIES})
```

**Download and Build InteractorStyleTerrain**

Click [here to download InteractorStyleTerrain](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/InteractorStyleTerrain.tar) and its *CMakeLists.txt* file.
Once the *tarball InteractorStyleTerrain.tar* has been downloaded and extracted,
```
cd InteractorStyleTerrain/build 
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
./InteractorStyleTerrain
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

