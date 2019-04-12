#include "vtkTestProgressReportFilter.h"
 
#include <vtkObjectFactory.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkInformationVector.h>
#include <vtkInformation.h>
#include <vtkDataObject.h>
#include <vtkSmartPointer.h>
 
vtkStandardNewMacro(vtkTestProgressReportFilter);

int vtkTestProgressReportFilter::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{
 
  // Get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
 
 
  // Get the input and ouptut
  vtkPolyData *input = dynamic_cast<vtkPolyData*>(
    inInfo->Get(vtkDataObject::DATA_OBJECT()));
 
  vtkPolyData *output = dynamic_cast<vtkPolyData*>(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));
 
  for(vtkIdType i = 0; i < input->GetNumberOfPoints(); i++)
  {
    this->UpdateProgress(static_cast<double>(i)/input->GetNumberOfPoints());
  }
     
  output->ShallowCopy(input);
 
  return 1;
}
