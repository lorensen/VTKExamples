#include <vtkCameraActor.h>
#include <vtkSmartPointer.h>

#include <vtkCamera.h>
#include <vtkMapper.h>
#include <vtkNamedColors.h>
#include <vtkPlanes.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

int main(int, char*[])
{
  auto namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Sphere
  auto sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(400);
  sphereSource->Update();

  auto sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  auto sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetDiffuseColor(
      namedColors->GetColor3d("Tomato").GetData());

  // Camera
  auto camera =
    vtkSmartPointer<vtkCamera>::New();

  auto cameraActor =
    vtkSmartPointer<vtkCameraActor>::New();
  cameraActor->SetCamera(camera);
  cameraActor->GetProperty()->SetColor(0, 0, 0);

  // (Xmin,Xmax,Ymin,Ymax,Zmin,Zmax).
  auto bounds = cameraActor->GetBounds();
  std::cout << "bounds: " << bounds[0] << " " << bounds[1] << " " << bounds[2]
            << " " << bounds[3] << " " << bounds[4] << " " << bounds[5]
            << std::endl;

  // Visualize
  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  auto renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(sphereActor);
  // Compute the active camera parameters
  renderer->ResetCamera();

  // Set the camera parameters for the camera actor
  camera->DeepCopy(renderer->GetActiveCamera());
  renderer->AddActor(cameraActor);

  // Position the camera so that we can see the camera actor
  renderer->GetActiveCamera()->SetPosition(1, 0, 0);
  renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  renderer->GetActiveCamera()->SetViewUp(0, 1, 0);
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);

  renderer->ResetCamera();
  renderer->SetBackground(namedColors->GetColor3d("SlateGray").GetData());

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
