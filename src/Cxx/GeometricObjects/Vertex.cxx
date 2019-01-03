#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkVertex.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);

  vtkSmartPointer<vtkVertex> vertex = 
    vtkSmartPointer<vtkVertex>::New();
  vertex->GetPointIds()->SetId(0, 0);
  
  vtkSmartPointer<vtkCellArray> vertices =
    vtkSmartPointer<vtkCellArray>::New();
  vertices->InsertNextCell(vertex);
  
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetVerts(vertices);
  
  
  // Setup actor and mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polydata);
 
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(10);
  actor->GetProperty()->SetColor(colors->GetColor3d("Cyan").GetData());

  // Setup render window, renderer, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Vertex");
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("DarkGreen").GetData());

  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
