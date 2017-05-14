#include "vtkTestClass2.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"

vtkStandardNewMacro(vtkTestClass);

vtkTestClass::vtkTestClass()
{
  this->SetNumberOfInputPorts(0);
}

int vtkTestClass::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *vtkNotUsed(outputVector))
{
  std::cout << "some output" << std::endl;

  int value = 3;
  vtkDebugMacro(<<"Value is: " << value);

  return 1;
}
