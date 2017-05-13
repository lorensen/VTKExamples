[VTKExamples](/home/)/[Cxx](/Cxx)/Developers/vtkTestFilterProgressFilter

### Description
<source lang="cpp">
#ifndef __vtkTestFilterProgressFilter_h
#define __vtkTestFilterProgressFilter_h
 
#include "vtkPolyDataAlgorithm.h"
 
class vtkTestFilterProgressFilter : public vtkPolyDataAlgorithm 
{
public:
  static vtkTestFilterProgressFilter *New();
  vtkTypeMacro(vtkTestFilterProgressFilter,vtkAlgorithm);

protected:
  vtkTestFilterProgressFilterr();
  ~vtkTestFilterProgressFilter() VTK_OVERRIDE {}
 
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) VTK_OVERRIDE; 
 
  static void ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);
  
private:
  vtkTestFilterProgressFilter(const vtkTestFilterProgressFilter&) VTK_DELETE_FUNCTION;
  void operator=(const vtkTestFilterProgressFilterr&) VTK_DELETE_FUNCTION;
 
};

#endif
</source>

**vtkTestFilterProgressFilter.cxx**
```c++
#include "vtkSmartPointer.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkCallbackCommand.h"

#include "vtkTestFilterProgressFilter.h"

vtkStandardNewMacro(vtkTestFilterProgressFilter);

vtkTestFilterProgressFilter::vtkTestFilterProgressFilter()
{
  vtkSmartPointer<vtkCallbackCommand> progressCallback =
      vtkSmartPointer<vtkCallbackCommand>::New();
  progressCallback->SetCallback(this->ProgressFunction);

  this->AddObserver(vtkCommand::ProgressEvent, progressCallback);
}

void vtkTestFilterProgressFilter::ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData)
{
  vtkTestFilterProgressFilterr* testFilter = static_cast<vtkTestFilterProgressFilter*>(caller);
  cout << "Progress: " << testFilter->GetProgress() << endl;
}

int vtkTestFilterProgressFilter::RequestData(vtkInformation *vtkNotUsed(request),
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
 
PROJECT(vtkTestFilterProgressFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkTestFilterProgressFilter MACOSX_BUNDLE vtkTestFilterProgressFilter.cxx)
 
target_link_libraries(vtkTestFilterProgressFilter ${VTK_LIBRARIES})
```

**Download and Build vtkTestFilterProgressFilter**

Click [here to download vtkTestFilterProgressFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkTestFilterProgressFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkTestFilterProgressFilter.tar* has been downloaded and extracted,
```
cd vtkTestFilterProgressFilter/build 
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
./vtkTestFilterProgressFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

