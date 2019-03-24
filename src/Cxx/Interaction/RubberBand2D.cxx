#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleRubberBand2D.h>
#include <vtkObjectFactory.h>
 
class MyRubberBand : public vtkInteractorStyleRubberBand2D
{
public:
  static MyRubberBand* New();
  vtkTypeMacro(MyRubberBand, vtkInteractorStyleRubberBand2D);
 
  virtual void OnLeftButtonUp() override
  {
    // Forward events
    vtkInteractorStyleRubberBand2D::OnLeftButtonUp();
 
    std::cout << "Start position: " << this->StartPosition[0] << " " << this->StartPosition[1] << std::endl;
    std::cout << "End position: " << this->EndPosition[0] << " " << this->EndPosition[1] << std::endl;
  }
};

vtkStandardNewMacro(MyRubberBand);
 
int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
 
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
 
  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white
 
  // Render
  renderWindow->Render();
 
  vtkSmartPointer<MyRubberBand> style = 
    vtkSmartPointer<MyRubberBand>::New();
  renderWindowInteractor->SetInteractorStyle( style );

  // Begin mouse interaction
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
