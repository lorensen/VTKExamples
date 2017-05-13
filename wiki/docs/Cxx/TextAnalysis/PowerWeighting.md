[VTKExamples](Home)/[Cxx](Cxx)/TextAnalysis/PowerWeighting

**PowerWeighting.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPowerWeighting.h>
#include <vtkDenseArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDenseArray<double> > array =
    vtkSmartPointer<vtkDenseArray<double> >::New();
  array->Resize(2);
  array->SetValue(0, 3);
  array->SetValue(1, 4);

  vtkSmartPointer<vtkArrayData> arrayData =
    vtkSmartPointer<vtkArrayData>::New();
  arrayData->AddArray(array);
  
  vtkSmartPointer<vtkPowerWeighting> powerWeighting =
    vtkSmartPointer<vtkPowerWeighting>::New();
  powerWeighting->SetPower(2);
  powerWeighting->SetInputConnection(arrayData->GetProducerPort());
  powerWeighting->Update();
  
  vtkSmartPointer<vtkArrayData> outputArrayData = powerWeighting->GetOutput();
  vtkSmartPointer<vtkDenseArray<double> > outputArray = vtkDenseArray<double>::SafeDownCast(outputArrayData->GetArray(0));

  std::cout << outputArray->GetValue(0) << std::endl;
  std::cout << outputArray->GetValue(1) << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PowerWeighting)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PowerWeighting MACOSX_BUNDLE PowerWeighting.cxx)
 
target_link_libraries(PowerWeighting ${VTK_LIBRARIES})
```

**Download and Build PowerWeighting**

Click [here to download PowerWeighting](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PowerWeighting.tar) and its *CMakeLists.txt* file.
Once the *tarball PowerWeighting.tar* has been downloaded and extracted,
```
cd PowerWeighting/build 
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
./PowerWeighting
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

