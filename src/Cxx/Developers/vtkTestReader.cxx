#include <vtkTestReader.h>

#include <vtkObjectFactory.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkInformationVector.h>
#include <vtkInformation.h>
#include <vtkDataObject.h>
#include <vtkNew.h>

vtkStandardNewMacro(vtkTestReader);

vtkTestReader::vtkTestReader()
{
  this->FileName = NULL;
  this->SetNumberOfInputPorts(0);
  this->SetNumberOfOutputPorts(1);
}

vtkTestReader::~vtkTestReader()
{

}

// This override is not needed as the FillOutputPortInformation on vtkPolyDataAlgorithm
// does this.  Override this if you need something different from one output that
// is a vtkPolyData
int vtkTestReader::FillOutputPortInformation( int port, vtkInformation* info )
{
  if ( port == 0 )
  {
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData" );
    
    return 1;
  }

  return 0;
}

int vtkTestReader::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *outputVector)
{

  // Get the output
  vtkPolyData *output = vtkPolyData::GetData(outputVector,0)
  
  vtkNew<vtkPolyData> polydata;
  vtkNew<vtkPoints> points;
  points->InsertNextPoint(0.0, 0.0, 0.0);
  polydata->SetPoints(points.GetPointer());
  
  //output = polydata.GetPointer(); //doesn't work
  output->ShallowCopy(polydata.GetPointer());
    
  return 1;
}


//----------------------------------------------------------------------------
void vtkTestReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "File Name: " 
      << (this->FileName ? this->FileName : "(none)") << "\n";	
}
