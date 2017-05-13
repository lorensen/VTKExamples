[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/KnownLengthArray

### Description
This example creates a VTK style float array. This can be easily
interchanged with vtkIntArray, vtkDoubleArray, etc.

The terminology is as follows:

* `SetNumberOfComponents()`: sets the number of elements that a tuple in the array will have. See [KnownLengthArrayOfVectors](Cxx/Utilities/KnownLengthArrayOfVectors) for an example with tuples with more than one element.

* `SetNumberOfValues()`: sets the number of tuples the array will have. See [UnknownLengthArray](Cxx/Utilities/UnknownLengthArray) for an example where the number of values is not known in advance.

**KnownLengthArray.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkFloatArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkFloatArray> distances =
    vtkSmartPointer<vtkFloatArray>::New();
  distances->SetName("Distances");
  distances->SetNumberOfComponents(1);
  distances->SetNumberOfValues(5);

  //set values
  for(vtkIdType i = 0; i < distances->GetNumberOfTuples(); i++)
  {
    float f = (float)i + 0.1;
    distances->SetValue(i, f);
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
 
PROJECT(KnownLengthArray)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(KnownLengthArray MACOSX_BUNDLE KnownLengthArray.cxx)
 
target_link_libraries(KnownLengthArray ${VTK_LIBRARIES})
```

**Download and Build KnownLengthArray**

Click [here to download KnownLengthArray](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/KnownLengthArray.tar) and its *CMakeLists.txt* file.
Once the *tarball KnownLengthArray.tar* has been downloaded and extracted,
```
cd KnownLengthArray/build 
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
./KnownLengthArray
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

