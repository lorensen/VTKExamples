[VTKExamples](/home/)/[Cxx](/Cxx)/Utilities/2DArray

### Description
This example creates a 5x5 2D array and sets the (4,4) (zero based indexing, of course) entry to 5.0. Then it outputs this value to demonstrate accessing.

**2DArray.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkDenseArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDenseArray<double> > array = 
    vtkSmartPointer<vtkDenseArray<double> >::New();
  
  array->Resize(5,5);
  
  array->SetValue(4,4, 5.0);
  
  std::cout << array->GetValue(4,4) << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(2DArray)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(2DArray MACOSX_BUNDLE 2DArray.cxx)
 
target_link_libraries(2DArray ${VTK_LIBRARIES})
```

**Download and Build 2DArray**

Click [here to download 2DArray](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/2DArray.tar) and its *CMakeLists.txt* file.
Once the *tarball 2DArray.tar* has been downloaded and extracted,
```
cd 2DArray/build 
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
./2DArray
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

