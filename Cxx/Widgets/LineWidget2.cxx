#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkLineWidget2.h>
#include <vtkLineRepresentation.h>
#include <vtkCommand.h>

// This does the actual work.
// Callback for the interaction
class vtkLineCallback : public vtkCommand
{
  public:
    static vtkLineCallback *New()
    {
      return new vtkLineCallback;
    }
    
    virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      
      vtkLineWidget2 *lineWidget = 
          reinterpret_cast<vtkLineWidget2*>(caller);
      
      // Get the actual box coordinates of the line
      vtkSmartPointer<vtkPolyData> polydata = 
          vtkSmartPointer<vtkPolyData>::New();
      static_cast<vtkLineRepresentation*>(lineWidget->GetRepresentation())->GetPolyData (polydata);
      
      // Display one of the points, just so we know it's working
      double p[3];
      polydata->GetPoint(0,p);
      std::cout << "P: " << p[0] << " " << p[1] << " " << p[2] << std::endl;
    }
    vtkLineCallback(){}
    
};
 
 
int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  //renderer->AddActor(actor);
  
  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkLineWidget2> lineWidget = 
    vtkSmartPointer<vtkLineWidget2>::New();
  lineWidget->SetInteractor(renderWindowInteractor);
  lineWidget->CreateDefaultRepresentation();
  
  // You could do this if you want to set properties at this point:
  //vtkSmartPointer<vtkLineRepresentation> lineRepresentation = 
    //vtkSmartPointer<vtkLineRepresentation>::New();
  //lineWidget->SetRepresentation(lineRepresentation);
    
  vtkSmartPointer<vtkLineCallback> lineCallback = 
    vtkSmartPointer<vtkLineCallback>::New();
   
  lineWidget->AddObserver(vtkCommand::InteractionEvent,lineCallback);
  
  // Render
  renderWindow->Render();
  
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  lineWidget->On();
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
