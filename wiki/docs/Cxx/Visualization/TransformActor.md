[VTKExamples](/index/)/[Cxx](/Cxx)/Visualization/TransformActor

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestTransformActor.png?raw=true" width="256" />

### Description
This examples demonstrates how to transform an actor. This is different than using vtkTransformPolyDataFilter in that it doesn't actually transform the data (you can't access the transformed coordinates) - it is all done on the video card.

**TransformActor.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkConeSource.h>
#include <vtkTransform.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create a cone
  vtkSmartPointer<vtkConeSource> coneSource1 = 
    vtkSmartPointer<vtkConeSource>::New();
  coneSource1->Update();
  
  vtkSmartPointer<vtkConeSource> coneSource2 = 
    vtkSmartPointer<vtkConeSource>::New();
  coneSource2->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> mapper1 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper1->SetInputConnection(coneSource1->GetOutputPort());
  vtkSmartPointer<vtkActor> actor1 = 
    vtkSmartPointer<vtkActor>::New();
  actor1->SetMapper(mapper1);
  
  // Create a second, transformed cone
  vtkSmartPointer<vtkPolyDataMapper> mapper2 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper2->SetInputConnection(coneSource2->GetOutputPort());
  vtkSmartPointer<vtkActor> actor2 = 
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(mapper2);
  
  vtkSmartPointer<vtkTransform> transform = 
    vtkSmartPointer<vtkTransform>::New();
  transform->PostMultiply(); //this is the key line
  transform->RotateZ(90.0);
  
  actor2->SetUserTransform(transform);
  
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
  renderer->AddActor(actor1);
  renderer->AddActor(actor2);
  renderer->SetBackground(1,1,1); // Background color white

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TransformActor)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TransformActor MACOSX_BUNDLE TransformActor.cxx)
 
target_link_libraries(TransformActor ${VTK_LIBRARIES})
```

**Download and Build TransformActor**

Click [here to download TransformActor](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TransformActor.tar) and its *CMakeLists.txt* file.
Once the *tarball TransformActor.tar* has been downloaded and extracted,
```
cd TransformActor/build 
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
./TransformActor
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

