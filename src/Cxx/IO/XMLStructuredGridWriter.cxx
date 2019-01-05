#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkStructuredGrid.h>
#include <vtkSmartPointer.h>

int main ( int, char *[] )
{
   // Create a grid
  vtkSmartPointer<vtkStructuredGrid> structuredGrid =
    vtkSmartPointer<vtkStructuredGrid>::New();

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(1, 0, 0);
  points->InsertNextPoint(0, 1, 0);
  points->InsertNextPoint(1, 1, 0);
  points->InsertNextPoint(0, 2, 0);
  points->InsertNextPoint(1, 2, 1);
  
  // Specify the dimensions of the grid
  structuredGrid->SetDimensions(2,3,1);
  structuredGrid->SetPoints(points);
  
  // Write file
  vtkSmartPointer<vtkXMLStructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLStructuredGridWriter>::New();
  writer->SetFileName("output.vts");
  writer->SetInputData(structuredGrid);
  writer->Write();

  return EXIT_SUCCESS;
}
