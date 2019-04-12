#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkPassThrough.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  std::cout << "Points before: " << sphereSource->GetOutput()->GetNumberOfPoints() << std::endl;
  
  vtkSmartPointer<vtkPassThrough> passThrough = 
    vtkSmartPointer<vtkPassThrough>::New();
  passThrough->SetInputConnection(sphereSource->GetOutputPort());
  passThrough->Update();
  
  vtkSmartPointer<vtkPolyData> output = dynamic_cast<vtkPolyData*>(passThrough->GetOutput());
  
  std::cout << "Points after: " << output->GetNumberOfPoints() << std::endl;
  
  return EXIT_SUCCESS;
}
