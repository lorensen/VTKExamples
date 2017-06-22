#include <vtkSmartPointer.h>
#include <vtkFrustumSource.h>

#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkCamera.h>
#include <vtkPlanes.h>
#include <vtkMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  double planesArray[24];
  
  camera->GetFrustumPlanes(1.0, planesArray);
  
  vtkSmartPointer<vtkPlanes> planes =
    vtkSmartPointer<vtkPlanes>::New();
  planes->SetFrustumPlanes(planesArray);
  
  vtkSmartPointer<vtkFrustumSource> frustumSource =
    vtkSmartPointer<vtkFrustumSource>::New();
  frustumSource->ShowLinesOff();
  frustumSource->SetPlanes(planes);
  frustumSource->Update();

  vtkPolyData* frustum = frustumSource->GetOutput();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(frustum);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  // a renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(namedColors->GetColor3d("BurlyWood").GetData());

  // Position the camera so that we can see the frustum
  renderer->GetActiveCamera()->SetPosition(1, 0, 0);
  renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  renderer->GetActiveCamera()->SetViewUp(0, 1, 0);
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCamera();

  // render an image (lights and cameras are created automatically)
  renderWindow->Render();

  // begin mouse interaction
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
