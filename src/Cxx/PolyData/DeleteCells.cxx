#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkNamedColors.h>
 
int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);
  points->InsertNextPoint(1,1,0);
  points->InsertNextPoint(0,1,0);
 
  vtkSmartPointer<vtkLine> line0 = 
    vtkSmartPointer<vtkLine>::New();
  line0->GetPointIds()->SetId(0, 0);
  line0->GetPointIds()->SetId(1, 1);
 
  vtkSmartPointer<vtkLine> line1 = 
    vtkSmartPointer<vtkLine>::New();
  line1->GetPointIds()->SetId(0, 1);
  line1->GetPointIds()->SetId(1, 2);
 
  vtkSmartPointer<vtkLine> line2 = 
    vtkSmartPointer<vtkLine>::New();
  line2->GetPointIds()->SetId(0, 2);
  line2->GetPointIds()->SetId(1, 3);
 
  vtkSmartPointer<vtkCellArray> lines =
    vtkSmartPointer<vtkCellArray>::New();
  lines->InsertNextCell(line0);
  lines->InsertNextCell(line1);
  lines->InsertNextCell(line2);
 
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetLines(lines);

  // Tell the polydata to build 'upward' links from points to cells.
  polydata->BuildLinks();
  // Mark a cell as deleted.
  polydata->DeleteCell(1);
  // Remove the marked cell.
  polydata->RemoveDeletedCells();

  // Visualize
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputDataObject(polydata);
 
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());
  actor->GetProperty()->SetLineWidth(4);
 
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(actor);
 
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
