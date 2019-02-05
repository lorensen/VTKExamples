#include <vtkCellArray.h>
#include <vtkIdList.h>
#include <vtkKdTreePointLocator.h>
#include <vtkPointSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

int main(int, char *[]) {
  // Create some random points
  vtkSmartPointer<vtkPointSource> pointSource =
      vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(10);
  pointSource->Update();

  // Create the tree
  vtkSmartPointer<vtkKdTreePointLocator> pointTree =
      vtkSmartPointer<vtkKdTreePointLocator>::New();
  pointTree->SetDataSet(pointSource->GetOutput());
  pointTree->BuildLocator();

  // Find the k closest points to (0,0,0)
  unsigned int k = 1;
  double testPoint[3] = {0.0, 0.0, 0.0};
  vtkSmartPointer<vtkIdList> result = vtkSmartPointer<vtkIdList>::New();

  pointTree->FindClosestNPoints(k, testPoint, result);

  for (vtkIdType i = 0; i < k; i++) {
    vtkIdType point_ind = result->GetId(i);
    double p[3];
    pointSource->GetOutput()->GetPoint(point_ind, p);
    std::cout << "Closest point " << i << ": Point " << point_ind << ": ("
              << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }

  // Should return:
  // Closest point 0: Point 2: (-0.136162, -0.0276359, 0.0369441)
  
  return EXIT_SUCCESS;
}
