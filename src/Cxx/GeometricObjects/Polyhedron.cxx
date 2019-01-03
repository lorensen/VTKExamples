#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <vtkDataSetMapper.h>
#include <vtkIdList.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyhedron.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>

int main( int, char*[] )
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // create polyhedron (cube)
  vtkIdType pointIds[8] = {0, 1, 2, 3, 4, 5, 6, 7};

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(-1.0,-1.0,-1.0);
  points->InsertNextPoint( 1.0,-1.0,-1.0);
  points->InsertNextPoint( 1.0, 1.0,-1.0);
  points->InsertNextPoint(-1.0, 1.0,-1.0);
  points->InsertNextPoint(-1.0,-1.0, 1.0);
  points->InsertNextPoint( 1.0,-1.0, 1.0);
  points->InsertNextPoint( 1.0, 1.0, 1.0);
  points->InsertNextPoint(-1.0, 1.0, 1.0);

  vtkSmartPointer<vtkCellArray> faces =
    vtkSmartPointer<vtkCellArray>::New();
  vtkIdType face0[4] = {0, 3, 2, 1};
  vtkIdType face1[4] = {0, 4, 7, 3};
  vtkIdType face2[4] = {4, 5, 6, 7};
  vtkIdType face3[4] = {5, 1, 2, 6};
  vtkIdType face4[4] = {0, 1, 5, 4};
  vtkIdType face5[4] = {2, 3, 7, 6};

  faces->InsertNextCell(4, face0);
  faces->InsertNextCell(4, face1);
  faces->InsertNextCell(4, face2);
  faces->InsertNextCell(4, face3);
  faces->InsertNextCell(4, face4);
  faces->InsertNextCell(4, face5);

  vtkSmartPointer<vtkUnstructuredGrid> ugrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ugrid->SetPoints(points);
  ugrid->InsertNextCell(
    VTK_POLYHEDRON, 8, pointIds,
    6, faces->GetPointer());

  // Here we write out the cube.
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetInputData(ugrid);
  writer->SetFileName("polyhedron.vtu");
  writer->SetDataModeToAscii();
  writer->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputData(ugrid);

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
  renderWindow->SetWindowName("Polyhedron");
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Salmon").GetData());
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
