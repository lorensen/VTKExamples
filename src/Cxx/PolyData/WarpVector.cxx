#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkLine.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkWarpVector.h>

int main(int, char *[])
{

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(2.0, 0.0, 0.0);
  points->InsertNextPoint(3.0, 0.0, 0.0);
  points->InsertNextPoint(4.0, 0.0, 0.0);

  vtkSmartPointer<vtkCellArray> lines =
    vtkSmartPointer<vtkCellArray>::New();
  vtkSmartPointer<vtkLine> line =
    vtkSmartPointer<vtkLine>::New();
  line->GetPointIds()->SetId(0, 0);
  line->GetPointIds()->SetId(1, 1);
  lines->InsertNextCell(line);
  line->GetPointIds()->SetId(0, 1);
  line->GetPointIds()->SetId(1, 2);
  lines->InsertNextCell(line);
  line->GetPointIds()->SetId(0, 2);
  line->GetPointIds()->SetId(1, 3);
  lines->InsertNextCell(line);
  line->GetPointIds()->SetId(0, 3);
  line->GetPointIds()->SetId(1, 4);
  lines->InsertNextCell(line);

  vtkSmartPointer<vtkDoubleArray> warpData =
    vtkSmartPointer<vtkDoubleArray>::New();
  warpData->SetNumberOfComponents(3);
  warpData->SetName("warpData");
  double warp[3] = {0.0, 0.0, 0.0};
  warp[1] = 0.0;
  warpData->InsertNextTuple(warp);
  warp[1] = 0.1;
  warpData->InsertNextTuple(warp);
  warp[1] = 0.3;
  warpData->InsertNextTuple(warp);
  warp[1] = 0.0;
  warpData->InsertNextTuple(warp);
  warp[1] = 0.1;
  warpData->InsertNextTuple(warp);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetLines(lines);
  polydata->GetPointData()->AddArray(warpData);
  polydata->GetPointData()->SetActiveVectors(warpData->GetName());

  //WarpVector will use the array marked as active vector in polydata
  //it has to be a 3 component array
  //with the same number of tuples as points in polydata
  vtkSmartPointer<vtkWarpVector> warpVector =
    vtkSmartPointer<vtkWarpVector>::New();
  warpVector->SetInputData(polydata);
  warpVector->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(warpVector->GetPolyDataOutput());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3);

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
