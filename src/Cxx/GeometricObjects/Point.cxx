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

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create the geometry of a point (the coordinate)
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  const float p[3] = {1.0, 2.0, 3.0};
	
  // Create the topology of the point (a vertex)
  vtkSmartPointer<vtkCellArray> vertices =
    vtkSmartPointer<vtkCellArray>::New();
  // We need an an array of point id's for InsertNextCell.
  vtkIdType pid[1];
  pid[0] = points->InsertNextPoint(p);
  vertices->InsertNextCell(1,pid);
  
  // Create a polydata object
  vtkSmartPointer<vtkPolyData> point =
    vtkSmartPointer<vtkPolyData>::New();

  // Set the points and vertices we created as the geometry and topology of the polydata
  point->SetPoints(points);
  point->SetVerts(vertices);
  
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(point);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  actor->GetProperty()->SetPointSize(20);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Point");
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("DarkOliveGreen").GetData());
  
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
