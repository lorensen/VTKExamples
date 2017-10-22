```cmake
cmake_minimum_required(VERSION 2.6)
 
project(CheckForModule)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
find_package(VTK REQUIRED)
if(NOT vtkIOParallel_LOADED)
  message(FATAL_ERROR "vtkIOParallel is required but not available.")
endif()
 
add_executable(CheckForModule CheckForModule.cxx)
target_link_libraries(CheckForModule ${VTK_LIBRARIES})
```
