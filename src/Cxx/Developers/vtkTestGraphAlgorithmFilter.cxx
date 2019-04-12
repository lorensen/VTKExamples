#include "vtkTestGraphAlgorithmFilter.h"

#include <vtkObjectFactory.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkInformationVector.h>
#include <vtkInformation.h>
#include <vtkDataObject.h>
#include <vtkSmartPointer.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkMutableGraphHelper.h>

vtkStandardNewMacro(vtkTestGraphAlgorithmFilter);

int vtkTestGraphAlgorithmFilter::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{

  // get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  // get the input and ouptut
  vtkGraph *input = dynamic_cast<vtkGraph*>(
      inInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkGraph *output = dynamic_cast<vtkGraph*>(
                                    outInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkSmartPointer<vtkMutableDirectedGraph> mdg =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();

  vtkSmartPointer<vtkMutableUndirectedGraph> mug =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  if(input->IsA("vtkMutableUndirectedGraph"))
  {
    vtkSmartPointer<vtkMutableUndirectedGraph> ug =
      vtkSmartPointer<vtkMutableUndirectedGraph>::New();
    ug->AddVertex();
    output->ShallowCopy(ug);
  }
  else if(input->IsA("vtkMutableDirectedGraph"))
  {
    vtkSmartPointer<vtkMutableDirectedGraph> dg =
      vtkSmartPointer<vtkMutableDirectedGraph>::New();
    dg->AddVertex();
    output->ShallowCopy(dg);
  }


  std::cout << "Output is type: " << output->GetClassName() << std::endl;

  return 1;
}
