#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkClipPolyData.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPlane.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSuperquadricSource.h>

int main(int, char*[])
{
  vtkNew<vtkNamedColors> colors;

  // Create a superquadric
  vtkNew<vtkSuperquadricSource> superquadricSource;
  superquadricSource->SetPhiRoundness(3.1);
  superquadricSource->SetThetaRoundness(2.2);

  // Define a clipping plane
  vtkNew<vtkPlane> clipPlane;
  clipPlane->SetNormal(1.0, -1.0, -1.0);
  clipPlane->SetOrigin(0.0, 0.0, 0.0);

  // Clip the source with the plane
  vtkNew<vtkClipPolyData> clipper;
  clipper->SetInputConnection(superquadricSource->GetOutputPort());
  clipper->SetClipFunction(clipPlane);
  // This will give us the polygonal data that is clipped away
  clipper->GenerateClippedOutputOn();

  // Create a mapper and actor
  vtkNew<vtkPolyDataMapper> superquadricMapper;
  superquadricMapper->SetInputConnection(clipper->GetOutputPort());

  vtkNew<vtkActor> superquadricActor;
  superquadricActor->SetMapper(superquadricMapper);

  // Create a property to be used for the back faces. Turn off all
  // shading by specifying 0 weights for specular and diffuse. Max the
  // ambient.
  vtkNew<vtkProperty> backFaces;
  backFaces->SetSpecular(0.0);
  backFaces->SetDiffuse(0.0);
  backFaces->SetAmbient(1.0);
  backFaces->SetAmbientColor(colors->GetColor3d("Tomato").GetData());

  superquadricActor->SetBackfaceProperty(backFaces);

  // Here we get the the polygonal data that is clipped away
  vtkNew<vtkPolyDataMapper> clippedAwayMapper;
  clippedAwayMapper->SetInputData(clipper->GetClippedOutput());
  clippedAwayMapper->ScalarVisibilityOff();

  // Let us display it as a faint object
  vtkNew<vtkActor> clippedAwayActor;
  clippedAwayActor->SetMapper(clippedAwayMapper);
  clippedAwayActor->GetProperty()->SetDiffuseColor(
      colors->GetColor3d("Silver").GetData());
  clippedAwayActor->GetProperty()->SetOpacity(0.1);

  // Create a renderer
  vtkNew<vtkRenderer> renderer;

  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->SetWindowName("SolidClip");

  renderWindow->AddRenderer(renderer);

  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add actors to the renderers
  renderer->AddActor(superquadricActor);
  renderer->AddActor(clippedAwayActor);
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renderWindow->SetSize(600, 600);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Dolly(1.5);
  renderer->ResetCameraClippingRange();
  renderWindow->Render();

  // Interact with the window
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
