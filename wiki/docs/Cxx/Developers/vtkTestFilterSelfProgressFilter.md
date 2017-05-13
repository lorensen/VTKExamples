[VTKExamples](/index/)/[Cxx](/Cxx)/Developers/vtkTestFilterSelfProgressFilter

### Description
<source lang="cpp">
#ifndef __vtkTestFilterSelfProgressFilter_h
#define __vtkTestFilterSelfProgressFilter_h
 
#include "vtkPolyDataAlgorithm.h"
 
class vtkTestFilterSelfProgressFilter : public vtkPolyDataAlgorithm 
{
public:
  vtkTypeMacro(vtkTestFilterSelfProgressFilter,vtkAlgorithm);
  
  static vtkTestFilterSelfProgressFilter *New();
 
protected:
  vtkTestFilterSelfProgressFilter();
  ~vtkTestFilterSelfProgressFilter(){}
 
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) VTK_OVERRIDE; 
 
  static void ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);
  
private:
  vtkTestFilterSelfProgressFilter(const vtkTestFilterSelfProgressFilter&);  // Not implemented.
  void operator=(const vtkTestFilterSelfProgressFilter&);  // Not implemented.
 
};
 
#endif
</source>

**vtkTestFilterSelfProgressFilter.cxx**
```c++
#include "vtkSmartPointer.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkCallbackCommand.h"

#include "vtkTestFilterSelfProgressFilter.h"

vtkStandardNewMacro(vtkTestFilterSelfProgressFilter);

vtkTestFilterSelfProgressFilter::vtkTestFilterSelfProgressFilter()
{
  vtkSmartPointer<vtkCallbackCommand> progressCallback =
      vtkSmartPointer<vtkCallbackCommand>::New();
  progressCallback->SetCallback(this->ProgressFunction);

  this->AddObserver(vtkCommand::ProgressEvent, progressCallback);
}

void vtkTestFilterSelfProgressFilter::ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData)
{
  vtkTestFilterSelfProgressFilter* testFilter = static_cast<vtkTestFilterSelfProgressFilter*>(caller);
  cout << "Progress: " << testFilter->GetProgress() << endl;
}

int vtkTestFilterSelfProgressFilter::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{

  // get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);


  // get the input and ouptut
  vtkPolyData *input = vtkPolyData::SafeDownCast(
      inInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkPolyData *output = vtkPolyData::SafeDownCast(
      outInfo->Get(vtkDataObject::DATA_OBJECT()));

  for(vtkIdType i = 0; i < input->GetNumberOfPoints(); i++)
  {
    this->UpdateProgress(static_cast<double>(i)/input->GetNumberOfPoints());
  }

  output->ShallowCopy(input);

  return 1;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkTestFilterSelfProgressFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkTestFilterSelfProgressFilter MACOSX_BUNDLE vtkTestFilterSelfProgressFilter.cxx)
 
target_link_libraries(vtkTestFilterSelfProgressFilter ${VTK_LIBRARIES})
```

**Download and Build vtkTestFilterSelfProgressFilter**

Click [here to download vtkTestFilterSelfProgressFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkTestFilterSelfProgressFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkTestFilterSelfProgressFilter.tar* has been downloaded and extracted,
```
cd vtkTestFilterSelfProgressFilter/build 
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
./vtkTestFilterSelfProgressFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

