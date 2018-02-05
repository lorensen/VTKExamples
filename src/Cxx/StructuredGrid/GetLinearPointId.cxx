#include <vtkSmartPointer.h>
#include <vtkStructuredData.h>
#include <vtkStructuredGrid.h>

int main(int, char *[])
{
  // Create a grid
  vtkSmartPointer<vtkStructuredGrid> structuredGrid =
    vtkSmartPointer<vtkStructuredGrid>::New();

  // Set the dimensions of the grid
  {
    int dims[3] = {5,10,1};
    structuredGrid->SetDimensions(dims);
  }

  // Retrieve the dimensions of the grid
  int dimensions[3];
  structuredGrid->GetDimensions(dimensions);

  {
  int queryPoint[3] = {4, 0, 0};
  vtkIdType pointId = vtkStructuredData::ComputePointId(dimensions, queryPoint);

  std::cout << "PointId: " << pointId << std::endl; // Outputs '4'
  }

  {
  int queryPoint[3] = {0, 1, 0};
  vtkIdType pointId = vtkStructuredData::ComputePointId(dimensions, queryPoint);

  std::cout << "PointId: " << pointId << std::endl; // Outputs '5'
  }
  return EXIT_SUCCESS;
}
