[VTKExamples](Home)/[Cxx](Cxx)/SimpleOperations/FloatingPointExceptions

### Description
This example makes the illegal division by zero produce an error:
 Error: Floating point exception detected. Signal 8
rather than simply store "inf" in y.

**FloatingPointExceptions.cxx**
```c++
#include <vtkFloatingPointExceptions.h>

// Avoid the "potential divide by 0" warning from the Microsoft
// compiler, since this example intentionally divides by 0
#ifdef _MSC_VER
#pragma warning (disable: 4723)
#endif

int main(int, char *[])
{
  // Disabled by default with gcc or visual studio.
  // Enabled by default by Borland CC.
  vtkFloatingPointExceptions::Enable(); 

  double x = 0.0;
  double y = 1.0/x; // floating-point exception

  std::cout << "x: " << x << " y: " << y << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(FloatingPointExceptions)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FloatingPointExceptions MACOSX_BUNDLE FloatingPointExceptions.cxx)
 
target_link_libraries(FloatingPointExceptions ${VTK_LIBRARIES})
```

**Download and Build FloatingPointExceptions**

Click [here to download FloatingPointExceptions](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/FloatingPointExceptions.tar) and its *CMakeLists.txt* file.
Once the *tarball FloatingPointExceptions.tar* has been downloaded and extracted,
```
cd FloatingPointExceptions/build 
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
./FloatingPointExceptions
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

