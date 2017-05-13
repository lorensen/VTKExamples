[VTKExamples](/index/)/[Cxx](/Cxx)/Developers/vtkTestAlgorithmSource

### Description
<source lang="cpp">
#ifndef __vtkTestAlgorithmSource_h
#define __vtkTestAlgorithmSource_h

#include "vtkAlgorithm.h"

class vtkDataSet;
class vtkTest1;

class vtkTestAlgorithmSource : public vtkAlgorithm
{
public:
  static vtkTestAlgorithmSource *New();
  vtkTypeMacro(vtkTestAlgorithmSource,vtkAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get the output data object for a port on this algorithm.
  vtkTest1* GetOutput();
  vtkTest1* GetOutput(int);
  virtual void SetOutput(vtkDataObject* d);

  // Description:
  // see vtkAlgorithm for details
  virtual int ProcessRequest(vtkInformation*,
                             vtkInformationVector**,
                             vtkInformationVector*);

protected:
  vtkTestAlgorithmSource();
  ~vtkTestAlgorithmSource();

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

private:
  vtkTestAlgorithmSource( const vtkTestAlgorithmSource& ); // Not implemented.
  void operator = ( const vtkTestAlgorithmSource& );  // Not implemented.
};

#endif
</source>

**vtkTestAlgorithmSource.cxx**
```c++
#include "vtkTestAlgorithmSource.h"
#include "vtkTest1.h"

#include "vtkCommand.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"

vtkStandardNewMacro(vtkTestAlgorithmSource);

//----------------------------------------------------------------------------
vtkTestAlgorithmSource::vtkTestAlgorithmSource()
{
  this->SetNumberOfInputPorts( 0 );
  this->SetNumberOfOutputPorts( 1 );
}

//----------------------------------------------------------------------------
vtkTestAlgorithmSource::~vtkTestAlgorithmSource()
{
}

//----------------------------------------------------------------------------
void vtkTestAlgorithmSource::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
vtkTest1* vtkTestAlgorithmSource::GetOutput()
{
  return this->GetOutput(0);
}

//----------------------------------------------------------------------------
vtkTest1* vtkTestAlgorithmSource::GetOutput(int port)
{
  return vtkTest1::SafeDownCast(this->GetOutputDataObject(port));
}

//----------------------------------------------------------------------------
void vtkTestAlgorithmSource::SetOutput(vtkDataObject* d)
{
  this->GetExecutive()->SetOutputData(0, d);
}


//----------------------------------------------------------------------------
int vtkTestAlgorithmSource::ProcessRequest(vtkInformation* request,
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
int vtkTestAlgorithmSource::FillOutputPortInformation(
    int vtkNotUsed(port), vtkInformation* info)
{
  // now add our info
  info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkTest1");
  return 1;
}


//----------------------------------------------------------------------------
int vtkTestAlgorithmSource::RequestDataObject(
                                        vtkInformation* vtkNotUsed(request),
    vtkInformationVector** vtkNotUsed(inputVector),
                                      vtkInformationVector* outputVector )
{
  for ( int i = 0; i < this->GetNumberOfOutputPorts(); ++i )
  {
    vtkInformation* outInfo = outputVector->GetInformationObject( i );
    vtkTest1* output = vtkTest1::SafeDownCast(
                                            outInfo->Get( vtkDataObject::DATA_OBJECT() ) );
    if ( ! output )
    {
      output = vtkTest1::New();
      outInfo->Set( vtkDataObject::DATA_OBJECT(), output );
      output->FastDelete();
      this->GetOutputPortInformation( i )->Set(
                                      vtkDataObject::DATA_EXTENT_TYPE(), output->GetExtentType() );
    }
  }
  return 1;
}

//----------------------------------------------------------------------------
int vtkTestAlgorithmSource::RequestInformation(
                                         vtkInformation* vtkNotUsed(request),
    vtkInformationVector** vtkNotUsed(inputVector),
                                      vtkInformationVector* vtkNotUsed(outputVector))
{
  // do nothing let subclasses handle it
  return 1;
}

//----------------------------------------------------------------------------
int vtkTestAlgorithmSource::RequestUpdateExtent(
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
int vtkTestAlgorithmSource::RequestData(
                                  vtkInformation* vtkNotUsed(request),
    vtkInformationVector** vtkNotUsed( inputVector ),
                                       vtkInformationVector* vtkNotUsed(outputVector) )
{
  // do nothing let subclasses handle it
  return 1;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkTestAlgorithmSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkTestAlgorithmSource MACOSX_BUNDLE vtkTestAlgorithmSource.cxx)
 
target_link_libraries(vtkTestAlgorithmSource ${VTK_LIBRARIES})
```

**Download and Build vtkTestAlgorithmSource**

Click [here to download vtkTestAlgorithmSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkTestAlgorithmSource.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkTestAlgorithmSource.tar* has been downloaded and extracted,
```
cd vtkTestAlgorithmSource/build 
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
./vtkTestAlgorithmSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

