#include <vtkSmartPointer.h>

#include "vtkTestAlgorithmSource.h"
#include "vtkTest1.h"

int main(int, char *[])
{
  vtkTestAlgorithmSource* source = vtkTestAlgorithmSource::New();
  source->Update();
  
  vtkTest1* test = source->GetOutput();
  std::cout << test->GetValue() << std::endl;
  
  return EXIT_SUCCESS;
}
