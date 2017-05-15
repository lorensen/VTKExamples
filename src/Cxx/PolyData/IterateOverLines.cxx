#include <vtkSmartPointer.h>
#include <vtkLine.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>

int main(int, char *[])
{
  double origin[3] = {0.0, 0.0, 0.0};
  double p0[3] = {1.0, 0.0, 0.0};
  double p1[3] = {0.0, 1.0, 0.0};
  double p2[3] = {0.0, 1.0, 2.0};
  double p3[3] = {1.0, 2.0, 3.0};

  // Create a vtkPoints object and store the points in it
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(origin);
  points->InsertNextPoint(p0);
  points->InsertNextPoint(p1);
  points->InsertNextPoint(p2);
  points->InsertNextPoint(p3);

  // Create a cell array to store the lines in and add the lines to it
  vtkSmartPointer<vtkCellArray> lines =
    vtkSmartPointer<vtkCellArray>::New();

  //Create four lines
  for(unsigned int i = 0; i < 4; i++)
  {
    vtkSmartPointer<vtkLine> line =
      vtkSmartPointer<vtkLine>::New();
    line->GetPointIds()->SetId(0,i);
    line->GetPointIds()->SetId(1,i+1);
    lines->InsertNextCell(line);
  }

  // Create a polydata to store everything in
  vtkSmartPointer<vtkPolyData> linesPolyData =
    vtkSmartPointer<vtkPolyData>::New();

  // Add the points to the dataset
  linesPolyData->SetPoints(points);

  // Add the lines to the dataset
  linesPolyData->SetLines(lines);

  std::cout << "There are " << linesPolyData->GetNumberOfLines() << " lines." << std::endl;

  linesPolyData->GetLines()->InitTraversal();
  vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();
  while(linesPolyData->GetLines()->GetNextCell(idList))
  {
    std::cout << "Line has " << idList->GetNumberOfIds() << " points." << std::endl;

    for(vtkIdType pointId = 0; pointId < idList->GetNumberOfIds(); pointId++)
    {
      std::cout << idList->GetId(pointId) << " ";
    }
    std::cout << std::endl;
  }
  return EXIT_SUCCESS;
}
