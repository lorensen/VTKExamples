#include <vtkSmartPointer.h>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkIdList.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkTriangle> triangle =
    vtkSmartPointer<vtkTriangle>::New();
  triangle->GetPoints()->SetPoint(0, 1.0, 0.0, 0.0);
  triangle->GetPoints()->SetPoint(1, 0.0, 0.0, 0.0);
  triangle->GetPoints()->SetPoint(2, 0.0, 1.0, 0.0);
  triangle->GetPointIds()->SetId ( 0, 0 );
  triangle->GetPointIds()->SetId ( 1, 1 );
  triangle->GetPointIds()->SetId ( 2, 2 );

  std::cout << "The cell has " << triangle->GetNumberOfEdges()
            << " edges." << std::endl;

  for(vtkIdType i = 0; i < triangle->GetNumberOfEdges(); i++)
  {
    vtkCell* edge = triangle->GetEdge(i);

    vtkIdList* pointIdList = edge->GetPointIds();
    std::cout << "Edge " << i << " has " << pointIdList->GetNumberOfIds()
              << " points."  << std::endl;

    for(vtkIdType p = 0; p < pointIdList->GetNumberOfIds(); p++)
    {
      std::cout << "Edge " << i << " uses point " << pointIdList->GetId(p)
                << std::endl;
    }

  }


  return EXIT_SUCCESS;
}
