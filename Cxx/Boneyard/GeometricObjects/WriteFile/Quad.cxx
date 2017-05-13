#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkQuad.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  //Setup the coordinates of four points 
  //(must be in counter clockwise order)
  double P0[3] = {0.0, 0.0, 0.0};
  double P1[3] = {1.0, 0.0, 0.0};
  double P2[3] = {1.0, 1.0, 0.0};
  double P3[3] = {0.0, 1.0, 0.0};
      
  //Create the points
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(P0);
  points->InsertNextPoint(P1);
  points->InsertNextPoint(P2);
  points->InsertNextPoint(P3);
  
  //Create a quad on the points
  vtkSmartPointer<vtkQuad> quad = vtkSmartPointer<vtkQuad>::New();
  quad->GetPointIds()->SetId(0,0);
  quad->GetPointIds()->SetId(1,1);
  quad->GetPointIds()->SetId(2,2);
  quad->GetPointIds()->SetId(3,3);
  
  //Add the quad to a cell array
  vtkSmartPointer<vtkCellArray> quads = vtkSmartPointer<vtkCellArray>::New();
  quads->InsertNextCell(quad);

  //Add the points and quad to a polydata
  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetPolys(quads);

  //Write the file
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInput(polydata);
  writer->SetFileName("Quad.vtp");
  writer->Write();

  return EXIT_SUCCESS;
}
