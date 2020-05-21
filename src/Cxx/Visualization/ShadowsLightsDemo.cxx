// The scene consists of
// * 4 actors: a rectangle, a box, a cone and a sphere. The box, the cone and
// the sphere are above the rectangle.
// * 2 spotlights: one in the direction of the box, another one in the
// direction of the sphere. Both lights are above the box, the cone and
// the sphere.
#include <vtkSmartPointer.h>

#include <vtkCameraPass.h>
#include <vtkRenderPassCollection.h>

#include <vtkSequencePass.h>
#include <vtkShadowMapBakerPass.h>
#include <vtkShadowMapPass.h>

#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkPlaneSource.h>
#include <vtkSphereSource.h>

#include <vtkOpenGLRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkLightActor.h>
#include <vtkLightCollection.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>

#include <vtkNamedColors.h>

namespace {
// For each spotlight, add a light frustum wireframe representation and a cone
// wireframe representation, colored with the light color.
void AddLightActors(vtkRenderer* r);
} // namespace

int main(int, char*[])
{
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(400, 400);
  renderWindow->SetMultiSamples(0);

  renderWindow->SetAlphaBitPlanes(1);
  interactor->SetRenderWindow(renderWindow);

  auto renderer = vtkSmartPointer<vtkOpenGLRenderer>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  auto rectangleSource = vtkSmartPointer<vtkPlaneSource>::New();
  rectangleSource->SetOrigin(-5.0, 0.0, 5.0);
  rectangleSource->SetPoint1(5.0, 0.0, 5.0);
  rectangleSource->SetPoint2(-5.0, 0.0, -5.0);
  rectangleSource->SetResolution(100, 100);

  auto rectangleMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  rectangleMapper->SetInputConnection(rectangleSource->GetOutputPort());

  rectangleMapper->SetScalarVisibility(0);

  auto shadows = vtkSmartPointer<vtkShadowMapPass>::New();

  auto seq = vtkSmartPointer<vtkSequencePass>::New();

  auto passes = vtkSmartPointer<vtkRenderPassCollection>::New();
  passes->AddItem(shadows->GetShadowMapBakerPass());
  passes->AddItem(shadows);
  seq->SetPasses(passes);

  auto cameraP = vtkSmartPointer<vtkCameraPass>::New();
  cameraP->SetDelegatePass(seq);

  // tell the renderer to use our render pass pipeline
  vtkOpenGLRenderer* glrenderer =
      dynamic_cast<vtkOpenGLRenderer*>(renderer.GetPointer());
  glrenderer->SetPass(cameraP);

  auto colors = vtkSmartPointer<vtkNamedColors>::New();
  vtkColor3d boxColor = colors->GetColor3d("Tomato");
  vtkColor3d rectangleColor = colors->GetColor3d("Beige");
  vtkColor3d coneColor = colors->GetColor3d("Peacock");
  vtkColor3d sphereColor = colors->GetColor3d("Banana");

  auto rectangleActor = vtkSmartPointer<vtkActor>::New();
  rectangleActor->SetMapper(rectangleMapper);
  rectangleActor->SetVisibility(1);
  rectangleActor->GetProperty()->SetColor(rectangleColor.GetData());

  auto boxSource = vtkSmartPointer<vtkCubeSource>::New();
  boxSource->SetXLength(2.0);

  auto boxNormals = vtkSmartPointer<vtkPolyDataNormals>::New();
  boxNormals->SetInputConnection(boxSource->GetOutputPort());
  boxNormals->ComputePointNormalsOff();
  boxNormals->ComputeCellNormalsOn();
  boxNormals->Update();
  boxNormals->GetOutput()->GetPointData()->SetNormals(nullptr);

  auto boxMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  boxMapper->SetInputConnection(boxNormals->GetOutputPort());
  boxMapper->SetScalarVisibility(0);

  auto boxActor = vtkSmartPointer<vtkActor>::New();
  boxActor->SetMapper(boxMapper);
  boxActor->SetVisibility(1);
  boxActor->SetPosition(-2.0, 2.0, 0.0);
  boxActor->GetProperty()->SetColor(boxColor.GetData());

  auto coneSource = vtkSmartPointer<vtkConeSource>::New();
  coneSource->SetResolution(24);
  coneSource->SetDirection(1.0, 1.0, 1.0);

  auto coneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection(coneSource->GetOutputPort());
  coneMapper->ScalarVisibilityOff();

  auto coneActor = vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMapper);
  coneActor->VisibilityOn();
  coneActor->SetPosition(0.0, 1.0, 1.0);
  coneActor->GetProperty()->SetColor(coneColor.GetData());

  auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetThetaResolution(32);
  sphereSource->SetPhiResolution(32);

  auto sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  sphereMapper->ScalarVisibilityOff();

  auto sphereActor = vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);

  sphereActor->VisibilityOn();
  sphereActor->SetPosition(2.0, 2.0, -1.0);
  sphereActor->GetProperty()->SetColor(sphereColor.GetData());

  renderer->AddViewProp(rectangleActor);
  renderer->AddViewProp(boxActor);
  renderer->AddViewProp(coneActor);
  renderer->AddViewProp(sphereActor);

  // Spotlights.

  // lighting the box.
  auto l1 = vtkSmartPointer<vtkLight>::New();
  l1->SetPosition(-4.0, 4.0, -1.0);
  l1->SetFocalPoint(boxActor->GetPosition());
  l1->SetColor(1.0, 1.0, 1.0);
  l1->PositionalOn();
  renderer->AddLight(l1);
  l1->SwitchOn();

  // lighting the sphere
  auto l2 = vtkSmartPointer<vtkLight>::New();
  l2->SetPosition(4.0, 5.0, 1.0);
  l2->SetFocalPoint(sphereActor->GetPosition());
  l2->SetColor(1.0, 0.0, 1.0);
  l2->PositionalOn();
  renderer->AddLight(l2);
  l2->SwitchOn();

  AddLightActors(renderer);

  renderer->SetBackground2(colors->GetColor3d("Silver").GetData());
  renderer->SetBackground(colors->GetColor3d("LightGrey").GetData());
  renderer->SetGradientBackground(true);

  renderWindow->Render();
  renderWindow->SetWindowName("ShadowsLightsDemo");

  renderer->ResetCamera();

  auto camera = renderer->GetActiveCamera();
  camera->Azimuth(40.0);
  camera->Elevation(10.0);

  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}

namespace {
// For each spotlight, add a light frustum wireframe representation and a cone
// wireframe representation, colored with the light color.
void AddLightActors(vtkRenderer* r)
{
  vtkLightCollection* lights = r->GetLights();
  lights->InitTraversal();

  vtkLight* light = lights->GetNextItem();
  while (light != 0)
  {
    double angle = light->GetConeAngle();
    if (light->LightTypeIsSceneLight() && light->GetPositional() &&
        angle < 180.0) // spotlight
    {
      auto light_actor = vtkSmartPointer<vtkLightActor>::New();
      light_actor->SetLight(light);
      r->AddViewProp(light_actor);
    }
    light = lights->GetNextItem();
  }
}
} // namespace
