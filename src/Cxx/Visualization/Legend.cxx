#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkLegendBoxActor.h>
#include <vtkNamedColors.h>

#include <vtkSmartPointer.h>
 
int main (int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5000.0);
  sphereSource->Update();

  vtkPolyData* polydata = sphereSource->GetOutput();
 
  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polydata);
 
  // Create an actor
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
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
 
  vtkSmartPointer<vtkLegendBoxActor> legend = 
    vtkSmartPointer<vtkLegendBoxActor>::New();
  legend->SetNumberOfEntries(2);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  double color[4];

  vtkSmartPointer<vtkCubeSource> legendBox = 
    vtkSmartPointer<vtkCubeSource>::New();
  legendBox->Update();
  colors->GetColor("tomato", color);
  legend->SetEntry(0, legendBox->GetOutput(), "Box", color);

  colors->GetColor("banana", color);
  legend->SetEntry(1, sphereSource->GetOutput(), "Ball", color);
  
  // place legend in lower right
  legend->GetPositionCoordinate()->SetCoordinateSystemToView();
  legend->GetPositionCoordinate()->SetValue(.5, -1.0);

  legend->GetPosition2Coordinate()->SetCoordinateSystemToView();
  legend->GetPosition2Coordinate()->SetValue(1.0, -0.5);

  legend->UseBackgroundOn();
  double background[4];
  colors->GetColor("warm_grey", background);
  legend->SetBackgroundColor(background);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->AddActor(legend);
  renderer->SetBackground(0,1,1); // Background color cyan
 
  // Render an image (lights and cameras are created automatically)
  renderWindow->Render();
 
  // Begin mouse interaction
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
