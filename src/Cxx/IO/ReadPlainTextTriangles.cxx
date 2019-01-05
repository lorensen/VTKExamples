#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkXMLPolyDataWriter.h>
#include <iostream>

vtkPolyData * custom_reader(std::istream & infile)
{
  vtkIdType number_of_points, number_of_triangles;
  infile >> number_of_points >> number_of_triangles;

  vtkSmartPointer<vtkPoints> points
    = vtkSmartPointer<vtkPoints>::New();
  points->SetNumberOfPoints(number_of_points);
  for (vtkIdType i = 0; i < number_of_points; i++)
  {
    double x, y, z;
    infile >> x >> y >> z;
    points->SetPoint(i, x, y, z);
  }

  vtkSmartPointer<vtkCellArray> polys
    = vtkSmartPointer<vtkCellArray>::New();
  for (vtkIdType i = 0; i < number_of_triangles; i++)
  {
    vtkIdType a, b, c;
    infile >> a >> b >> c;
    polys->InsertNextCell(3);
    polys->InsertCellPoint(a);
    polys->InsertCellPoint(b);
    polys->InsertCellPoint(c);
  }
  vtkPolyData * polydata = vtkPolyData::New();
  polydata->SetPoints(points);
  polydata->SetPolys(polys);
  return polydata;
}

int main(int argc, char * argv[])
{
  // Verify command line arguments
  if(argc != 2)
  {
    std::cerr << "Required arguments: triangleFile.txt" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  std::ifstream fin(inputFilename.c_str());

  vtkSmartPointer<vtkPolyData> polydata
    = vtkSmartPointer<vtkPolyData>::Take(
      custom_reader(fin));

  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputData(polydata);
  writer->SetFileName("x.vtp");
  writer->Write();
  return EXIT_SUCCESS;
}
