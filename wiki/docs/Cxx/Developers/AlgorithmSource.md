[VTKExamples](Home)/[Cxx](Cxx)/Developers/AlgorithmSource

### Description
This example demonstrates how to create a source that returns a custom class. To test that it is working, the class vtkTest1 simply stores a double named 'Value' that is instantiated to the value of 4.5. Example.cxx instantiates a vtkTestSource which produces a vtkTest1.

**AlgorithmSource.cxx**
```c++
#include <vtkSmartPointer.h>

#include "vtkTestAlgorithmSource.h"
#include "vtkTest1.h"

int main(int, char *[])
{
  vtkTestAlgorithmSource* source = vtkTestAlgorithmSource::New();
  source->Update();
  
  vtkTest1* test = source->GetOutput();
  std::cout << test->GetValue() << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(AlgorithmSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(AlgorithmSource MACOSX_BUNDLE AlgorithmSource.cxx)
 
target_link_libraries(AlgorithmSource ${VTK_LIBRARIES})
```

**Download and Build AlgorithmSource**

Click [here to download AlgorithmSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/AlgorithmSource.tar) and its *CMakeLists.txt* file.
Once the *tarball AlgorithmSource.tar* has been downloaded and extracted,
```
cd AlgorithmSource/build 
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
./AlgorithmSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

