#include <vtkRenderView.h>
#include <vtkSphereSource.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderView> renderView =
    vtkSmartPointer<vtkRenderView>::New();
  renderView->SetInteractionMode(vtkRenderView::INTERACTION_MODE_3D);
  renderView->GetRenderer()->AddActor(actor);
  renderView->Update();

  renderView->ResetCamera();
  renderView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
