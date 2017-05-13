[VTKExamples](Home)/[Cxx](Cxx)/Developers/Warnings

**Warnings.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkDataObject.h>
#include <vtkObjectFactory.h>

class TestClass : public vtkDataObject
{
  public:
  static TestClass *New();
  vtkTypeRevisionMacro(TestClass,vtkDataObject);
  TestClass()
  {
    vtkWarningMacro("Test warning.");
  }
};

vtkStandardNewMacro(TestClass);

int main(int, char *[])
{

  vtkSmartPointer<TestClass> test =
      vtkSmartPointer<TestClass>::New();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Warnings)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Warnings MACOSX_BUNDLE Warnings.cxx)
 
target_link_libraries(Warnings ${VTK_LIBRARIES})
```

**Download and Build Warnings**

Click [here to download Warnings](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Warnings.tar) and its *CMakeLists.txt* file.
Once the *tarball Warnings.tar* has been downloaded and extracted,
```
cd Warnings/build 
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
./Warnings
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

