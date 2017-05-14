#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkFeatureEdges.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkFeatureEdges> featureEdges =
    vtkSmartPointer<vtkFeatureEdges>::New();
  featureEdges->FeatureEdgesOff();
  featureEdges->BoundaryEdgesOn();
  featureEdges->NonManifoldEdgesOn();
  featureEdges->SetInputConnection(sphereSource->GetOutputPort());
  featureEdges->Update();

  int numberOfOpenEdges = featureEdges->GetOutput()->GetNumberOfCells();

  if(numberOfOpenEdges > 0)
  {
    std::cout << "Surface is not closed" << std::endl;
  }
  else
  {
    std::cout << "Surface is closed" << std::endl;
  }

  return EXIT_SUCCESS;
}
