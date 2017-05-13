[VTKExamples](Home)/[Cxx](Cxx)/Utilities/ArrayLookup

**ArrayLookup.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkFloatArray.h>
#include <vtkIdList.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkFloatArray> distances =
    vtkSmartPointer<vtkFloatArray>::New();
  distances->SetNumberOfComponents(1);
  distances->SetName("Distances");

  distances->InsertNextValue(5);
  distances->InsertNextValue(15);
  distances->InsertNextValue(15);
  distances->InsertNextValue(25);
  distances->InsertNextValue(15);

  // Get first location
  vtkIdType result = distances->LookupValue(15);
  std::cout << "result: " << result << std::endl;

  // Get all locations
  vtkSmartPointer<vtkIdList> idList =
    vtkSmartPointer<vtkIdList>::New();
  distances->LookupValue(15, idList);
  std::cout << "found at: " << std::endl;
  for(vtkIdType i = 0; i < idList->GetNumberOfIds(); i++)
  {
    std::cout << idList->GetId(i) << " ";
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ArrayLookup)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ArrayLookup MACOSX_BUNDLE ArrayLookup.cxx)
 
target_link_libraries(ArrayLookup ${VTK_LIBRARIES})
```

**Download and Build ArrayLookup**

Click [here to download ArrayLookup](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ArrayLookup.tar) and its *CMakeLists.txt* file.
Once the *tarball ArrayLookup.tar* has been downloaded and extracted,
```
cd ArrayLookup/build 
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
./ArrayLookup
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

