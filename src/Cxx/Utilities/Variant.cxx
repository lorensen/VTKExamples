#include <vtkVariant.h>

#include <iostream>
#include <string>

int main(int, char *[])
{
  double dVal = vtkVariant("2").ToDouble();
  std::cout << "dVal: " << dVal << std::endl;
  std::string strVal = vtkVariant(dVal).ToString();
  std::cout << "strVal: " << strVal << std::endl;
  return EXIT_SUCCESS;
}
