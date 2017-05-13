[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/ShallowCopy

**ShallowCopy.cxx**
```c++
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

  vtkSmartPointer<vtkPolyData> polydataCopy = vtkSmartPointer<vtkPolyData>::New();

  polydataCopy->ShallowCopy(polydata);

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ShallowCopy)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ShallowCopy MACOSX_BUNDLE ShallowCopy.cxx)
 
target_link_libraries(ShallowCopy ${VTK_LIBRARIES})
```

**Download and Build ShallowCopy**

Click [here to download ShallowCopy](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ShallowCopy.tar) and its *CMakeLists.txt* file.
Once the *tarball ShallowCopy.tar* has been downloaded and extracted,
```
cd ShallowCopy/build 
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
./ShallowCopy
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

