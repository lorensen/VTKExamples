#include <vtkSmartPointer.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkPolyDataSilhouette.h>
#include <vtkMath.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkPropPicker.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkNamedColors.h>

namespace
{
// Handle mouse events
class MouseInteractorHighLightActor : public vtkInteractorStyleTrackballCamera
{
public:
  static MouseInteractorHighLightActor* New();
  vtkTypeMacro(MouseInteractorHighLightActor,
               vtkInteractorStyleTrackballCamera);

  MouseInteractorHighLightActor()
  {
    LastPickedActor = nullptr;
    SilhouetteActor = nullptr;
    Silhouette = nullptr;
  }
  virtual ~MouseInteractorHighLightActor()
  {
  }
  virtual void OnLeftButtonDown() override
  {
    int *clickPos = this->GetInteractor()->GetEventPosition();

    // Pick from this location.
    auto picker =
      vtkSmartPointer<vtkPropPicker>::New();
    picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
    this->LastPickedActor = picker->GetActor();

    // If we picked something before, remove the silhouette actor and
    // generate a new one
    if (this->LastPickedActor)
    {
      this->GetDefaultRenderer()->RemoveActor(this->SilhouetteActor);

      // Highlight the picked actor by generating a silouhette
      this->Silhouette->SetInputData(
        dynamic_cast<vtkPolyDataMapper*>(this->LastPickedActor->GetMapper())->GetInput());
      this->GetDefaultRenderer()->AddActor(this->SilhouetteActor);
    }

    // Forward events
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}
  void SetSilhouette(vtkPolyDataSilhouette *silhouette)
  {
    this->Silhouette = silhouette;
  }
  void SetSilhouetteActor(vtkActor *silhouetteActor)
  {
    this->SilhouetteActor = silhouetteActor;
  }
private:
  vtkActor *              LastPickedActor;
  vtkActor *              SilhouetteActor;
  vtkPolyDataSilhouette * Silhouette;
};
}

vtkStandardNewMacro(MouseInteractorHighLightActor);

// Execute application.
int main(int argc, char* argv[])
{
  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();
  colors->SetColor("Bkg", 0.3, 0.4, 0.5);

  int numberOfSpheres = 10;
  if (argc > 1)
  {
    numberOfSpheres = atoi(argv[1]);
  }
  // Create a renderer and render window
  auto renderer =
      vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);

  // An interactor
  auto interactor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  for (int i = 0; i < numberOfSpheres; ++i)
  {
    auto source =
        vtkSmartPointer<vtkSphereSource>::New();
    double x, y, z, radius;
    x = vtkMath::Random(-5, 5);
    y = vtkMath::Random(-5, 5);
    z = vtkMath::Random(-5, 5);
    radius = vtkMath::Random(0.5, 1.0);
    source->SetRadius(radius);
    source->SetCenter(x, y, z);
    source->SetPhiResolution(11);
    source->SetThetaResolution(21);
    auto mapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(source->GetOutputPort());
    auto actor =
        vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    double r, g, b;
    r = vtkMath::Random(0.4, 1.0);
    g = vtkMath::Random(0.4, 1.0);
    b = vtkMath::Random(0.4, 1.0);
    actor->GetProperty()->SetDiffuseColor(r, g, b);
    actor->GetProperty()->SetDiffuse(0.8);
    actor->GetProperty()->SetSpecular(0.5);
    actor->GetProperty()->SetSpecularColor(
        colors->GetColor3d("White").GetData());
    actor->GetProperty()->SetSpecularPower(30.0);
    renderer->AddActor(actor);
  }

  renderer->SetBackground(colors->GetColor3d("Bkg").GetData());

  // Render and interact
  renderWindow->Render();

  // Create the silhouette pipeline, the input data will be set in the
  // interactor
  auto silhouette =
    vtkSmartPointer<vtkPolyDataSilhouette>::New();
  silhouette->SetCamera(renderer->GetActiveCamera());

  // Create mapper and actor for silhouette
  auto silhouetteMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  silhouetteMapper->SetInputConnection(silhouette->GetOutputPort());

  auto silhouetteActor =
    vtkSmartPointer<vtkActor>::New();
  silhouetteActor->SetMapper(silhouetteMapper);
  silhouetteActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  silhouetteActor->GetProperty()->SetLineWidth(5);

  // Set the custom type to use for interaction.
  auto style =
      vtkSmartPointer<MouseInteractorHighLightActor>::New();
  style->SetDefaultRenderer(renderer);
  style->SetSilhouetteActor(silhouetteActor);
  style->SetSilhouette(silhouette);

  interactor->SetInteractorStyle(style);

  interactor->Start();

  return EXIT_SUCCESS;
}
