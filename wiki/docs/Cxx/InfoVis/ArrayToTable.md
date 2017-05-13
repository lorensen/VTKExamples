[VTKExamples](/index/)/[Cxx](/Cxx)/InfoVis/ArrayToTable

**ArrayToTable.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkDenseArray.h>
#include <vtkArrayToTable.h>
#include <vtkTable.h>
#include <vtkArrayData.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDenseArray<int> > array =
      vtkSmartPointer<vtkDenseArray<int> >::New();
  array->Resize(2,4);

  //set values
  std::cout << "There are " << array->GetExtents()[0].GetEnd() << std::endl;
  std::cout << "There are " << array->GetExtents()[1].GetEnd() << std::endl;

  for(vtkIdType i = 0; i < array->GetExtents()[0].GetEnd(); i++)
  {
    for(vtkIdType j = 0; j < array->GetExtents()[1].GetEnd(); j++)
    {	
      array->SetValue(i, j, i+j);
    }
  }

  vtkSmartPointer<vtkArrayData> arrayData =
    vtkSmartPointer<vtkArrayData>::New();
  arrayData->AddArray(array);

  vtkSmartPointer<vtkArrayToTable> arrayToTable =
    vtkSmartPointer<vtkArrayToTable>::New();
#if VTK_MAJOR_VERSION <= 5
  arrayToTable->SetInputConnection(arrayData->GetProducerPort());
#else
  arrayToTable->SetInputData(arrayData);
#endif
  arrayToTable->Update();

  vtkSmartPointer<vtkTable> table = arrayToTable->GetOutput();
  table->Dump();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ArrayToTable)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ArrayToTable MACOSX_BUNDLE ArrayToTable.cxx)
 
target_link_libraries(ArrayToTable ${VTK_LIBRARIES})
```

**Download and Build ArrayToTable**

Click [here to download ArrayToTable](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ArrayToTable.tar) and its *CMakeLists.txt* file.
Once the *tarball ArrayToTable.tar* has been downloaded and extracted,
```
cd ArrayToTable/build 
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
./ArrayToTable
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

