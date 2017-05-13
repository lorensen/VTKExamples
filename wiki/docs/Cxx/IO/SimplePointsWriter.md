[VTKExamples](/home/)/[Cxx](/Cxx)/IO/SimplePointsWriter

### Description
**Note:** For the opposite operation (reading a points file) see the
[SimplePointsReader](Cxx/IO/SimplePointsReader) example.

**SimplePointsWriter.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkSimplePointsWriter.h>

int main(int vtkNotUsed(argc), char* vtkNotUsed(argv)[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkSimplePointsWriter> writer =
    vtkSmartPointer<vtkSimplePointsWriter>::New();
  writer->SetFileName("test.xyz");
  writer->SetInputConnection(sphereSource->GetOutputPort());
  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SimplePointsWriter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SimplePointsWriter MACOSX_BUNDLE SimplePointsWriter.cxx)
 
target_link_libraries(SimplePointsWriter ${VTK_LIBRARIES})
```

**Download and Build SimplePointsWriter**

Click [here to download SimplePointsWriter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SimplePointsWriter.tar) and its *CMakeLists.txt* file.
Once the *tarball SimplePointsWriter.tar* has been downloaded and extracted,
```
cd SimplePointsWriter/build 
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
./SimplePointsWriter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

