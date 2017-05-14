[VTKExamples](/index/)/[Cxx](/Cxx)/Matlab/MatlabEngineFilter

### Description
This example currently does nothing. 

**MatlabEngineFilter.cxx**
```c++
//need to set VTK_USE_MATLAB_MEX ON

#include <vtkSmartPointer.h>
#include <vtkMatlabEngineFilter.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkMatlabEngineFilter> matlabFilter = 
      vtkSmartPointer<vtkMatlabEngineFilter>::New();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MatlabEngineFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MatlabEngineFilter MACOSX_BUNDLE MatlabEngineFilter.cxx)
 
target_link_libraries(MatlabEngineFilter ${VTK_LIBRARIES})
```

**Download and Build MatlabEngineFilter**

Click [here to download MatlabEngineFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MatlabEngineFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball MatlabEngineFilter.tar* has been downloaded and extracted,
```
cd MatlabEngineFilter/build 
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
./MatlabEngineFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

