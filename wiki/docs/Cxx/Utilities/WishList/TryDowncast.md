[VTKExamples](Home)/[Cxx](Cxx)/Utilities/WishList/TryDowncast

**TryDowncast.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkTryDowncast.h>

int main(int, char *[])
{
  // Demonstrate a check of a cast
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TryDowncast)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TryDowncast MACOSX_BUNDLE TryDowncast.cxx)
 
target_link_libraries(TryDowncast ${VTK_LIBRARIES})
```

**Download and Build TryDowncast**

Click [here to download TryDowncast](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TryDowncast.tar) and its *CMakeLists.txt* file.
Once the *tarball TryDowncast.tar* has been downloaded and extracted,
```
cd TryDowncast/build 
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
./TryDowncast
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

