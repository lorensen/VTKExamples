#include <vtkSmartPointer.h>
#include <vtkCallbackCommand.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleUser.h>

static void ClickCallbackFunction ( vtkObject* caller,
                                    long unsigned int eventId,
                                    void* clientData,
                                    void* callData );

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();

  vtkSmartPointer<vtkCallbackCommand> clickCallback = 
    vtkSmartPointer<vtkCallbackCommand>::New();
  clickCallback->SetCallback(ClickCallbackFunction);

  renderWindowInteractor->AddObserver ( vtkCommand::LeftButtonPressEvent, clickCallback );
  
  vtkSmartPointer<vtkInteractorStyleUser> style = 
    vtkSmartPointer<vtkInteractorStyleUser>::New();
  renderWindowInteractor->SetInteractorStyle(style);
  
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}


void ClickCallbackFunction (vtkObject *,
                            long unsigned int,
                            void *,
                            void *)
{
  std::cout << "Click callback" << std::endl;

  // We can get the calling object like this:
  // vtkRenderWindowInteractor *iren = 
  //  static_cast<vtkRenderWindowInteractor*>(caller);
}
