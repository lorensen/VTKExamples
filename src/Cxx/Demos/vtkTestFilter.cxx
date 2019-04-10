#include <vtkTestFilter.h>

#include <vtkObjectFactory.h>
#include <vtkCommand.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkInformationVector.h>
#include <vtkInformation.h>
#include <vtkDataObject.h>
#include <vtkSmartPointer.h>
#include <vtkAppendPolyData.h>
#include <vtkSphereSource.h>

vtkStandardNewMacro(vtkTestFilter);

vtkTestFilter::vtkTestFilter()
{
  this->SetNumberOfInputPorts(0);
  this->Output = vtkSmartPointer<vtkPolyData>::New();

  this->RefreshEvent = vtkCommand::UserEvent + 1;

}

int vtkTestFilter::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{
  // Get the info object
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  vtkPolyData *output = dynamic_cast<vtkPolyData*>(
      outInfo->Get(vtkDataObject::DATA_OBJECT()));

  this->Output->DeepCopy(output);

  for(unsigned int i = 0; i < 10; i++)
  {
    Iterate(i);
    this->InvokeEvent(this->RefreshEvent, NULL);
  }

  output->ShallowCopy(this->Output);

  return 1;
}

void vtkTestFilter::Iterate(unsigned int iteration)
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(iteration, 0, 0);
  sphereSource->SetRadius(0.2);
  sphereSource->Update();

  vtkSmartPointer<vtkAppendPolyData> appendFilter =
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendFilter->AddInputConnection(this->Output->GetProducerPort());
  appendFilter->AddInputConnection(sphereSource->GetOutputPort());
  appendFilter->Update();

  this->Output->DeepCopy(appendFilter->GetOutput());
}
