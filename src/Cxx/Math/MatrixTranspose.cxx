#include <vtkSmartPointer.h>
#include <vtkMatrix3x3.h>
	
int main(int, char *[])
{
  vtkSmartPointer<vtkMatrix3x3> m = 
    vtkSmartPointer<vtkMatrix3x3>::New();
  
  m->SetElement(2,1,2.0); // Set element (2,1) to 2.0
  
  std::cout << *m << std::endl;
  
  m->Transpose();
  
  std::cout << *m << std::endl;
  
  return EXIT_SUCCESS;
}
