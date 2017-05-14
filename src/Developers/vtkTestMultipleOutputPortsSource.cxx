#include "vtkTestMultipleOutputPortsSource.h"
#include "vtkTestA.h"
#include "vtkTestB.h"

#include "vtkCommand.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"

vtkCxxRevisionMacro(vtkTestMultipleOutputPortsSource, "$Revision: 1.1 $");
vtkStandardNewMacro(vtkTestMultipleOutputPortsSource);

//----------------------------------------------------------------------------
vtkTestMultipleOutputPortsSource::vtkTestMultipleOutputPortsSource()
{
  this->SetNumberOfInputPorts( 0 );
  this->SetNumberOfOutputPorts( 2 );
}

//----------------------------------------------------------------------------
vtkTestMultipleOutputPortsSource::~vtkTestMultipleOutputPortsSource()
{
}

//----------------------------------------------------------------------------
void vtkTestMultipleOutputPortsSource::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
vtkTestA* vtkTestMultipleOutputPortsSource::GetOutputA()
{
  return vtkTestA::SafeDownCast(this->GetOutputDataObject(0));
}

//----------------------------------------------------------------------------
vtkTestB* vtkTestMultipleOutputPortsSource::GetOutputB()
{
  return vtkTestB::SafeDownCast(this->GetOutputDataObject(1));
}


//----------------------------------------------------------------------------
void vtkTestMultipleOutputPortsSource::SetOutput(vtkDataObject* d)
{
  this->GetExecutive()->SetOutputData(0, d);
}


//----------------------------------------------------------------------------
int vtkTestMultipleOutputPortsSource::ProcessRequest(vtkInformation* request,
                                     vtkInformationVector** inputVector,
                                     vtkInformationVector* outputVector)
{
  // Create an output object of the correct type.
  if(request->Has(vtkDemandDrivenPipeline::REQUEST_DATA_OBJECT()))
  {
    return this->RequestDataObject(request, inputVector, outputVector);
  }
  // generate the data
  if(request->Has(vtkDemandDrivenPipeline::REQUEST_DATA()))
  {
    return this->RequestData(request, inputVector, outputVector);
  }

  if(request->Has(vtkStreamingDemandDrivenPipeline::REQUEST_UPDATE_EXTENT()))
  {
    return this->RequestUpdateExtent(request, inputVector, outputVector);
  }

  // execute information
  if(request->Has(vtkDemandDrivenPipeline::REQUEST_INFORMATION()))
  {
    return this->RequestInformation(request, inputVector, outputVector);
  }

  return this->Superclass::ProcessRequest(request, inputVector, outputVector);
}

//----------------------------------------------------------------------------
int vtkTestMultipleOutputPortsSource::FillOutputPortInformation(int port, vtkInformation* info)
{
  // now add our info
  if(port == 0)
  {
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkTestA");
  }
  else if(port == 1)
  {
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkTestB");
  }

  return 1;
}


//----------------------------------------------------------------------------
int vtkTestMultipleOutputPortsSource::RequestDataObject(
                                        vtkInformation* vtkNotUsed(request),
    vtkInformationVector** vtkNotUsed(inputVector),
                                      vtkInformationVector* outputVector )
{
  //output 0 - TestA
  vtkInformation* outInfoA = outputVector->GetInformationObject(0);
  vtkTestA* outputA = vtkTestA::SafeDownCast(
                                          outInfoA->Get( vtkDataObject::DATA_OBJECT() ) );
  if ( ! outputA )
  {
    outputA = vtkTestA::New();
    outInfoA->Set( vtkDataObject::DATA_OBJECT(), outputA );
    outputA->FastDelete();
    outputA->SetPipelineInformation( outInfoA );
    this->GetOutputPortInformation(0)->Set(
                                    vtkDataObject::DATA_EXTENT_TYPE(), outputA->GetExtentType() );
  }

  //output 1 - TestB
  vtkInformation* outInfoB = outputVector->GetInformationObject(1);
  vtkTestB* outputB = vtkTestB::SafeDownCast(
                                              outInfoB->Get( vtkDataObject::DATA_OBJECT() ) );
  if ( ! outputB )
  {
    outputB = vtkTestB::New();
    outInfoB->Set( vtkDataObject::DATA_OBJECT(), outputB );
    outputB->FastDelete();
    outputB->SetPipelineInformation( outInfoB );
    this->GetOutputPortInformation(1)->Set(
                                    vtkDataObject::DATA_EXTENT_TYPE(), outputB->GetExtentType() );
  }

  return 1;
}

//----------------------------------------------------------------------------
int vtkTestMultipleOutputPortsSource::RequestInformation(
                                         vtkInformation* vtkNotUsed(request),
    vtkInformationVector** vtkNotUsed(inputVector),
                                      vtkInformationVector* vtkNotUsed(outputVector))
{
  // do nothing let subclasses handle it
  return 1;
}

//----------------------------------------------------------------------------
int vtkTestMultipleOutputPortsSource::RequestUpdateExtent(
                                          vtkInformation* vtkNotUsed(request),
    vtkInformationVector** inputVector,
    vtkInformationVector* vtkNotUsed(outputVector))
{
  int numInputPorts = this->GetNumberOfInputPorts();
  for (int i=0; i<numInputPorts; i++)
  {
    int numInputConnections = this->GetNumberOfInputConnections(i);
    for (int j=0; j<numInputConnections; j++)
    {
      vtkInformation* inputInfo = inputVector[i]->GetInformationObject(j);
      inputInfo->Set(vtkStreamingDemandDrivenPipeline::EXACT_EXTENT(), 1);
    }
  }
  return 1;
}

//----------------------------------------------------------------------------
// This is the superclasses style of Execute method.  Convert it into
// an imaging style Execute method.
int vtkTestMultipleOutputPortsSource::RequestData(
                                  vtkInformation* vtkNotUsed(request),
    vtkInformationVector** vtkNotUsed( inputVector ),
                                       vtkInformationVector* outputVector )
{
  //actually setup the output here
  vtkInformation* outInfoA = outputVector->GetInformationObject(0);
  vtkTestA* outputA = vtkTestA::SafeDownCast(
                                          outInfoA->Get( vtkDataObject::DATA_OBJECT() ) );

  outputA->SetValue(111);

  vtkInformation* outInfoB = outputVector->GetInformationObject(1);
  vtkTestB* outputB = vtkTestB::SafeDownCast(
                                             outInfoB->Get( vtkDataObject::DATA_OBJECT() ) );

  outputB->SetValue(222);

  return 1;
}
