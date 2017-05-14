[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/GetDataRoot

**GetDataRoot.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkTesting.h>

int main(int, char *[])
{
  // Locate VTK_DATA_ROOT
  vtkSmartPointer<vtkTesting> testHelper =
    vtkSmartPointer<vtkTesting>::New();
  std::string dataRoot = testHelper->GetDataRoot();

  std::cout << "dataRoot: " << dataRoot << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GetDataRoot)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GetDataRoot MACOSX_BUNDLE GetDataRoot.cxx)
 
target_link_libraries(GetDataRoot ${VTK_LIBRARIES})
```

**Download and Build GetDataRoot**

Click [here to download GetDataRoot](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GetDataRoot.tar) and its *CMakeLists.txt* file.
Once the *tarball GetDataRoot.tar* has been downloaded and extracted,
```
cd GetDataRoot/build 
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
./GetDataRoot
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

