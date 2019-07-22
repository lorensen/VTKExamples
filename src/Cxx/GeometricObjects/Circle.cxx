// Classes specific to this example
#include <vtkRegularPolygonSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
// Generic VTK pipeline elements
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
// Auxiliary class
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  // Create a circle
  vtkSmartPointer<vtkRegularPolygonSource> polygonSource =
    vtkSmartPointer<vtkRegularPolygonSource>::New();
  
  //polygonSource->GeneratePolygonOff(); // Uncomment this line to generate only the outline of the circle
  polygonSource->SetNumberOfSides(50);
  polygonSource->SetRadius(5);
  polygonSource->SetCenter(0, 0, 0);
  
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(polygonSource->GetOutputPort());;
  
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(.3,.3,.5); // Background color purple
  
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
