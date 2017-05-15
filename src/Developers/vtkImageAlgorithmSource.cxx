#include "vtkImageAlgorithmSource.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"

#include "vtkSmartPointer.h"
#include "vtkImageData.h"

vtkStandardNewMacro(vtkImageAlgorithmSource);

vtkImageAlgorithmSource::vtkImageAlgorithmSource()
{
  this->SetNumberOfOutputPorts(1);
  this->SetNumberOfInputPorts(0);
}

int vtkImageAlgorithmSource::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
    
  vtkImageData *output = vtkImageData::SafeDownCast(
      outInfo->Get(vtkDataObject::DATA_OBJECT()));
    
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  //image->SetDimensions(2,3,1);
  image->SetExtent(0, 2, 0, 3, 0, 0);
  image->SetScalarComponentFromDouble(0,0,0,0, 5.0);
  
  output->ShallowCopy(image);

  // Without these lines, the output will appear real but will not work as the input to any other filters
  output->SetExtent(image->GetExtent());
  output->SetUpdateExtent(output->GetExtent());
  output->SetWholeExtent(output->GetExtent());

  return 1;
}
