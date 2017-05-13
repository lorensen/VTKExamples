[VTKExamples](Home)/[Cxx](Cxx)/Developers/AlgorithmFilter

### Description
This example demonstrates how to create a filter that accepts a custom class and returns a custom class. To test that it is working, the class vtkTest simply stores a double named 'Value' that is instantiated to the value of 4.5. Example.cxx instantiates a vtkTest and sets its value to 5.6. The filter adds 1.0 to this value, so the vtkTest that is the output of the vtkTestAlgorithmFilter should contain the value 6.6.

**AlgorithmFilter.cxx**
```c++
#include <vtkSmartPointer.h>

#include "vtkTestAlgorithmFilter.h"
#include "vtkTest.h"

int main(int, char *[])
{
  vtkSmartPointer<vtkTest> inputTest = 
    vtkSmartPointer<vtkTest>::New();
  inputTest->SetValue(5.6);
  std::cout << "Input value: " << inputTest->GetValue() << std::endl;
  
  vtkSmartPointer<vtkTestAlgorithmFilter> filter = vtkTestAlgorithmFilter::New();
  filter->SetInput(inputTest);
  filter->Update();
  
  vtkTest* outputTest = filter->GetOutput();
  std::cout << "Output value: " << outputTest->GetValue() << std::endl;
  std::cout << "Input value is still: " << inputTest->GetValue() << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(AlgorithmFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(AlgorithmFilter MACOSX_BUNDLE AlgorithmFilter.cxx)
 
target_link_libraries(AlgorithmFilter ${VTK_LIBRARIES})
```

**Download and Build AlgorithmFilter**

Click [here to download AlgorithmFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/AlgorithmFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball AlgorithmFilter.tar* has been downloaded and extracted,
```
cd AlgorithmFilter/build 
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
./AlgorithmFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

