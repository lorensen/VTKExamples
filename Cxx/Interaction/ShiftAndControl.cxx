#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkObjectFactory.h>

class MouseInteractorStyleShiftAndControl : public vtkInteractorStyleTrackballActor
{
  public:
    static MouseInteractorStyleShiftAndControl* New();

    virtual void OnLeftButtonDown()
    {
      if(this->Interactor->GetShiftKey())
      {
        std::cout << "Shift held. ";
      }

      if(this->Interactor->GetControlKey())
      {
        std::cout << "Control held. ";
      }

        /* this doesn't work ??? */
      if(this->Interactor->GetAltKey())
      {
        std::cout << "Alt held. ";
      }

      std::cout << "Pressed left mouse button." << std::endl;

      // Forward events
      vtkInteractorStyleTrackballActor::OnLeftButtonDown();
    }

};

vtkStandardNewMacro(MouseInteractorStyleShiftAndControl);

int main (int, char *[])
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

  vtkSmartPointer<MouseInteractorStyleShiftAndControl> style =
    vtkSmartPointer<MouseInteractorStyleShiftAndControl>::New();

  renderWindowInteractor->SetInteractorStyle( style );

  // Begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
