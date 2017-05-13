[VTKExamples](Home)/[Cxx](Cxx)/Utilities/CheckVTKVersion

### Description
This example demonstrates how to check the VTK version with vtkVersion.

**CheckVTKVersion.cxx**
```c++
#include <vtkVersion.h>

int main(int, char *[])
{
  std::cout << vtkVersion::GetVTKSourceVersion() << std::endl;
  std::cout << vtkVersion::GetVTKMajorVersion() << std::endl;
  std::cout << vtkVersion::GetVTKMinorVersion() << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CheckVTKVersion)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CheckVTKVersion MACOSX_BUNDLE CheckVTKVersion.cxx)
 
target_link_libraries(CheckVTKVersion ${VTK_LIBRARIES})
```

**Download and Build CheckVTKVersion**

Click [here to download CheckVTKVersion](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CheckVTKVersion.tar) and its *CMakeLists.txt* file.
Once the *tarball CheckVTKVersion.tar* has been downloaded and extracted,
```
cd CheckVTKVersion/build 
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
./CheckVTKVersion
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

