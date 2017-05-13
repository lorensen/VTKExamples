[VTKExamples](Home)/[Cxx](Cxx)/Math/MatrixInverse

**MatrixInverse.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkMatrix3x3.h>
	
int main(int, char *[])
{
  vtkSmartPointer<vtkMatrix3x3> m = 
    vtkSmartPointer<vtkMatrix3x3>::New();
  
  m->SetElement(2,1,2.0); // Set element (0,0) to 1.0
  
  std::cout << *m << std::endl;
  
  m->Invert();
  
  std::cout << *m << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MatrixInverse)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MatrixInverse MACOSX_BUNDLE MatrixInverse.cxx)
 
target_link_libraries(MatrixInverse ${VTK_LIBRARIES})
```

**Download and Build MatrixInverse**

Click [here to download MatrixInverse](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MatrixInverse.tar) and its *CMakeLists.txt* file.
Once the *tarball MatrixInverse.tar* has been downloaded and extracted,
```
cd MatrixInverse/build 
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
./MatrixInverse
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

