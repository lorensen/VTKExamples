[VTKExamples](Home)/[Cxx](Cxx)/Utilities/DenseArrayRange

**DenseArrayRange.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkDenseArray.h>
#include <vtkArrayRange.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDenseArray<double> > array =
      vtkSmartPointer<vtkDenseArray<double> >::New();
  array->Resize(5,1);

  for(unsigned int i = 0; i < 5; i++)
  {
    array->SetValue(i, 0, 2.0);
    double val = array->GetValue(i,0);
    std::cout << "val: " << val << std::endl;
  }

  //int extent = array->GetExtents()[1];
  int dim1start = array->GetExtent(0).GetBegin();
  int dim1end = array->GetExtent(0).GetEnd();
  std::cout << "dim1: " << dim1start << " to " << dim1end << std::endl;
  //int dim2 = array->GetExtent(1)[1];

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DenseArrayRange)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DenseArrayRange MACOSX_BUNDLE DenseArrayRange.cxx)
 
target_link_libraries(DenseArrayRange ${VTK_LIBRARIES})
```

**Download and Build DenseArrayRange**

Click [here to download DenseArrayRange](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DenseArrayRange.tar) and its *CMakeLists.txt* file.
Once the *tarball DenseArrayRange.tar* has been downloaded and extracted,
```
cd DenseArrayRange/build 
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
./DenseArrayRange
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

