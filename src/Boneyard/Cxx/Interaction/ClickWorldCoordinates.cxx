#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkPointPicker.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
#include <vtkCoordinate.h>
#include <vtkRendererCollection.h>

// Define interaction style
class MouseInteractorStyle3 : public vtkInteractorStyleTrackballCamera
{
  public:
    static MouseInteractorStyle3* New();

    virtual void OnLeftButtonDown() 
    {
      std::cout << "Pressed left mouse button." << std::endl;
      int x = this->Interactor->GetEventPosition()[0];
      int y = this->Interactor->GetEventPosition()[1];
      std::cout << "(x,y) = (" << x << "," << y << ")" << std::endl;
      vtkSmartPointer<vtkCoordinate> coordinate = 
        vtkSmartPointer<vtkCoordinate>::New();
      coordinate->SetCoordinateSystemToDisplay();
      coordinate->SetValue(x,y,0);
      
      // This doesn't produce the right value if the sphere is zoomed in???
      double* world = coordinate->GetComputedWorldValue(this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
      std::cout << "World coordinate: " << world[0] << ", " << world[1] << ", " << world[2] << std::endl;
      
      // Forward events
      vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }
    
};

vtkStandardNewMacro(MouseInteractorStyle3);

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
  
  vtkSmartPointer<MouseInteractorStyle3> style =
    vtkSmartPointer<MouseInteractorStyle3>::New();
  renderWindowInteractor->SetInteractorStyle( style );
  
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();
  
  return  EXIT_SUCCESS ;
}
