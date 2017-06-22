#include <vtkSmartPointer.h>
#include <vtkCameraActor.h>

#include <vtkNamedColors.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <vtkPlanes.h>
#include <vtkMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(400);
  sphereSource->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor = 
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetDiffuseColor(
    namedColors->GetColor3d("Tomato").GetData());
  
  // Camera
  vtkSmartPointer<vtkCamera> camera = 
    vtkSmartPointer<vtkCamera>::New();

  vtkSmartPointer<vtkCameraActor> cameraActor = 
    vtkSmartPointer<vtkCameraActor>::New();
  cameraActor->SetCamera(camera);
  cameraActor->GetProperty()->SetColor(0, 0, 0);

  // (Xmin,Xmax,Ymin,Ymax,Zmin,Zmax).
  double* bounds = new double[6];
  bounds = cameraActor->GetBounds();
  std::cout << "bounds: " << bounds[0] << " " << bounds[1] << " " << bounds[2] << " " << 
      bounds[3] << " " << bounds[4] << " " << bounds[5] << std::endl;

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
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
