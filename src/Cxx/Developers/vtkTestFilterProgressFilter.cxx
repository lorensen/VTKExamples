#include <vtkSmartPointer.h>

#include <vtkObjectFactory.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkInformationVector.h>
#include <vtkInformation.h>
#include <vtkDataObject.h>
#include <vtkCallbackCommand.h>

#include "vtkTestFilterProgressFilter.h"

vtkStandardNewMacro(vtkTestFilterProgressFilter);

vtkTestFilterProgressFilter::vtkTestFilterProgressFilter()
{
  vtkSmartPointer<vtkCallbackCommand> progressCallback =
      vtkSmartPointer<vtkCallbackCommand>::New();
  progressCallback->SetCallback(this->ProgressFunction);

  this->AddObserver(vtkCommand::ProgressEvent, progressCallback);
}

void vtkTestFilterProgressFilter::ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData)
{
  vtkTestFilterProgressFilterr* testFilter = static_cast<vtkTestFilterProgressFilter*>(caller);
  cout << "Progress: " << testFilter->GetProgress() << endl;
}

int vtkTestFilterProgressFilter::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{

  // get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);


  // get the input and ouptut
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
