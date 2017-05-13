[VTKExamples](Home)/[Cxx](Cxx)/CMakeTechniques/CheckForModule

**CheckForModule.cxx**
```c++
#include <vtkPolyData.h>

int main(int, char *[])
{

  return EXIT_SUCCESS;
}
```
```cmake
cmake_minimum_required(VERSION 2.6)
 
PROJECT(CheckForModule)
 
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
 
find_package(VTK REQUIRED)
if(NOT vtkIOParallel_LOADED)
  message(FATAL_ERROR "vtkIOParallel is required but not available.")
endif()
 
ADD_EXECUTABLE(CheckForModule CheckForModule.cxx)
TARGET_LINK_LIBRARIES(CheckForModule ${VTK_LIBRARIES})
```
