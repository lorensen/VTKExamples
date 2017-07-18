#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCellTreeLocator.h>
#include <vtkGenericCell.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(1.0);
  sphereSource->Update();


  // Create the tree
  vtkSmartPointer<vtkCellTreeLocator> cellTree =
    vtkSmartPointer<vtkCellTreeLocator>::New();
  cellTree->SetDataSet(sphereSource->GetOutput());
  cellTree->BuildLocator();

  double testInside[3] = {.5, 0.0, 0.0};
  double testOutside[3] = {10.0, 0.0, 0.0};

  double pcoords[3], weights[3];

  vtkIdType cellId;

  vtkSmartPointer<vtkGenericCell> cell = vtkSmartPointer<vtkGenericCell>::New();

  int returnValue = EXIT_SUCCESS;

  // Should be inside
  cellId = cellTree->FindCell(testInside,0,
                              cell, pcoords, weights);
  if (cellId>=0)
  {
    std::cout << "First point: in cell " << cellId << std::endl;
  }
  else
  {
    std::cout << "ERROR: Cell was not found but should have been." << std::endl;
    returnValue = EXIT_FAILURE;
  }

  // Should be outside
  cellId = cellTree->FindCell(testOutside,0,
                            cell, pcoords, weights);
  if (cellId>=0)
  {
    std::cout << "ERROR: Found point in cell " << cellId
              << " but it should be outside the domain." << std::endl;
    returnValue = EXIT_FAILURE;
  }
  else
  {
    std::cout << "Second point: outside" << std::endl;
  }

  return returnValue;
}
