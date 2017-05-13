[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/VectorArrayUnknownLength

### Description
This example creates a VTK style float array of vectors. This can be easily interchanged with vtkIntArray, vtkDoubleArray, etc.

The only difference between this example and the [KnownLengthArrayOfVectors](Cxx/Utilities/KnownLengthArrayOfVectors) example is that `SetNumberOfValues()` is not called, and `SetTuple()` is replaced by `InsertNextTuple()`. 

**VectorArrayUnknownLength.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkFloatArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkFloatArray> distances =
    vtkSmartPointer<vtkFloatArray>::New();
  distances->SetName("Distances");
  distances->SetNumberOfComponents(3);

  //set values
  for(vtkIdType i = 0; i < 5; i++)
  {
    float tuple[3];
    tuple[0] = (float)i + 0.1;
    tuple[1] = (float)i + 0.2;
    tuple[2] = (float)i + 0.3;
    //this will allocate memory as necessary
    distances->InsertNextTuple(tuple);
  }

  //get values
  for(vtkIdType i = 0; i < distances->GetNumberOfTuples(); i++)
  {
    double d[3];
    distances->GetTuple(i, d);
    std::cout << d[0] << " " << d[1] << " " << d[2] << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(VectorArrayUnknownLength)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VectorArrayUnknownLength MACOSX_BUNDLE VectorArrayUnknownLength.cxx)
 
target_link_libraries(VectorArrayUnknownLength ${VTK_LIBRARIES})
```

**Download and Build VectorArrayUnknownLength**

Click [here to download VectorArrayUnknownLength](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VectorArrayUnknownLength.tar) and its *CMakeLists.txt* file.
Once the *tarball VectorArrayUnknownLength.tar* has been downloaded and extracted,
```
cd VectorArrayUnknownLength/build 
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
./VectorArrayUnknownLength
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

