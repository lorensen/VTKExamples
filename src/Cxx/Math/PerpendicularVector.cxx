#include <vtkSmartPointer.h>
#include <vtkMath.h>

int main(int, char *[])
{
  double x[3] = {1,0,0};
  double y[3];
  vtkMath::Perpendiculars(x, y, NULL, 0);

  std::cout << "y: " << y[0] << " " << y[1] << " " << y[2] << std::endl;
  
  return EXIT_SUCCESS;
}
