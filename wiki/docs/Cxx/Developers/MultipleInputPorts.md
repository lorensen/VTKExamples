[VTKExamples](Home)/[Cxx](Cxx)/Developers/MultipleInputPorts

### Description
See also the {{class|vtkAppendPolyData}} class ([usage]]([../../Cxx/Filtering/CombinePolyData|example)).

**MultipleInputPorts.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

#include "vtkTestMultipleInputPortsFilter.h"

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource1 =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->SetThetaResolution(5);
  sphereSource1->Update();

  vtkSmartPointer<vtkSphereSource> sphereSource2 =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetThetaResolution(10);
  sphereSource2->Update();

  vtkSmartPointer<vtkTestMultipleInputPortsFilter> filter =
      vtkSmartPointer<vtkTestMultipleInputPortsFilter>::New();
  filter->SetInputConnection(0, sphereSource1->GetOutputPort());
  filter->SetInputConnection(1, sphereSource2->GetOutputPort());
  filter->Update();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MultipleInputPorts)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MultipleInputPorts MACOSX_BUNDLE MultipleInputPorts.cxx)
 
target_link_libraries(MultipleInputPorts ${VTK_LIBRARIES})
```

**Download and Build MultipleInputPorts**

Click [here to download MultipleInputPorts](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MultipleInputPorts.tar) and its *CMakeLists.txt* file.
Once the *tarball MultipleInputPorts.tar* has been downloaded and extracted,
```
cd MultipleInputPorts/build 
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
./MultipleInputPorts
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

