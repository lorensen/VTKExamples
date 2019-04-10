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
