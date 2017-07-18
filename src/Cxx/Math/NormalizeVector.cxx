#include <vtkMath.h>

int main(int, char*[])
{
  double a[3] = {100.0, 2.0, 1.0};
  std::cout << a[0] << " " << a[1] << " " << a[2] << std::endl;
  vtkMath::Normalize(a);
  std::cout << a[0] << " " << a[1] << " " << a[2] << std::endl;
  
  return EXIT_SUCCESS;
}
