[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/DetermineActorType

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Utilities/TestDetermineActorType.png?raw=true" width="256" />

**DetermineActorType.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkActorCollection.h>
#include <vtkCubeAxesActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

int main(int, char *[])
{
  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Cube axes
  vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor =
    vtkSmartPointer<vtkCubeAxesActor>::New();

  // Create a renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  cubeAxesActor->SetCamera(renderer->GetActiveCamera());

  renderer->AddActor(actor);
  renderer->AddActor(cubeAxesActor);

  // Determine the types of the actors - method 1
  {
  std::cout << "Method 1:" << std::endl;
  vtkActorCollection* actorCollection = renderer->GetActors();
  actorCollection->InitTraversal();

  for(vtkIdType i = 0; i < actorCollection->GetNumberOfItems(); i++)
  {
    vtkActor* nextActor = actorCollection->GetNextActor();
    std::cout << "nextActor " << i << " : " << nextActor->GetClassName() << std::endl;
    std::string className = nextActor->GetClassName();
    std::string wantedClass = "vtkCubeAxesActor";
    if(className == wantedClass)
    {
      std::cout << "nextActor " << i << " is a vtkCubeAxesActor!" << std::endl;
    }
    else
    {
      std::cout << "nextActor " << i << " is NOT a vtkCubeAxesActor!" << std::endl;
    }
  }
  }

  // Determine the types of the actors - method 2
  {
  std::cout << "Method 2:" << std::endl;
  vtkActorCollection* actorCollection = renderer->GetActors();
  actorCollection->InitTraversal();

  for(vtkIdType i = 0; i < actorCollection->GetNumberOfItems(); i++)
  {
    vtkActor* nextActor = actorCollection->GetNextActor();
    std::cout << "nextActor " << i << " : " << nextActor->GetClassName() << std::endl;
    if(nextActor->IsA("vtkCubeAxesActor"))
    {
      std::cout << "nextActor " << i << " is a vtkCubeAxesActor!" << std::endl;
    }
    else
    {
      std::cout << "nextActor " << i << " is NOT a vtkCubeAxesActor!" << std::endl;
    }
  }
  }

  // Determine the types of the actors - method 3
  {
  std::cout << "Method 3:" << std::endl;
  vtkActorCollection* actorCollection = renderer->GetActors();
  actorCollection->InitTraversal();

  for(vtkIdType i = 0; i < actorCollection->GetNumberOfItems(); i++)
  {
    vtkActor* nextActor = actorCollection->GetNextActor();
    std::cout << "nextActor " << i << " : " << nextActor->GetClassName() << std::endl;

    if(vtkCubeAxesActor::SafeDownCast(nextActor) != 0)
    {
      std::cout << "nextActor " << i << " is a vtkCubeAxesActor!" << std::endl;
    }
    else
    {
      std::cout << "nextActor " << i << " is NOT a vtkCubeAxesActor!" << std::endl;
    }
  }
  }

  // Determine the types of the actors - method 4
  {
  std::cout << "Method 4:" << std::endl;
  vtkActorCollection* actorCollection = renderer->GetActors();
  actorCollection->InitTraversal();

  for(vtkIdType i = 0; i < actorCollection->GetNumberOfItems(); i++)
  {
    vtkActor* nextActor = actorCollection->GetNextActor();
    std::cout << "nextActor " << i << " : " << nextActor->GetClassName() << std::endl;

    if(dynamic_cast<vtkCubeAxesActor*>(nextActor) != 0)
    {
      std::cout << "nextActor " << i << " is a vtkCubeAxesActor!" << std::endl;
    }
    else
    {
      std::cout << "nextActor " << i << " is NOT a vtkCubeAxesActor!" << std::endl;
    }
  }
  }

  // Render the scene
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->ResetCamera();
  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DetermineActorType)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DetermineActorType MACOSX_BUNDLE DetermineActorType.cxx)
 
target_link_libraries(DetermineActorType ${VTK_LIBRARIES})
```

**Download and Build DetermineActorType**

Click [here to download DetermineActorType](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DetermineActorType.tar) and its *CMakeLists.txt* file.
Once the *tarball DetermineActorType.tar* has been downloaded and extracted,
```
cd DetermineActorType/build 
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
./DetermineActorType
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

