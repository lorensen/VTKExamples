[VTKExamples](Home)/[Cxx](Cxx)/Developers/FilterProgress

**FilterProgress.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>

#include "vtkTestFilterProgressFilter.h"

void ProgressFunction(vtkObject* caller,
                      long unsigned int eventId,
                      void* clientData,
                      void* callData);

int main(int, char *[])
{ 
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  vtkSmartPointer<vtkTestFilterProgressFilter> testFilter = 
    vtkSmartPointer<vtkTestFilterProgressFilter>::New();
  testFilter->SetInputConnection(sphereSource->GetOutputPort());
  testFilter->Update();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(FilterProgress)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FilterProgress MACOSX_BUNDLE FilterProgress.cxx)
 
target_link_libraries(FilterProgress ${VTK_LIBRARIES})
```

**Download and Build FilterProgress**

Click [here to download FilterProgress](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/FilterProgress.tar) and its *CMakeLists.txt* file.
Once the *tarball FilterProgress.tar* has been downloaded and extracted,
```
cd FilterProgress/build 
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
./FilterProgress
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

