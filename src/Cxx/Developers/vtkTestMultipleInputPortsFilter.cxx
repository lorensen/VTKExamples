#include "vtkTestMultipleInputPortsFilter.h"

#include <vtkObjectFactory.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkInformationVector.h>
#include <vtkInformation.h>
#include <vtkDataObject.h>
#include <vtkSmartPointer.h>

vtkStandardNewMacro(vtkTestMultipleInputPortsFilter);

vtkTestMultipleInputPortsFilter::vtkTestMultipleInputPortsFilter()
{
  this->SetNumberOfInputPorts(2);
}

int vtkTestMultipleInputPortsFilter::FillInputPortInformation( int port, vtkInformation* info )
{
  if ( port == 0 )
  {
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData" );
    return 1;
  }
  else if(port == 1)
  {
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData" );
    return 1;
  }

  return 0;
}

int vtkTestMultipleInputPortsFilter::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{

  // get the info objects
  vtkInformation *inInfo0 = inputVector[0]->GetInformationObject(0);
  vtkInformation *inInfo1 = inputVector[1]->GetInformationObject(0);

  vtkInformation *outInfo = outputVector->GetInformationObject(0);


  // get the input and ouptut
  vtkPolyData *input0 = vtkPolyData::SafeDownCast(
      inInfo0->Get(vtkDataObject::DATA_OBJECT()));

  std::cout << "input0 has " << input0->GetNumberOfPoints() << " points." << std::endl;

  vtkPolyData *input1 = vtkPolyData::SafeDownCast(
      inInfo1->Get(vtkDataObject::DATA_OBJECT()));

  std::cout << "input1 has " << input1->GetNumberOfPoints() << " points." << std::endl;

  vtkPolyData *output = vtkPolyData::SafeDownCast(
      outInfo->Get(vtkDataObject::DATA_OBJECT()));

  output->ShallowCopy(input0);

  return 1;
}
