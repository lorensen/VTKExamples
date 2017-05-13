[VTKExamples](Home)/[Cxx](Cxx)/IO/XMLPUnstructuredGridWriter

**XMLPUnstructuredGridWriter.cxx**
```c++
#include <vtkDelaunay3D.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkXMLPUnstructuredGridWriter.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkDelaunay3D> delaunay =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay->SetInputConnection(sphereSource->GetOutputPort());
  delaunay->Update();

  vtkSmartPointer<vtkXMLPUnstructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLPUnstructuredGridWriter>::New();
  writer->SetInputConnection(delaunay->GetOutputPort());
  writer->SetFileName("Test.pvtu");
  writer->SetNumberOfPieces(4);
  writer->SetStartPiece(0);
  writer->SetEndPiece(3);
  writer->Update();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(XMLPUnstructuredGridWriter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(XMLPUnstructuredGridWriter MACOSX_BUNDLE XMLPUnstructuredGridWriter.cxx)
 
target_link_libraries(XMLPUnstructuredGridWriter ${VTK_LIBRARIES})
```

**Download and Build XMLPUnstructuredGridWriter**

Click [here to download XMLPUnstructuredGridWriter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/XMLPUnstructuredGridWriter.tar) and its *CMakeLists.txt* file.
Once the *tarball XMLPUnstructuredGridWriter.tar* has been downloaded and extracted,
```
cd XMLPUnstructuredGridWriter/build 
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
./XMLPUnstructuredGridWriter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

