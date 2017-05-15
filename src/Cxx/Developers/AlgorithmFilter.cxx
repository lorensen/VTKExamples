#include <vtkSmartPointer.h>

#include "vtkTestAlgorithmFilter.h"
#include "vtkTest.h"

int main(int, char *[])
{
  vtkSmartPointer<vtkTest> inputTest = 
    vtkSmartPointer<vtkTest>::New();
  inputTest->SetValue(5.6);
  std::cout << "Input value: " << inputTest->GetValue() << std::endl;
  
  vtkSmartPointer<vtkTestAlgorithmFilter> filter = vtkTestAlgorithmFilter::New();
  filter->SetInput(inputTest);
  filter->Update();
  
  vtkTest* outputTest = filter->GetOutput();
  std::cout << "Output value: " << outputTest->GetValue() << std::endl;
  std::cout << "Input value is still: " << inputTest->GetValue() << std::endl;
  
  return EXIT_SUCCESS;
}
