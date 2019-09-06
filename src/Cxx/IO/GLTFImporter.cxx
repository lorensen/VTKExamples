#include <vtkSmartPointer.h>
#include <vtkGLTFImporter.h>

#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>

int main(int argc, char* argv[])
{
  if (argc <= 1)
  {
    std::cout << "Usage: " << argv[0] << " <gltf file>" << std::endl;
    return EXIT_FAILURE;
  }

  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkColor3d backgroundColor = colors->GetColor3d("SlateGray");

  auto importer =
    vtkSmartPointer<vtkGLTFImporter>::New();
  importer->SetFileName(argv[1]);

  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(backgroundColor.GetData());
  renderer->UseHiddenLineRemovalOn();

  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 512);
  renderWindow->AddRenderer(renderer);

  auto renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  auto style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  renderWindowInteractor->SetInteractorStyle(style);

  importer->SetRenderWindow(renderWindow);
  importer->Update();

  auto headLight =
    vtkSmartPointer<vtkLight>::New();
  headLight->SetLightTypeToHeadlight();
  headLight->SwitchOn();
  renderer->AddLight(headLight);

  renderWindow->Render();
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(20);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCameraClippingRange();

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
