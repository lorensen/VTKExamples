[VTKExamples](/index/)/[Cxx](/Cxx)/Developers/vtkTestGraphAlgorithmSource

### Description
<source lang="cpp">
#ifndef __vtkTestGraphAlgorithmSource_h
#define __vtkTestGraphAlgorithmSource_h

#include "vtkGraphAlgorithm.h"

class vtkTestGraphAlgorithmSource : public vtkGraphAlgorithm 
{
public:
  static vtkTestGraphAlgorithmSource *New();
  vtkTypeMacro(vtkTestGraphAlgorithmSource,vtkGraphAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);
	
protected:
  vtkTestGraphAlgorithmSource();
  ~vtkTestGraphAlgorithmSource();
  
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  
  int RequestDataObject(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestGraphAlgorithmSource(const vtkTestGraphAlgorithmSource&);  // Not implemented.
  void operator=(const vtkTestGraphAlgorithmSource&);  // Not implemented.

};

#endif
</source>

**vtkTestGraphAlgorithmSource.cxx**
```c++
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
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkTestGraphAlgorithmSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkTestGraphAlgorithmSource MACOSX_BUNDLE vtkTestGraphAlgorithmSource.cxx)
 
target_link_libraries(vtkTestGraphAlgorithmSource ${VTK_LIBRARIES})
```

**Download and Build vtkTestGraphAlgorithmSource**

Click [here to download vtkTestGraphAlgorithmSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkTestGraphAlgorithmSource.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkTestGraphAlgorithmSource.tar* has been downloaded and extracted,
```
cd vtkTestGraphAlgorithmSource/build 
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
./vtkTestGraphAlgorithmSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

