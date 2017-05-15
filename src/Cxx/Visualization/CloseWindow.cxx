#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkCubeSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

void KeypressCallbackFunction (
  vtkObject* caller,
  long unsigned int eventId,
  void* clientData,
  void* callData );

int main(int, char *[])
{
  vtkSmartPointer<vtkCubeSource> cubeSource = 
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();
  
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cubeSource->GetOutputPort());
 
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
 
  vtkSmartPointer<vtkCallbackCommand> keypressCallback = 
    vtkSmartPointer<vtkCallbackCommand>::New();
  keypressCallback->SetCallback ( KeypressCallbackFunction );
  renderWindowInteractor->AddObserver (
    vtkCommand::KeyPressEvent,
    keypressCallback );
  
  // Add the actor to the scene
  renderer->AddActor(actor);
  
  // Render and interact
  renderWindow->Render();
  renderWindow->SetWindowName("First Window");
  renderWindowInteractor->Start();
  
  std::cout << "Window 1 closed..." << std::endl;
  
  // Make another interactor, but use the same render window
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor2 = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor2->AddObserver (
    vtkCommand::KeyPressEvent, keypressCallback );

  renderWindowInteractor2->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindow->SetWindowName("Second Window");

  renderWindowInteractor2->Start();
  std::cout << "Window 2 closed. Exiting..." << std::endl;

  return EXIT_SUCCESS;
}

void KeypressCallbackFunction (
  vtkObject* caller,
  long unsigned int vtkNotUsed(eventId),
  void* vtkNotUsed(clientData),
  void* vtkNotUsed(callData) )
{
  
  vtkRenderWindowInteractor *iren = 
    static_cast<vtkRenderWindowInteractor*>(caller);
  // Close the window
  iren->GetRenderWindow()->Finalize();

  // Stop the interactor
  iren->TerminateApp();
  std::cout << "Closing window..." << std::endl;
}
