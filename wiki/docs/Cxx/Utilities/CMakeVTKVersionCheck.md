[VTKExamples](Home)/[Cxx](Cxx)/Utilities/CMakeVTKVersionCheck

**CMakeVTKVersionCheck.cxx**
```c++
#include <vtkPolyData.h>

int main(int, char *[])
{

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CMakeVTKVersionCheck)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CMakeVTKVersionCheck MACOSX_BUNDLE CMakeVTKVersionCheck.cxx)
 
target_link_libraries(CMakeVTKVersionCheck ${VTK_LIBRARIES})
```

**Download and Build CMakeVTKVersionCheck**

Click [here to download CMakeVTKVersionCheck](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CMakeVTKVersionCheck.tar) and its *CMakeLists.txt* file.
Once the *tarball CMakeVTKVersionCheck.tar* has been downloaded and extracted,
```
cd CMakeVTKVersionCheck/build 
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
./CMakeVTKVersionCheck
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

