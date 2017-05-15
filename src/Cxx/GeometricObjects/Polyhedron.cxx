#include "vtkSmartPointer.h"

#include "vtkVersion.h"
#include "vtkUnstructuredGrid.h"
#include "vtkPolyhedron.h"
#include "vtkCellArray.h"
#include "vtkPointData.h"
#include "vtkCellData.h"
#include "vtkIdList.h"
#include "vtkPoints.h"
#include "vtkDataArray.h"
#include "vtkXMLUnstructuredGridWriter.h"

int main( int, char*[] )
{
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

  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
#if VTK_MAJOR_VERSION <= 5
  writer->SetInput(ugrid);
#else
  writer->SetInputData(ugrid);
#endif
  writer->SetFileName("polyhedron.vtu");
  writer->SetDataModeToAscii();
  writer->Update();

  return EXIT_SUCCESS;
}
