#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkIdList.h>
#include <vtkKdTreePointLocator.h>

int main(int, char *[])
{
  // Setup point coordinates
  double x[3] = {1.0, 0.0, 0.0};
  double y[3] = {0.0, 1.0, 0.0};
  double z[3] = {0.0, 0.0, 1.0};

  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(x);
  points->InsertNextPoint(y);
  points->InsertNextPoint(z);
  
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
    
  // Create the tree
  vtkSmartPointer<vtkKdTreePointLocator> kDTree = 
    vtkSmartPointer<vtkKdTreePointLocator>::New();
  kDTree->SetDataSet(polydata);
  kDTree->BuildLocator();
  
  double testPoint[3] = {2.0, 0.0, 0.0};
	
  // Find the closest points to TestPoint
  vtkIdType iD = kDTree->FindClosestPoint(testPoint);
  std::cout << "The closest point is point " << iD << std::endl;
  
  //Get the coordinates of the closest point
  double closestPoint[3];
  kDTree->GetDataSet()->GetPoint(iD, closestPoint);
  std::cout << "Coordinates: " << closestPoint[0] << " " << closestPoint[1] << " " << closestPoint[2] << std::endl;
  
  return EXIT_SUCCESS;
}
