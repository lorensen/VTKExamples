[VTKExamples](Home)/[Cxx](Cxx)/Developers/ProgressReport

### Description
This example demonstrates how to get the progress of a filter. This requires that the filter is updating its progress in a sensible way. A sample filter is provided which loops through the input points and updates its progress along the way.

**ProgressReport.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>

#include "vtkTestProgressReportFilter.h"

void ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);

int main(int, char *[])
{ 
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  vtkSmartPointer<vtkCallbackCommand> progressCallback = 
    vtkSmartPointer<vtkCallbackCommand>::New();
  progressCallback->SetCallback(ProgressFunction);
    
  vtkSmartPointer<vtkTestProgressReportFilter> testFilter = 
    vtkSmartPointer<vtkTestProgressReportFilter>::New();
  testFilter->SetInputConnection(sphereSource->GetOutputPort());
  testFilter->AddObserver(vtkCommand::ProgressEvent, progressCallback);
  testFilter->Update();
  
  return EXIT_SUCCESS;
}

void ProgressFunction ( vtkObject* caller,
                        long unsigned int vtkNotUsed(eventId),
                        void* vtkNotUsed(clientData),
                        void* vtkNotUsed(callData) )
{
  vtkTestProgressReportFilter* testFilter = static_cast<vtkTestProgressReportFilter*>(caller);
  std::cout << "Progress: " << testFilter->GetProgress() << std::endl;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ProgressReport)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ProgressReport MACOSX_BUNDLE ProgressReport.cxx)
 
target_link_libraries(ProgressReport ${VTK_LIBRARIES})
```

**Download and Build ProgressReport**

Click [here to download ProgressReport](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ProgressReport.tar) and its *CMakeLists.txt* file.
Once the *tarball ProgressReport.tar* has been downloaded and extracted,
```
cd ProgressReport/build 
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
./ProgressReport
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

