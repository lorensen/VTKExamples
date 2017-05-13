[VTKExamples](/home/)/[Cxx](/Cxx)/Utilities/VersionMacros

**VersionMacros.cxx**
```c++
#include <vtkPolyData.h>
#include <vtkVersion.h> // NOTE: without this include, the VTK_[]_VERSION are not defined!

// These functions allow you to output the version defines at compile time
#define STR(x) STR2(x)
#define STR2(x) #x

int main(int, char *[])
{
  #if VTK_MAJOR_VERSION>5 || (VTK_MAJOR_VERSION==5 && VTK_MINOR_VERSION>4)
    #pragma message(STR(VTK_MAJOR_VERSION))
  #endif

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(VersionMacros)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VersionMacros MACOSX_BUNDLE VersionMacros.cxx)
 
target_link_libraries(VersionMacros ${VTK_LIBRARIES})
```

**Download and Build VersionMacros**

Click [here to download VersionMacros](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VersionMacros.tar) and its *CMakeLists.txt* file.
Once the *tarball VersionMacros.tar* has been downloaded and extracted,
```
cd VersionMacros/build 
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
./VersionMacros
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

