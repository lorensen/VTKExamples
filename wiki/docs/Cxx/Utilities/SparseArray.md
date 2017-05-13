[VTKExamples](/home/)/[Cxx](/Cxx)/Utilities/SparseArray

**SparseArray.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSparseArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSparseArray<double> > array =
    vtkSmartPointer<vtkSparseArray<double> >::New();
  array->Resize(5,1);
  array->SetNullValue(-1);

  for(unsigned int i = 0; i < 5; i++)
  {
    array->SetValue(i, 0, i);
  }

  for(unsigned int i = 0; i < 6; i++)
  {
    double val = array->GetValue(i,0);
    std::cout << val << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SparseArray)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SparseArray MACOSX_BUNDLE SparseArray.cxx)
 
target_link_libraries(SparseArray ${VTK_LIBRARIES})
```

**Download and Build SparseArray**

Click [here to download SparseArray](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SparseArray.tar) and its *CMakeLists.txt* file.
Once the *tarball SparseArray.tar* has been downloaded and extracted,
```
cd SparseArray/build 
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
./SparseArray
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

