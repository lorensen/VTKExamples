[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/ColorTransferFunction

### Description
This example demonstrates how to map the values (0.0 to 10.0) to the colors (red to green).

**ColorTransferFunction.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkColorTransferFunction.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = 
    vtkSmartPointer<vtkColorTransferFunction>::New();
  
  colorTransferFunction->AddRGBPoint(0.0, 1, 0, 0);
  colorTransferFunction->AddRGBPoint(10.0, 0, 1, 0);
  
  double color[3];
  colorTransferFunction->GetColor(1.0, color);
  std::cout << color[0] << " " << color[1] << " " << color[2] << std::endl;
  
  colorTransferFunction->GetColor(5.0, color);
  std::cout << color[0] << " " << color[1] << " " << color[2] << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ColorTransferFunction)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ColorTransferFunction MACOSX_BUNDLE ColorTransferFunction.cxx)
 
target_link_libraries(ColorTransferFunction ${VTK_LIBRARIES})
```

**Download and Build ColorTransferFunction**

Click [here to download ColorTransferFunction](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ColorTransferFunction.tar) and its *CMakeLists.txt* file.
Once the *tarball ColorTransferFunction.tar* has been downloaded and extracted,
```
cd ColorTransferFunction/build 
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
./ColorTransferFunction
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

