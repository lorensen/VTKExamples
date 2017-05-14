#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkModifiedBSPTree.h>
#include <vtkSphereSource.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  // Create the tree
  vtkSmartPointer<vtkModifiedBSPTree> bspTree =
    vtkSmartPointer<vtkModifiedBSPTree>::New();
  bspTree->SetDataSet(sphereSource->GetOutput());
  bspTree->BuildLocator();

  // Inputs
  double p1[3] = {-2,0,0};
  double p2[3] = {2,0,0};
  double tolerance = .001;
  
  // Outputs
  double t; // Parametric coordinate of intersection (0 (corresponding to p1) to 1 (corresponding to p2))
  double x[3]; // The coordinate of the intersection
  double pcoords[3];
  int subId;
  
  // Note: for a typical use case (ray-triangle intersection), pcoords and subId will not be used
  vtkIdType iD = bspTree->IntersectWithLine(p1, p2, tolerance, t, x, pcoords, subId);

  std::cout << "iD: " << iD << std::endl;
  std::cout << "t: " << t << std::endl;
  std::cout << "x: " << x[0] << " " << x[1] << " " << x[2] << std::endl;
  
  return EXIT_SUCCESS;
}
