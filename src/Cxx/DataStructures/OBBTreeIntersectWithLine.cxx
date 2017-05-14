#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkLine.h>
#include <vtkOBBTree.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  // Create the locator
  vtkSmartPointer<vtkOBBTree> tree = 
    vtkSmartPointer<vtkOBBTree>::New();
  tree->SetDataSet(sphereSource->GetOutput());
  tree->BuildLocator();
  
  // Intersect the locator with the line
  double lineP0[3] = {0.0, 0.0, 0.0};
  double lineP1[3] = {0.0, 0.0, 2.0};
  vtkSmartPointer<vtkPoints> intersectPoints = 
    vtkSmartPointer<vtkPoints>::New();
  
  tree->IntersectWithLine(lineP0, lineP1, intersectPoints, NULL);

  std::cout << "NumPoints: " << intersectPoints->GetNumberOfPoints()
            << std::endl;

  // Display list of intersections
  double intersection[3];
  for(int i = 0; i < intersectPoints->GetNumberOfPoints(); i++ )
  {
    intersectPoints->GetPoint(i, intersection);
    std::cout << "Intersection " << i << ": "
              << intersection[0] << ", "
              << intersection[1] << ", "
              << intersection[2] << std::endl;
  }
  
  return EXIT_SUCCESS;
}
