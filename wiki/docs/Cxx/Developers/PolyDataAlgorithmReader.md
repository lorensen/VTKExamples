[VTKExamples](Home)/[Cxx](Cxx)/Developers/PolyDataAlgorithmReader

### Description
This example demonstrates a reader that takes nothing as input and produces a vtkPolyData as output.

**PolyDataAlgorithmReader.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>

#include "vtkTestReader.h"

int main (int, char *[])
{
  vtkSmartPointer<vtkTestReader> reader =
    vtkSmartPointer<vtkTestReader>::New();
  reader->Update();
  
  vtkPolyData* polydata = reader->GetOutput();
  polydata->Print(std::cout);

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PolyDataAlgorithmReader)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PolyDataAlgorithmReader MACOSX_BUNDLE PolyDataAlgorithmReader.cxx)
 
target_link_libraries(PolyDataAlgorithmReader ${VTK_LIBRARIES})
```

**Download and Build PolyDataAlgorithmReader**

Click [here to download PolyDataAlgorithmReader](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PolyDataAlgorithmReader.tar) and its *CMakeLists.txt* file.
Once the *tarball PolyDataAlgorithmReader.tar* has been downloaded and extracted,
```
cd PolyDataAlgorithmReader/build 
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
./PolyDataAlgorithmReader
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

