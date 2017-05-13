[VTKExamples](/home/)/[Cxx](/Cxx)/Developers/vtkTestPolyDataFilter

### Description
<source lang="cpp">

#ifndef __vtkTestPolyDataFilter_h
#define __vtkTestPolyDataFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkTestPolyDataFilter : public vtkPolyDataAlgorithm 
{
public:
  vtkTypeMacro(vtkTestPolyDataFilter,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkTestPolyDataFilter *New();
	
protected:
  vtkTestPolyDataFilter();
  ~vtkTestPolyDataFilter();
  
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestPolyDataFilter(const vtkTestPolyDataFilter&);  // Not implemented.
  void operator=(const vtkTestPolyDataFilter&);  // Not implemented.

};

#endif

</source>

**vtkTestPolyDataFilter.cxx**
```c++
#include "vtkTestPolyDataFilter.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"

vtkStandardNewMacro(vtkTestPolyDataFilter);

vtkTestPolyDataFilter::vtkTestPolyDataFilter()
{
  this->SetNumberOfInputPorts(1);
  this->SetNumberOfOutputPorts(1);
}

vtkTestPolyDataFilter::~vtkTestPolyDataFilter()
{
}

int vtkTestPolyDataFilter::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{

  // get the input and output
  vtkPolyData* input = vtkPolyData::GetData(inputVector[0],0);
  vtkPolyData* output = vtkPolyData::GetData(outputVector,0);
  
  input->GetPoints()->InsertNextPoint(1.0, 1.0, 1.0);
    
  output->ShallowCopy(input);
    
  return 1;
}

//----------------------------------------------------------------------------
void vtkTestPolyDataFilter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkTestPolyDataFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkTestPolyDataFilter MACOSX_BUNDLE vtkTestPolyDataFilter.cxx)
 
target_link_libraries(vtkTestPolyDataFilter ${VTK_LIBRARIES})
```

**Download and Build vtkTestPolyDataFilter**

Click [here to download vtkTestPolyDataFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkTestPolyDataFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkTestPolyDataFilter.tar* has been downloaded and extracted,
```
cd vtkTestPolyDataFilter/build 
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
./vtkTestPolyDataFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

