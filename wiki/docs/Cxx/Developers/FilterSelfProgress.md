[VTKExamples](/home/)/[Cxx](/Cxx)/Developers/FilterSelfProgress

### Description
<source lang="cpp">
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
  vtkInformation *inInfo = inputVector[](0)->GetInformationObject(0);
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
</source>

**FilterSelfProgress.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>

#include "vtkTestFilterSelfProgressFilter.h"

void ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);

int main(int argc, char **argv)
{ 
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  vtkSmartPointer<vtkTestFilterSelfProgressFilter> testFilter = 
      vtkSmartPointer<vtkTestFilterSelfProgressFilter>::New();
  testFilter->SetInputConnection(sphereSource->GetOutputPort());
  testFilter->Update();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(FilterSelfProgress)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FilterSelfProgress MACOSX_BUNDLE FilterSelfProgress.cxx)
 
target_link_libraries(FilterSelfProgress ${VTK_LIBRARIES})
```

**Download and Build FilterSelfProgress**

Click [here to download FilterSelfProgress](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/FilterSelfProgress.tar) and its *CMakeLists.txt* file.
Once the *tarball FilterSelfProgress.tar* has been downloaded and extracted,
```
cd FilterSelfProgress/build 
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
./FilterSelfProgress
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

