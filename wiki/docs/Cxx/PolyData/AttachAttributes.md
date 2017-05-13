[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/AttachAttributes

**AttachAttributes.cxx**
```c++
// vtk includes
#include <vtkDoubleArray.h>
#include <vtkInformation.h>
#include <vtkInformationDoubleVectorKey.h>

// std includes
#include <iostream>

int main(int, char *[]) {

  // create a 2-element array
  vtkDoubleArray* array = vtkDoubleArray::New();
  array->SetName("array");
  array->SetNumberOfComponents(1);
  array->SetNumberOfTuples(2);
  array->SetValue(0, 1.);
  array->SetValue(1, 2.);

  // access the info (presently none stored)
  vtkInformation* info = array->GetInformation();

  // add one attribute, a double vector
  const char *name = "myKey";
  const char *location = "MyClass"; // 
  const int length = 3;
  vtkInformationDoubleVectorKey *key = new vtkInformationDoubleVectorKey(name, 
                                                                         location, 
                                                                         length);
  double values[] = {0.1, 0.2, 0.3};
  info->Set(key, values[0], values[1],values[2]);

  // extract the key
  double *vals = info->Get(key);
  std::cout << "extracted values are: " << vals[0] << ", " << vals[1] << ", " << vals[2] << '\n';
  array->Delete();
  // array->Delete will also delete key (do not call delete key)

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(AttachAttributes)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(AttachAttributes MACOSX_BUNDLE AttachAttributes.cxx)
 
target_link_libraries(AttachAttributes ${VTK_LIBRARIES})
```

**Download and Build AttachAttributes**

Click [here to download AttachAttributes](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/AttachAttributes.tar) and its *CMakeLists.txt* file.
Once the *tarball AttachAttributes.tar* has been downloaded and extracted,
```
cd AttachAttributes/build 
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
./AttachAttributes
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

