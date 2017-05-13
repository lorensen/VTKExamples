[VTKExamples](Home)/[Cxx](Cxx)/Utilities/GetClassName

### Description
This example demonstrates the GetClassName function. This should be available for every VTK class. This is extremely helpful for debugging - you are able to determine the type of a variable that is passed as an abstract type. With this information, the list of functions that can be called on this variable can be determined.

The example illustrates alternative ways to get the "name" of a class. Notice that the GetClassName provides a simple and useful solution.

**GetClassName.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <typeinfo>

static const char *unmangleName (const char * name);

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();

  std::cout << "points->GetClassName():             "
            << points->GetClassName() << std::endl;
  std::cout << "Mangled" << std::endl;
  std::cout << "\ttypeid(points).name():              "
            << typeid(points).name() << std::endl;
  std::cout << "\ttypeid(points.GetPointer()).name(): "
            << typeid(points.GetPointer()).name() << std::endl;
  std::cout << "Unmangled" << std::endl;
  std::cout << "\ttypeid(points.GetPointer()).name(): "
            << unmangleName(typeid(points).name()) << std::endl;
  std::cout << "\ttypeid(points.GetPointer()).name(): "
            << unmangleName(typeid(points.GetPointer()).name()) << std::endl;
  return EXIT_SUCCESS;
}

// Better name demangling for gcc
#if __GNUC__ > 3 || ( __GNUC__ == 3 && __GNUC_MINOR__ > 0 )
#define GCC_USEDEMANGLE
#endif

#ifdef GCC_USEDEMANGLE
#include <cstdlib>
#include <cxxabi.h>
#endif

const char *unmangleName (const char * name)
{
#ifdef GCC_USEDEMANGLE
  char const *mangledName = name;
  int         status;
  char *      unmangled = abi::__cxa_demangle(mangledName, 0, 0, &status);
  return unmangled;
#else
  return name;
#endif
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GetClassName)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GetClassName MACOSX_BUNDLE GetClassName.cxx)
 
target_link_libraries(GetClassName ${VTK_LIBRARIES})
```

**Download and Build GetClassName**

Click [here to download GetClassName](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GetClassName.tar) and its *CMakeLists.txt* file.
Once the *tarball GetClassName.tar* has been downloaded and extracted,
```
cd GetClassName/build 
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
./GetClassName
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

