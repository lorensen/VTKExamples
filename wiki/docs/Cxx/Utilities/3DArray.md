[VTKExamples](/home/)/[Cxx](/Cxx)/Utilities/3DArray

**3DArray.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkDenseArray.h>

int main(int, char *[])
{
  // Create an N-D array
  vtkSmartPointer<vtkDenseArray<double> > array = 
      vtkSmartPointer<vtkDenseArray<double> >::New();
  
  // Resize the array to 4x5x3
  array->Resize(4,5,3);
  
  // Set a value
  int i = 0; int j = 0; int k = 0;
  double value = 3.0;
  array->SetValue(i, j, k, value);
  
  // Get a value
  std::cout << array->GetValue(i,j,k) << std::endl;
  
  // Get size (bounds) of whole array
  cout << array->GetExtents() << endl;
  
  // Get size (bounds) of array dimensions
  std::cout << array->GetExtents()[0] << std::endl;
  std::cout << array->GetExtents()[1] << std::endl;
  std::cout << array->GetExtents()[2] << std::endl;
  
  // Get the bounds of the 0th dimension
  std::cout << array->GetExtents()[0].GetBegin() << std::endl;
  std::cout << array->GetExtents()[0].GetEnd() << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(3DArray)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(3DArray MACOSX_BUNDLE 3DArray.cxx)
 
target_link_libraries(3DArray ${VTK_LIBRARIES})
```

**Download and Build 3DArray**

Click [here to download 3DArray](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/3DArray.tar) and its *CMakeLists.txt* file.
Once the *tarball 3DArray.tar* has been downloaded and extracted,
```
cd 3DArray/build 
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
./3DArray
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

