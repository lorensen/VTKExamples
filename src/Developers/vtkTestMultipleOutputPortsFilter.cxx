#include "vtkTestMultipleOutputPortsFilter.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"

#include "vtkCubeSource.h"

vtkStandardNewMacro(vtkTestMultipleOutputPortsFilter);

vtkTestMultipleOutputPortsFilter::vtkTestMultipleOutputPortsFilter()
{
  this->SetNumberOfOutputPorts(2);
}

int vtkTestMultipleOutputPortsFilter::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{

  // get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);

  vtkInformation *outInfo0 = outputVector->GetInformationObject(0);
  vtkInformation *outInfo1 = outputVector->GetInformationObject(1);

  // get the input and ouptut
  vtkPolyData *input = vtkPolyData::SafeDownCast(
      inInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkPolyData *output0 = vtkPolyData::SafeDownCast(
    outInfo0->Get(vtkDataObject::DATA_OBJECT()));

  vtkPolyData *output1 = vtkPolyData::SafeDownCast(
    outInfo1->Get(vtkDataObject::DATA_OBJECT()));

  output0->ShallowCopy(input);

  vtkSmartPointer<vtkCubeSource> cubeSource =
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();
  
  output1->ShallowCopy(cubeSource->GetOutput());

  return 1;
}
