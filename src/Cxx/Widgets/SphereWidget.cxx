#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkSphereWidget.h>
#include <vtkSphereRepresentation.h>
#include <vtkCommand.h>

class SphereCallback : public vtkCommand
{
  public:
    static SphereCallback *New()
    {
      return new SphereCallback;
    }
    SphereCallback(){}
    
    virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      
      vtkSphereWidget *sphereWidget = 
          reinterpret_cast<vtkSphereWidget*>(caller);
      
      double center[3];
      sphereWidget->GetCenter(center);
      std::cout << "Center: " << center[0] << " " << center[1] << " " << center[2] << std::endl;
    }
    
};

int main(int, char *[])
{
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

  vtkSmartPointer<vtkSphereWidget> sphereWidget = 
    vtkSmartPointer<vtkSphereWidget>::New();
  sphereWidget->SetInteractor(renderWindowInteractor);
  sphereWidget->SetRepresentationToSurface();
  
  vtkSmartPointer<SphereCallback> sphereCallback = 
    vtkSmartPointer<SphereCallback>::New();
 
  sphereWidget->AddObserver(vtkCommand::InteractionEvent,sphereCallback);
  
  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  sphereWidget->On();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
