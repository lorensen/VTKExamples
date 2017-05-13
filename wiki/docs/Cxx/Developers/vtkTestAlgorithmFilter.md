[VTKExamples](Home)/[Cxx](Cxx)/Developers/vtkTestAlgorithmFilter

### Description
<source lang="cpp">
#ifndef __vtkTestAlgorithmFilter_h
#define __vtkTestAlgorithmFilter_h

#include "vtkAlgorithm.h"

class vtkDataSet;
class vtkTest;

class vtkTestAlgorithmFilter : public vtkAlgorithm
{
  public:
    static vtkTestAlgorithmFilter *New();
    vtkTypeMacro(vtkTestAlgorithmFilter,vtkAlgorithm);
    void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get the output data object for a port on this algorithm.
    vtkTest* GetOutput();
    vtkTest* GetOutput(int);
    virtual void SetOutput(vtkDataObject* d);

  // Description:
  // see vtkAlgorithm for details
    virtual int ProcessRequest(vtkInformation*,
                               vtkInformationVector**,
                               vtkInformationVector*);

  // this method is not recommended for use, but lots of old style filters use it
    vtkDataObject* GetInput();
    vtkDataObject* GetInput(int port);
    vtkTest* GetLabelHierarchyInput(int port);

  // Description:
  // Set an input of this algorithm. You should not override these
  // methods because they are not the only way to connect a pipeline.
  // Note that these methods support old-style pipeline connections.
  // When writing new code you should use the more general
  // vtkAlgorithm::SetInputConnection().  These methods transform the
  // input index to the input port index, not an index of a connection
  // within a single port.
    void SetInput( vtkDataObject* );
    void SetInput( int, vtkDataObject* );

  // Description:
  // Add an input of this algorithm.  Note that these methods support
  // old-style pipeline connections.  When writing new code you should
  // use the more general vtkAlgorithm::AddInputConnection().  See
  // SetInput() for details.
    void AddInput( vtkDataObject* );
    void AddInput( int, vtkDataObject* );

  protected:
    vtkTestAlgorithmFilter();
    ~vtkTestAlgorithmFilter();

  // Description:
  // This is called by the superclass.
  // This is the method you should override.
    virtual int RequestDataObject(
                                  vtkInformation* request,
                                  vtkInformationVector** inputVector,
                                  vtkInformationVector* outputVector );

  // convenience method
    virtual int RequestInformation(
                                   vtkInformation* request,
                                   vtkInformationVector** inputVector,
                                   vtkInformationVector* outputVector );

  // Description:
  // This is called by the superclass.
  // This is the method you should override.
    virtual int RequestData(
                            vtkInformation* request,
                            vtkInformationVector** inputVector,
                            vtkInformationVector* outputVector );

  // Description:
  // This is called by the superclass.
  // This is the method you should override.
    virtual int RequestUpdateExtent(
                                    vtkInformation*,
                                    vtkInformationVector**,
                                    vtkInformationVector* );

    virtual int FillOutputPortInformation( int port, vtkInformation* info );
    virtual int FillInputPortInformation( int port, vtkInformation* info );
    
  private:
    vtkTestAlgorithmFilter( const vtkTestAlgorithmFilter& ); // Not implemented.
    void operator = ( const vtkTestAlgorithmFilter& );  // Not implemented.
};

#endif
</source>

**vtkTestAlgorithmFilter.cxx**
```c++
#include "vtkTestAlgorithmFilter.h"
#include "vtkTest.h"

#include "vtkCommand.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"

vtkStandardNewMacro(vtkTestAlgorithmFilter);

//----------------------------------------------------------------------------
vtkTestAlgorithmFilter::vtkTestAlgorithmFilter()
{
  this->SetNumberOfInputPorts( 1 );
  this->SetNumberOfOutputPorts( 1 );
}

//----------------------------------------------------------------------------
vtkTestAlgorithmFilter::~vtkTestAlgorithmFilter()
{
}

//----------------------------------------------------------------------------
void vtkTestAlgorithmFilter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
vtkTest* vtkTestAlgorithmFilter::GetOutput()
{
  return this->GetOutput(0);
}

//----------------------------------------------------------------------------
vtkTest* vtkTestAlgorithmFilter::GetOutput(int port)
{
  return vtkTest::SafeDownCast(this->GetOutputDataObject(port));
}

//----------------------------------------------------------------------------
void vtkTestAlgorithmFilter::SetOutput(vtkDataObject* d)
{
  this->GetExecutive()->SetOutputData(0, d);
}

//----------------------------------------------------------------------------
vtkDataObject* vtkTestAlgorithmFilter::GetInput()
{
  return this->GetInput(0);
}

//----------------------------------------------------------------------------
vtkDataObject* vtkTestAlgorithmFilter::GetInput(int port)
{
  return this->GetExecutive()->GetInputData(port, 0);
}

//----------------------------------------------------------------------------
vtkTest* vtkTestAlgorithmFilter::GetLabelHierarchyInput(int port)
{
  return vtkTest::SafeDownCast(this->GetInput(port));
}

//----------------------------------------------------------------------------
int vtkTestAlgorithmFilter::ProcessRequest(vtkInformation* request,
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
int vtkTestAlgorithmFilter::FillOutputPortInformation(
    int vtkNotUsed(port), vtkInformation* info)
{
  // now add our info
  info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkTest");
  return 1;
}

//----------------------------------------------------------------------------
int vtkTestAlgorithmFilter::FillInputPortInformation(
                                               int vtkNotUsed(port), vtkInformation* info)
{
  info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkTest");
  return 1;
}


    int vtkTestAlgorithmFilter::RequestDataObject(vtkInformation* vtkNotUsed(request),
                                         vtkInformationVector** vtkNotUsed(inputVector),
         vtkInformationVector* outputVector )
    {
//RequestDataObject (RDO) is an earlier pipeline pass.
//During RDO, each filter is supposed to produce an empty data object of the proper type

  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  vtkTest* output = vtkTest::SafeDownCast(
    outInfo->Get( vtkDataObject::DATA_OBJECT() ) );

  if ( ! output )
  {
    output = vtkTest::New();
    outInfo->Set( vtkDataObject::DATA_OBJECT(), output );
    output->FastDelete();

    this->GetOutputPortInformation(0)->Set(
      vtkDataObject::DATA_EXTENT_TYPE(), output->GetExtentType() );
  }

  return 1;
    }


//----------------------------------------------------------------------------
int vtkTestAlgorithmFilter::RequestInformation(
                                         vtkInformation* vtkNotUsed(request),
    vtkInformationVector** vtkNotUsed(inputVector),
                                      vtkInformationVector* vtkNotUsed(outputVector))
{
  // do nothing let subclasses handle it
  return 1;
}

//----------------------------------------------------------------------------
int vtkTestAlgorithmFilter::RequestUpdateExtent(
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
int vtkTestAlgorithmFilter::RequestData(
                                  vtkInformation* vtkNotUsed(request),
    vtkInformationVector **inputVector,
    vtkInformationVector* outputVector )
{
//Later on RequestData (RD) happens.
//During RD each filter examines any inputs it has, then fills in that empty data object with real data.

  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  vtkTest* output = vtkTest::SafeDownCast(
                                          outInfo->Get( vtkDataObject::DATA_OBJECT() ) );

  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkTest *input = vtkTest::SafeDownCast(
                                         inInfo->Get(vtkDataObject::DATA_OBJECT()));
  output->ShallowCopy(input);
  output->SetValue(output->GetValue() + 1.0);

  return 1;
}

//----------------------------------------------------------------------------
void vtkTestAlgorithmFilter::SetInput(vtkDataObject* input)
{
  this->SetInput(0, input);
}

//----------------------------------------------------------------------------
void vtkTestAlgorithmFilter::SetInput(int index, vtkDataObject* input)
{
  if(input)
  {
    this->SetInputDataObject(index, input);
  }
  else
  {
    // Setting a NULL input removes the connection.
    this->SetInputDataObject(index, 0);
  }
}

//----------------------------------------------------------------------------
void vtkTestAlgorithmFilter::AddInput(vtkDataObject* input)
{
  this->AddInput(0, input);
}

//----------------------------------------------------------------------------
void vtkTestAlgorithmFilter::AddInput(int index, vtkDataObject* input)
{
  if(input)
  {
    this->AddInputDataObject(index, input);
  }
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkTestAlgorithmFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkTestAlgorithmFilter MACOSX_BUNDLE vtkTestAlgorithmFilter.cxx)
 
target_link_libraries(vtkTestAlgorithmFilter ${VTK_LIBRARIES})
```

**Download and Build vtkTestAlgorithmFilter**

Click [here to download vtkTestAlgorithmFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkTestAlgorithmFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkTestAlgorithmFilter.tar* has been downloaded and extracted,
```
cd vtkTestAlgorithmFilter/build 
```
If VTK is installed:
```
cmake ..
```
If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build:
```
cmake -DVTK_DIR:PATH=/home/me/vtk_build ..
```
Build the project:
```
make
```
and run it:
```
./vtkTestAlgorithmFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

