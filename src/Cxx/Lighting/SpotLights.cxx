#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkNamedColors.h>

int main (int, char *[])
{
  // create a rendering window and renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);

  // create a renderwindowinteractor
  vtkSmartPointer<vtkRenderWindowInteractor>   iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renderWindow);

  // create a plane and add it to the renderer
  vtkSmartPointer<vtkPlaneSource>   source =
    vtkSmartPointer<vtkPlaneSource>::New();
  source->SetOrigin(-5.0, 0.0, 5.0);
  source->SetPoint1(5.0, 0.0, 5.0);
  source->SetPoint2(-5.0, 0.0, -5.0);
  source->SetResolution(100, 100);
  vtkSmartPointer<vtkPolyDataMapper>   mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(source->GetOutputPort());

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkActor>   actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  renderer->AddActor(actor);
  
  // set camera view
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(40.0);
  renderer->GetActiveCamera()->Elevation(30.0);

  // create a green light
  vtkSmartPointer<vtkLight> greenLight =
    vtkSmartPointer<vtkLight>::New();
  greenLight->PositionalOn();
  greenLight->SetPosition(-4.0, 4.0, -1.0);
  greenLight->SetColor(colors->GetColor3d("Lawn_green").GetData());
  greenLight->SetIntensity(0.5);

  // create a pink light
  vtkSmartPointer<vtkLight> pinkLight =
    vtkSmartPointer<vtkLight>::New();
  pinkLight->PositionalOn();
  pinkLight->SetPosition(4.0, 5.0, 1.0);
  pinkLight->SetColor(colors->GetColor3d("DeepPink").GetData());
  pinkLight->SetIntensity(0.6);

  // add lights to the renderer
  renderer->AddLight(pinkLight);
  renderer->AddLight(greenLight);

  // define a background for better visibility
  renderer->SetBackground(colors->GetColor3d("RoyalBlue").GetData());
  renderer->SetBackground2(colors->GetColor3d("SkyBlue").GetData());
  renderer->GradientBackgroundOn();

  // enable interactor
  iren->Initialize();
  renderWindow->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
