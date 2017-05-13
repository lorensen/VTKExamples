[VTKExamples](Home)/[Cxx](Cxx)/Utilities/ColorLookupTable

### Description
This example shows how to create a table of colors that map from a continuous range of values.

**ColorLookupTable.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkLookupTable.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkLookupTable> lookupTable = 
    vtkSmartPointer<vtkLookupTable>::New();
  
  lookupTable->SetTableRange(0.0, 10.0);
  // If you don't want to use the whole color range, you can use
  // SetValueRange, SetHueRange, and SetSaturationRange
  lookupTable->Build();
  
  double color[3];
  lookupTable->GetColor(1.0, color);
  std::cout << color[0] << " " << color[1] << " " << color[2] << std::endl;
  
  lookupTable->GetColor(5.0, color);
  std::cout << color[0] << " " << color[1] << " " << color[2] << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ColorLookupTable)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ColorLookupTable MACOSX_BUNDLE ColorLookupTable.cxx)
 
target_link_libraries(ColorLookupTable ${VTK_LIBRARIES})
```

**Download and Build ColorLookupTable**

Click [here to download ColorLookupTable](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ColorLookupTable.tar) and its *CMakeLists.txt* file.
Once the *tarball ColorLookupTable.tar* has been downloaded and extracted,
```
cd ColorLookupTable/build 
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
./ColorLookupTable
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

