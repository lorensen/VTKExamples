#include <vtkSmartPointer.h>
#include <vtkPolygon.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>

int main(int, char *[])
{
  //Create four points
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);

  //Create a polygon
  vtkSmartPointer<vtkPolygon> polygon = 
    vtkSmartPointer<vtkPolygon>::New();
  polygon->GetPointIds()->SetNumberOfIds(4); //make a quad
  polygon->GetPointIds()->SetId(0, 0);
  polygon->GetPointIds()->SetId(1, 1);
  polygon->GetPointIds()->SetId(2, 2);
  polygon->GetPointIds()->SetId(3, 3);
  //this is an unfortunate example, as you cannot tell which 0,1,2 or 3 is which!
  //A clearer statement is SetId(0, IndexOfPoint0)

  //Create a cell array to add the polygon to.
  vtkSmartPointer<vtkCellArray> polygons = vtkSmartPointer<vtkCellArray>::New();
  polygons->InsertNextCell(polygon);

  //Add the points and polygon to a polydata object.
  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetPolys(polygons);

  //Write the file.
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("Polygon.vtp");
  writer->SetInput(polydata);
  writer->Write();

  return EXIT_SUCCESS;
}
