#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkCommand.h>
#include <vtkActor.h>
#include <vtkCallbackCommand.h>
#include <vtkSmartPointer.h>
#include <vtkPointPicker.h>
#include <vtkCamera.h>
//#include <vtkInteractorObserver.h>

void ClickCallbackFunction ( vtkObject* caller, long unsigned int eventId, void* clientData, void* callData );

int main(int, char *[])
{
  
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(1,1,1); // Background color white
  renderer->AddActor(actor);
  
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow ( renderWindow );
 
  vtkSmartPointer<vtkCallbackCommand> clickCallback = 
    vtkSmartPointer<vtkCallbackCommand>::New();
  clickCallback->SetCallback ( ClickCallbackFunction );

  renderWindowInteractor->AddObserver ( vtkCommand::LeftButtonPressEvent, clickCallback );
  
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}

void ClickCallbackFunction ( vtkObject* vtkNotUsed(caller), long unsigned int vtkNotUsed(eventId), void* vtkNotUsed(clientData), void* vtkNotUsed(callData) )
{
  std::cout << "Click callback" << std::endl;
  // Get the interactor like this:
  // vtkRenderWindowInteractor *iren = 
  //  static_cast<vtkRenderWindowInteractor*>(caller);

}
