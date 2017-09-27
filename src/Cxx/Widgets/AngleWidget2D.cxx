#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkAngleWidget.h>
#include <vtkAngleRepresentation2D.h>

int main(int /* argc */, char * /* argv */ [])
{
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

  double pos1[3] = {50.0, 200.0, 0.0};
  double pos2[3] = {200.0, 20.0, 0.0};
  double center[3] = {100.0, 100.0, 0.0};
  vtkSmartPointer<vtkAngleRepresentation2D> rep =
    vtkSmartPointer<vtkAngleRepresentation2D>::New();
  rep->ArcVisibilityOff();

  vtkSmartPointer<vtkAngleWidget> angleWidget =
    vtkSmartPointer<vtkAngleWidget>::New();
  angleWidget->CreateDefaultRepresentation();
  angleWidget->SetRepresentation(rep);
  angleWidget->SetInteractor(renderWindowInteractor);

  renderWindow->Render();

  renderWindowInteractor->Initialize();
  renderWindow->Render();
  angleWidget->On();
  rep->SetPoint1DisplayPosition(pos1);
  rep->SetPoint2DisplayPosition(pos2);
  rep->SetCenterDisplayPosition(center);
  rep->Ray1VisibilityOn();
  rep->Ray2VisibilityOn();
  rep->ArcVisibilityOn();

  // Begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
