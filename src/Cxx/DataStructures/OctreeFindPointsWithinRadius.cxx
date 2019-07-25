#include <vtkCellArray.h>
#include <vtkIdList.h>
#include <vtkOctreePointLocator.h>
#include <vtkPointSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

int main(int, char*[])
{
  // Create some random points
  auto pointSource = vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(10);
  pointSource->Update();

  // Create the tree
  auto octree = vtkSmartPointer<vtkOctreePointLocator>::New();
  octree->SetDataSet(pointSource->GetOutput());
  octree->BuildLocator();

  // Find the k closest points to (0,0,0)
  vtkIdType k = 1;
  double testPoint[3] = {0.0, 0.0, 0.0};
  auto result = vtkSmartPointer<vtkIdList>::New();

  octree->FindPointsWithinRadius(1.0, testPoint, result);

  for (vtkIdType i = 0; i < k; i++)
  {
    vtkIdType point_ind = result->GetId(i);
    double p[3];
    pointSource->GetOutput()->GetPoint(point_ind, p);
    std::cout << "Closest point " << i << ": Point " << point_ind << ": ("
              << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }

  return EXIT_SUCCESS;
}
