#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolygon.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Setup four points
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);
  
  // Create the polygon
  vtkSmartPointer<vtkPolygon> polygon =
    vtkSmartPointer<vtkPolygon>::New();
  polygon->GetPointIds()->SetNumberOfIds(4); //make a quad
  polygon->GetPointIds()->SetId(0, 0);
  polygon->GetPointIds()->SetId(1, 1);
  polygon->GetPointIds()->SetId(2, 2);
  polygon->GetPointIds()->SetId(3, 3);
  
  // Add the polygon to a list of polygons
  vtkSmartPointer<vtkCellArray> polygons =
    vtkSmartPointer<vtkCellArray>::New();
  polygons->InsertNextCell(polygon);

  // Create a PolyData
  vtkSmartPointer<vtkPolyData> polygonPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  polygonPolyData->SetPoints(points);
  polygonPolyData->SetPolys(polygons);

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polygonPolyData);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(
    colors->GetColor3d("Silver").GetData());

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Polygon");
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Salmon").GetData());
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
