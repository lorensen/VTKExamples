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

int main(int argc, char *argv[])
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

  vtkSmartPointer<vtkAngleRepresentation2D> rep = 
    vtkSmartPointer<vtkAngleRepresentation2D>::New();
  rep->ArcVisibilityOff();
  
  vtkSmartPointer<vtkAngleWidget> angleWidget = 
    vtkSmartPointer<vtkAngleWidget>::New();
  angleWidget->SetRepresentation(rep);
  angleWidget->SetInteractor(renderWindowInteractor);
  angleWidget->CreateDefaultRepresentation();
  
  renderWindow->Render();
  
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  angleWidget->On();
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
