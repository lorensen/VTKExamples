#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkAxesActor.h>
#include <vtkNamedColors.h>

class vtkTimerCallback2 : public vtkCommand
{
public:
 static vtkTimerCallback2 *New()
 {
  vtkTimerCallback2 *cb = new vtkTimerCallback2;
  return cb;
 }
 
 virtual void Execute(vtkObject *caller, unsigned long eventId, void * vtkNotUsed(callData))
 {
  actor->RotateZ(5);
  vtkRenderWindowInteractor *iren = dynamic_cast<vtkRenderWindowInteractor*>(caller);
  iren->GetRenderWindow()->Render();
 }
private:
 int TimerCount;
public:
 vtkActor* actor;
};

int main(int, char*[])
{
 vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
 
 // Create a sphere
 vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
 sphereSource->SetCenter(0.0, 0.0, 0.0);
 sphereSource->SetRadius(1.0);
 sphereSource->SetThetaResolution(15);
 sphereSource->SetPhiResolution(15);
 sphereSource->Update();
 
 // Create a mapper and actor
 vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
 mapper->SetInputConnection(sphereSource->GetOutputPort());
 vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
 actor->SetMapper(mapper);
 actor->RotateX(90);
 actor->GetProperty()->SetRepresentationToWireframe();
 
 // Create a renderer, render window, and interactor
 vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
 vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
 renderWindow->AddRenderer(renderer);
 
 vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
 renderWindowInteractor->SetRenderWindow(renderWindow);
 
 // Add the actor to the scene
 renderer->AddActor(actor);
 
 renderer->SetBackground(colors->GetColor3d("Seashell").GetData()); // Background color white
 // Render and interact
 renderWindow->Render();
 
 // Initialize must be called prior to creating timer events.
 renderWindowInteractor->Initialize();
 
 // Sign up to receive TimerEvent
 vtkSmartPointer<vtkTimerCallback2> cb = vtkSmartPointer<vtkTimerCallback2>::New();
 cb->actor = actor;
 renderWindowInteractor->AddObserver(vtkCommand::TimerEvent, cb);
 
 int timerId = renderWindowInteractor->CreateRepeatingTimer(100);
 
 // Start the interaction and timer
 renderWindowInteractor->Start();
 
 return EXIT_SUCCESS;
}
