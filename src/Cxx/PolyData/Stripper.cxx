#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkStripper.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  std::cout << "Number of cells before stripping: " << sphereSource->GetOutput()->GetNumberOfCells() << std::endl;
  
  vtkSmartPointer<vtkStripper> stripper = 
      vtkSmartPointer<vtkStripper>::New();
  stripper->SetInputConnection(sphereSource->GetOutputPort());
  stripper->Update();
  
  std::cout << "Number of cells after stripping: " << stripper->GetOutput()->GetNumberOfCells() << std::endl;
  
  return EXIT_SUCCESS;
}
