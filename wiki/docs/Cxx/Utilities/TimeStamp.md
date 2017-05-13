[VTKExamples](Home)/[Cxx](Cxx)/Utilities/TimeStamp

**TimeStamp.cxx**
```c++
#include <vtkTimeStamp.h>

int main(int, char *[])
{
  vtkTimeStamp timeStamp;
  std::cout << "Time stamp: " << timeStamp << std::endl;
  timeStamp.Modified();
  std::cout << "Time stamp: " << timeStamp << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TimeStamp)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TimeStamp MACOSX_BUNDLE TimeStamp.cxx)
 
target_link_libraries(TimeStamp ${VTK_LIBRARIES})
```

**Download and Build TimeStamp**

Click [here to download TimeStamp](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TimeStamp.tar) and its *CMakeLists.txt* file.
Once the *tarball TimeStamp.tar* has been downloaded and extracted,
```
cd TimeStamp/build 
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
./TimeStamp
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

