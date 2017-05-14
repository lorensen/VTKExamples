[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/VectorArrayKnownLength

### Description
This example creates a VTK style float array of vectors. This can be easily interchanged with vtkIntArray, vtkDoubleArray, etc.

**VectorArrayKnownLength.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkFloatArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkFloatArray> distances =
    vtkSmartPointer<vtkFloatArray>::New();
  distances->SetName("Distances");
  distances->SetNumberOfComponents(3);
  distances->SetNumberOfTuples(5);

  //set values
  for(vtkIdType i = 0; i < distances->GetNumberOfTuples(); i++)
  {
    float tuple[3];
    tuple[0] = (float)i + 0.1;
    tuple[1] = (float)i + 0.2;
    tuple[2] = (float)i + 0.3;
    distances->SetTuple(i, tuple);
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
 
PROJECT(VectorArrayKnownLength)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VectorArrayKnownLength MACOSX_BUNDLE VectorArrayKnownLength.cxx)
 
target_link_libraries(VectorArrayKnownLength ${VTK_LIBRARIES})
```

**Download and Build VectorArrayKnownLength**

Click [here to download VectorArrayKnownLength](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VectorArrayKnownLength.tar) and its *CMakeLists.txt* file.
Once the *tarball VectorArrayKnownLength.tar* has been downloaded and extracted,
```
cd VectorArrayKnownLength/build 
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
./VectorArrayKnownLength
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

