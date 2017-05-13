[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/TransformActorCollection

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestTransformActorCollection.png?raw=true" width="256" />

**TransformActorCollection.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkConeSource.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkTransform.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActorCollection.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  // Create a cone
  vtkSmartPointer<vtkConeSource> coneSource =
    vtkSmartPointer<vtkConeSource>::New();
  coneSource->SetHeight(3);

  vtkSmartPointer<vtkPolyDataMapper> coneMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection(coneSource->GetOutputPort());
  vtkSmartPointer<vtkActor> coneActor =
    vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMapper);

  // Create a cube
  vtkSmartPointer<vtkCubeSource> cubeSource =
    vtkSmartPointer<vtkCubeSource>::New();

  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
  vtkSmartPointer<vtkActor> cubeActor =
    vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);

  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();

  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  renderer->AddActor(sphereActor);

  vtkSmartPointer<vtkActorCollection> actorCollection =
    vtkSmartPointer<vtkActorCollection>::New();
  actorCollection->AddItem(cubeActor);
  actorCollection->AddItem(coneActor);
  actorCollection->InitTraversal();

  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->PostMultiply(); //this is the key line
  transform->Translate(5.0, 0, 0);

  //actorCollection->SetUserTransform(transform);

  for(vtkIdType i = 0; i < actorCollection->GetNumberOfItems(); i++)
  {
    vtkActor* actor = actorCollection->GetNextActor();
    actor->SetUserTransform(transform);
    renderer->AddActor(actor);
  }

  // Create a renderer, render window, and interactor

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->SetBackground(.2, .3, .4);

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TransformActorCollection)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TransformActorCollection MACOSX_BUNDLE TransformActorCollection.cxx)
 
target_link_libraries(TransformActorCollection ${VTK_LIBRARIES})
```

**Download and Build TransformActorCollection**

Click [here to download TransformActorCollection](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TransformActorCollection.tar) and its *CMakeLists.txt* file.
Once the *tarball TransformActorCollection.tar* has been downloaded and extracted,
```
cd TransformActorCollection/build 
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
./TransformActorCollection
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

