#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

int main ( int, char *[] )
{
  // Create 10 points.
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  for ( unsigned int i = 0; i < 10; ++i )
  {
    points->InsertNextPoint ( i, i, i );
  }

  // Create a polydata object and add the points to it.
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Write the file
  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("test.vtp");
  writer->SetInputData(polydata);

  // Optional - set the mode. The default is binary.
  //writer->SetDataModeToBinary();
  //writer->SetDataModeToAscii();

  writer->Write();

  return EXIT_SUCCESS;
}
