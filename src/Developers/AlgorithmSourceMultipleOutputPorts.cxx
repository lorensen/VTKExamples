#include <vtkSmartPointer.h>

#include "vtkTestMultipleOutputPortsSource.h"
#include "vtkTestA.h"
#include "vtkTestB.h"

int main (int argc, char *argv[])
{
  vtkTestMultipleOutputPortsSource* source = vtkTestMultipleOutputPortsSource::New();
  source->Update();
  
  vtkTestA* testa = source->GetOutputA();
  vtkTestB* testb = source->GetOutputB();
  
  std::cout << testa->GetValue() << std::endl;
  
  std::cout << testb->GetValue() << std::endl;
  
  return EXIT_SUCCESS;
}
