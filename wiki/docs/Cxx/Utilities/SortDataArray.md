[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/SortDataArray

**SortDataArray.cxx**
```c++
#include <vtkSortDataArray.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{

  vtkSmartPointer<vtkDoubleArray> valueArray =
    vtkSmartPointer<vtkDoubleArray>::New();
  valueArray->InsertNextValue(20.0);
  valueArray->InsertNextValue(10.0);
  valueArray->InsertNextValue(30.0);

  vtkSmartPointer<vtkIntArray> keyArray =
    vtkSmartPointer<vtkIntArray>::New();
  keyArray->InsertNextValue(1);
  keyArray->InsertNextValue(0);
  keyArray->InsertNextValue(2);

  std::cout << "Unsorted: " << valueArray->GetValue(0) << " "
            << valueArray->GetValue(1) << " "
            << valueArray->GetValue(2) << std::endl;

  // Sort the array
  vtkSmartPointer<vtkSortDataArray> sortDataArray =
    vtkSmartPointer<vtkSortDataArray>::New();
  sortDataArray->Sort(keyArray, valueArray);

  std::cout << "Sorted: " << valueArray->GetValue(0) << " "
            << valueArray->GetValue(1) << " "
            << valueArray->GetValue(2) << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SortDataArray)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SortDataArray MACOSX_BUNDLE SortDataArray.cxx)
 
target_link_libraries(SortDataArray ${VTK_LIBRARIES})
```

**Download and Build SortDataArray**

Click [here to download SortDataArray](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SortDataArray.tar) and its *CMakeLists.txt* file.
Once the *tarball SortDataArray.tar* has been downloaded and extracted,
```
cd SortDataArray/build 
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
./SortDataArray
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

