[VTKExamples](Home)/[Cxx](Cxx)/Math/PerpendicularVector

**PerpendicularVector.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkMath.h>

int main(int, char *[])
{
  double x[3] = {1,0,0};
  double y[3];
  vtkMath::Perpendiculars(x, y, NULL, 0);

  std::cout << "y: " << y[0] << " " << y[1] << " " << y[2] << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PerpendicularVector)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PerpendicularVector MACOSX_BUNDLE PerpendicularVector.cxx)
 
target_link_libraries(PerpendicularVector ${VTK_LIBRARIES})
```

**Download and Build PerpendicularVector**

Click [here to download PerpendicularVector](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PerpendicularVector.tar) and its *CMakeLists.txt* file.
Once the *tarball PerpendicularVector.tar* has been downloaded and extracted,
```
cd PerpendicularVector/build 
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
./PerpendicularVector
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

