#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkLine.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  //create two points, P0 and P1
  double P0[3] = {1.0, 0.0, 0.0};
  double P1[3] = {0.0, 1.0, 0.0};
      
  //add the two poitns to a vtkPoints object
  vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
  pts->InsertNextPoint(P0);
  pts->InsertNextPoint(P1);
  
  //create a line between the two points
  vtkSmartPointer<vtkLine> line = vtkSmartPointer<vtkLine>::New();
  line->GetPointIds()->SetId(0,0); //the SetId(A,B) call is the following: 
  //A = the id of the point relative to the line - this can only be 0 or 1. 
  //B = the index into the vtkPoints object of the point that you would like to set the Ath point to.
  line->GetPointIds()->SetId(1,1);
  
  //create a cell array to store the line in
  vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
  lines->InsertNextCell(line);

  //create a polydata to store everything in
  vtkSmartPointer<vtkPolyData> pdata = vtkSmartPointer<vtkPolyData>::New();

  //add the points to the dataset
  pdata->SetPoints(pts);

  //add the lines to the dataset
  pdata->SetLines(lines);

  //write the file
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInput(pdata);
  writer->SetFileName("Line.vtp");
  writer->Write();

  return EXIT_SUCCESS;
}
