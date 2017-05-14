#include <vtkSmartPointer.h>
#include <vtkVector.h>

#include <iostream>

int main(int, char *[])
{
  vtkVector3d v(1.0, 2.0, 3.0);
  std::cout << v.GetX() << " " << v.GetY() << " " << v.GetZ() << std::endl;
    
  double* vals = v.GetData();
  
  std::cout << vals[0] << " " << vals[1] << " " << vals[2] << std::endl;
  
  return EXIT_SUCCESS;
}
