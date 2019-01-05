#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyLine.h>
#include <vtkTriangle.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkSmartPointer.h>

int main ( int, char *[] )
{
  // Create 8 Vertices.
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  for ( unsigned int i = 0; i < 2; ++i )
     for ( unsigned int j = 0; j < 4; ++j )
          points->InsertNextPoint( i, j, 0);

   //Create Edges
    vtkSmartPointer<vtkPolyLine> line =
    vtkSmartPointer<vtkPolyLine>::New();
    line->GetPointIds()->SetNumberOfIds(8);
  for ( unsigned int i = 0; i < 8; ++i )
      line->GetPointIds()->SetId(i,i);

   vtkSmartPointer<vtkCellArray> cellArray =
    vtkSmartPointer<vtkCellArray>::New();
   cellArray->InsertNextCell(line);

  // Create a Graph with Vertices and Edges.
  vtkSmartPointer<vtkUnstructuredGrid> grid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  grid->SetPoints(points);
  grid->SetCells(VTK_POLY_LINE,cellArray);

  // Write the file
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName("testVertex.vtu");
  writer->SetInputData(grid);
  writer->Write();

  return EXIT_SUCCESS;
}
