#include <vtkSmartPointer.h>

#include "vtkTestClass3.h"

int main(int, char*[])
{
  vtkSmartPointer<vtkTestClass> testClass =
    vtkSmartPointer<vtkTestClass>::New();
  testClass->Update();
  
  double test[3];
  testClass->SetTestVector(test);

  double testOut[3];
  testClass->GetTestVector(test);
  
  return EXIT_SUCCESS;
}
