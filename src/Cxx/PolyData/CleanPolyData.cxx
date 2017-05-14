#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkPolyData.h>
#include <vtkCleanPolyData.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkCubeSource> cubeSource = 
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();
  
  std::cout << "Input cube has " << cubeSource->GetOutput()->GetNumberOfPoints() 
    << " vertices." << std::endl;
    
  vtkSmartPointer<vtkCleanPolyData> cleanPolyData = 
      vtkSmartPointer<vtkCleanPolyData>::New();
  cleanPolyData->SetInputConnection(cubeSource->GetOutputPort());
  cleanPolyData->Update();
  
  std::cout << "Cleaned cube has " << cleanPolyData->GetOutput()->GetNumberOfPoints() 
    << " vertices." << std::endl;
  
  return EXIT_SUCCESS;
}
