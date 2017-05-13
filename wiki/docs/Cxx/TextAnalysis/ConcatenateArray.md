[VTKExamples](Home)/[Cxx](Cxx)/TextAnalysis/ConcatenateArray

**ConcatenateArray.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkConcatenateArray.h>
#include <vtkDenseArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDenseArray<double> > array0 =
    vtkSmartPointer<vtkDenseArray<double> >::New();
  array0->Resize(2);
  array0->SetValue(0, 0);
  array0->SetValue(1, 1);

  vtkSmartPointer<vtkDenseArray<double> > array1 =
    vtkSmartPointer<vtkDenseArray<double> >::New();
  array1->Resize(2);
  array1->SetValue(0, 2);
  array1->SetValue(1, 3);

  vtkSmartPointer<vtkArrayData> arrayData0 =
    vtkSmartPointer<vtkArrayData>::New();
  arrayData0->AddArray(array0);
  arrayData0->Update();
  
  vtkSmartPointer<vtkArrayData> arrayData1 =
    vtkSmartPointer<vtkArrayData>::New();
  arrayData1->AddArray(array1);
  arrayData1->Update();
  
  vtkSmartPointer<vtkConcatenateArray> concatenateArray =
    vtkSmartPointer<vtkConcatenateArray>::New();
  concatenateArray->SetInput(0, arrayData0);
  concatenateArray->SetInput(1, arrayData1);
  concatenateArray->Update();

  vtkSmartPointer<vtkArrayData> outputArrayData = concatenateArray->GetOutput();
  vtkSmartPointer<vtkDenseArray<double> > outputArray = vtkDenseArray<double>::SafeDownCast(outputArrayData->GetArray(0));

  std::cout << outputArray->GetValue(0) << std::endl;
  std::cout << outputArray->GetValue(1) << std::endl;
  std::cout << outputArray->GetValue(2) << std::endl;
  std::cout << outputArray->GetValue(3) << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ConcatenateArray)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ConcatenateArray MACOSX_BUNDLE ConcatenateArray.cxx)
 
target_link_libraries(ConcatenateArray ${VTK_LIBRARIES})
```

**Download and Build ConcatenateArray**

Click [here to download ConcatenateArray](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ConcatenateArray.tar) and its *CMakeLists.txt* file.
Once the *tarball ConcatenateArray.tar* has been downloaded and extracted,
```
cd ConcatenateArray/build 
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
./ConcatenateArray
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

