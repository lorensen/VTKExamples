[VTKExamples](/home/)/[Cxx](/Cxx)/Math/NormalizeVector

**NormalizeVector.cxx**
```c++
#include "vtkMath.h"

int main(int, char*[])
{
  double a[3] = {100.0, 2.0, 1.0};
  std::cout << a[0] << " " << a[1] << " " << a[2] << std::endl;
  vtkMath::Normalize(a);
  std::cout << a[0] << " " << a[1] << " " << a[2] << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(NormalizeVector)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(NormalizeVector MACOSX_BUNDLE NormalizeVector.cxx)
 
target_link_libraries(NormalizeVector ${VTK_LIBRARIES})
```

**Download and Build NormalizeVector**

Click [here to download NormalizeVector](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/NormalizeVector.tar) and its *CMakeLists.txt* file.
Once the *tarball NormalizeVector.tar* has been downloaded and extracted,
```
cd NormalizeVector/build 
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
./NormalizeVector
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

