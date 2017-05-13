[VTKExamples](Home)/[Cxx](Cxx)/Utilities/Variant

**Variant.cxx**
```c++
#include <vtkVariant.h>

#include <iostream>
#include <string>

int main(int, char *[])
{
  double dVal = vtkVariant("2").ToDouble();
  std::cout << "dVal: " << dVal << std::endl;
  std::string strVal = vtkVariant(dVal).ToString();
  std::cout << "strVal: " << strVal << std::endl;
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Variant)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Variant MACOSX_BUNDLE Variant.cxx)
 
target_link_libraries(Variant ${VTK_LIBRARIES})
```

**Download and Build Variant**

Click [here to download Variant](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Variant.tar) and its *CMakeLists.txt* file.
Once the *tarball Variant.tar* has been downloaded and extracted,
```
cd Variant/build 
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
./Variant
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

