[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/Vector

**Vector.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkVector.h>

#include <iostream>

int main(int, char *[])
{
  vtkVector3d v(1.0, 2.0, 3.0);
  std::cout << v.GetX() << " " << v.GetY() << " " << v.GetZ() << std::endl;
    
  double* vals = v.GetData();
  
  std::cout << vals[0] << " " << vals[1] << " " << vals[2] << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Vector)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Vector MACOSX_BUNDLE Vector.cxx)
 
target_link_libraries(Vector ${VTK_LIBRARIES})
```

**Download and Build Vector**

Click [here to download Vector](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Vector.tar) and its *CMakeLists.txt* file.
Once the *tarball Vector.tar* has been downloaded and extracted,
```
cd Vector/build 
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
./Vector
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

