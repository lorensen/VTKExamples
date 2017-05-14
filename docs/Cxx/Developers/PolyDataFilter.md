[VTKExamples](/index/)/[Cxx](/Cxx)/Developers/PolyDataFilter

### Description
This example demonstrates a filter named vtkTestPolyDataFilter that takes a vtkPolyData as input and produces a vtkPolyData as output.

**PolyDataFilter.cxx**
```c++
#include <vtkSmartPointer.h>

#include "vtkTestPolyDataFilter.h"

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  
  vtkSmartPointer<vtkPolyData> inputPolydata =   
    vtkSmartPointer<vtkPolyData>::New();
  inputPolydata->SetPoints(points);
  
  std::cout << "Input points: " << inputPolydata->GetNumberOfPoints() 
            << std::endl;
  
  vtkSmartPointer<vtkTestPolyDataFilter> filter = 
    vtkSmartPointer<vtkTestPolyDataFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  filter->SetInput(inputPolydata);
#else
  filter->SetInputData(inputPolydata);
#endif
  filter->Update();
  
  vtkPolyData* outputPolydata = filter->GetOutput();
  
  std::cout << "Output points: " << outputPolydata->GetNumberOfPoints() 
            << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PolyDataFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PolyDataFilter MACOSX_BUNDLE PolyDataFilter.cxx)
 
target_link_libraries(PolyDataFilter ${VTK_LIBRARIES})
```

**Download and Build PolyDataFilter**

Click [here to download PolyDataFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PolyDataFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball PolyDataFilter.tar* has been downloaded and extracted,
```
cd PolyDataFilter/build 
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
./PolyDataFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

