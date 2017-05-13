[VTKExamples](Home)/[Cxx](Cxx)/Utilities/DeepCopy

**DeepCopy.cxx**
```c++
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

  vtkSmartPointer<vtkPolyData> polydataCopy = vtkSmartPointer<vtkPolyData>::New();

  polydataCopy->DeepCopy(polydata);
  
  return 0;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DeepCopy)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DeepCopy MACOSX_BUNDLE DeepCopy.cxx)
 
target_link_libraries(DeepCopy ${VTK_LIBRARIES})
```

**Download and Build DeepCopy**

Click [here to download DeepCopy](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DeepCopy.tar) and its *CMakeLists.txt* file.
Once the *tarball DeepCopy.tar* has been downloaded and extracted,
```
cd DeepCopy/build 
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
./DeepCopy
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

