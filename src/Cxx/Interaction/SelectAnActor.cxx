#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkObjectFactory.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPropPicker.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

// Handle mouse events
class MouseInteractorStyle5 : public vtkInteractorStyleTrackballActor
{
public:
  static MouseInteractorStyle5* New();
  vtkTypeMacro(MouseInteractorStyle5, vtkInteractorStyleTrackballActor);

  virtual void OnLeftButtonDown() override
  {
    // Forward events
    vtkInteractorStyleTrackballActor::OnLeftButtonDown();

    if(this->InteractionProp == this->Cube)
    {
      std::cout << "Picked cube." << std::endl;
    }
    else if(this->InteractionProp == this->Sphere)
    {
      std::cout << "Picked sphere." << std::endl;
    }
  }

  vtkActor* Cube;
  vtkActor* Sphere;
};

vtkStandardNewMacro(MouseInteractorStyle5);

int main(int, char *[])
{
  // Create a cube
  vtkSmartPointer<vtkCubeSource> cubeSource =
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

  vtkSmartPointer<vtkActor> cubeActor =
    vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);

  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(5,0,0);
  sphereSource->Update();

  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

  // Create an actor
  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);

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

  // Set the custom stype to use for interaction.
  vtkSmartPointer<MouseInteractorStyle5> style =
    vtkSmartPointer<MouseInteractorStyle5>::New();
  style->SetDefaultRenderer(renderer);
  style->Cube = cubeActor;
  style->Sphere = sphereActor;

  renderWindowInteractor->SetInteractorStyle(style);

  renderer->AddActor(cubeActor);
  renderer->AddActor(sphereActor);
  renderer->SetBackground(0,0,1);

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
