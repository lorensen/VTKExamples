[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/ArrayWriter

**ArrayWriter.cxx**
```c++
#include <vtkVersion.h>
#include <vtkDenseArray.h>
#include <vtkSmartPointer.h>
#include <vtkArrayWriter.h>
#include <vtkArrayData.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDenseArray<double> > array =
    vtkSmartPointer<vtkDenseArray<double> >::New();
  array->Resize(1,3);
  array->SetValue(0,0, 1.0);
  array->SetValue(0,1, 2.0);
  array->SetValue(0,2, 3.0);
  {
  // Method 1
  vtkSmartPointer<vtkArrayWriter> writer =
    vtkSmartPointer<vtkArrayWriter>::New();
  vtkSmartPointer<vtkArrayData> arrayData =
    vtkSmartPointer<vtkArrayData>::New();
  arrayData->AddArray(array);
#if VTK_MAJOR_VERSION <= 5
  writer->SetInput(arrayData);
#else
  writer->SetInputData(arrayData);
#endif
  vtkStdString file1 = "Test1.txt";
  writer->Write(file1);
  }
  {
  vtkStdString file2 = "Test2.txt";
  // Method 2
  vtkSmartPointer<vtkArrayWriter> writer =
    vtkSmartPointer<vtkArrayWriter>::New();
  writer->Write(array, file2);
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ArrayWriter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ArrayWriter MACOSX_BUNDLE ArrayWriter.cxx)
 
target_link_libraries(ArrayWriter ${VTK_LIBRARIES})
```

**Download and Build ArrayWriter**

Click [here to download ArrayWriter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ArrayWriter.tar) and its *CMakeLists.txt* file.
Once the *tarball ArrayWriter.tar* has been downloaded and extracted,
```
cd ArrayWriter/build 
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
./ArrayWriter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

