[VTKExamples](Home)/[Cxx](Cxx)/Utilities/UnknownLengthArray

### Description
The only difference between this example and the [KnownLengthArray](Cxx/Utilities/KnownLengthArray) example is that `SetNumberOfValues()` is not called, and `SetValue()` is replaced by `InsertNextValue()`.

**UnknownLengthArray.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkFloatArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkFloatArray> distances =
    vtkSmartPointer<vtkFloatArray>::New();
  distances->SetName("Distances");
  distances->SetNumberOfComponents(1);

  //set values
  for(vtkIdType i = 0; i < 5; i++)
  {
    float f = (float)i + 0.1;
    //this will allocate memory as necessary
    distances->InsertNextValue(f);
  }

  //get values
  for(vtkIdType i = 0; i < distances->GetNumberOfTuples(); i++)
  {
    float f = distances->GetValue(i);
    std::cout << f << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(UnknownLengthArray)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(UnknownLengthArray MACOSX_BUNDLE UnknownLengthArray.cxx)
 
target_link_libraries(UnknownLengthArray ${VTK_LIBRARIES})
```

**Download and Build UnknownLengthArray**

Click [here to download UnknownLengthArray](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/UnknownLengthArray.tar) and its *CMakeLists.txt* file.
Once the *tarball UnknownLengthArray.tar* has been downloaded and extracted,
```
cd UnknownLengthArray/build 
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
./UnknownLengthArray
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

