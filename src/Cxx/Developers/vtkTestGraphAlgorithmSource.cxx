#include "vtkTestGraphAlgorithmSource.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"
#include "vtkMutableUndirectedGraph.h"
#include "vtkUndirectedGraph.h"
#include "vtkGraph.h"

vtkStandardNewMacro(vtkTestGraphAlgorithmSource);

vtkTestGraphAlgorithmSource::vtkTestGraphAlgorithmSource()
{
  this->SetNumberOfInputPorts(0);
  this->SetNumberOfOutputPorts(1);
}

vtkTestGraphAlgorithmSource::~vtkTestGraphAlgorithmSource()
{

}

int vtkTestGraphAlgorithmSource::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *outputVector)
{
  
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  
  vtkGraph *output = vtkGraph::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));
  
  vtkSmartPointer<vtkMutableUndirectedGraph> NewGraph =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();
    
  //add 3 vertices
  NewGraph->AddVertex();
  NewGraph->AddVertex();
  NewGraph->AddVertex();
  
  output->ShallowCopy(NewGraph);
  
  return 1;
}

int vtkTestGraphAlgorithmSource::RequestDataObject(
  vtkInformation*, 
  vtkInformationVector**, 
  vtkInformationVector* )
{

  vtkUndirectedGraph *output = 0;
  output = vtkUndirectedGraph::New();
  
  
  this->GetExecutive()->SetOutputData(0, output);
  output->Delete();

  return 1;
}

//----------------------------------------------------------------------------
void vtkTestGraphAlgorithmSource::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
