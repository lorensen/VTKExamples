[VTKExamples](Home)/[Cxx](Cxx)/IO/XMLPImageDataWriter

**XMLPImageDataWriter.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkXMLPImageDataWriter.h>
#include <vtkImageCanvasSource2D.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkImageCanvasSource2D> drawing =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetScalarTypeToUnsignedChar();
  drawing->SetExtent(0, 20, 0, 50, 0, 1);
  drawing->SetDrawColor(255.0, 255.0, 255.0);
  drawing->DrawCircle(5, 5, 3);

  int numberOfPieces = 4;
  
  vtkSmartPointer<vtkXMLPImageDataWriter> writer =
    vtkSmartPointer<vtkXMLPImageDataWriter>::New();
  writer->SetInputConnection(drawing->GetOutputPort());
  writer->SetFileName("Test.pvti");
  writer->SetNumberOfPieces(numberOfPieces);
  writer->SetEndPiece(numberOfPieces-1);
  writer->SetStartPiece(0);
  writer->Update();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(XMLPImageDataWriter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(XMLPImageDataWriter MACOSX_BUNDLE XMLPImageDataWriter.cxx)
 
target_link_libraries(XMLPImageDataWriter ${VTK_LIBRARIES})
```

**Download and Build XMLPImageDataWriter**

Click [here to download XMLPImageDataWriter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/XMLPImageDataWriter.tar) and its *CMakeLists.txt* file.
Once the *tarball XMLPImageDataWriter.tar* has been downloaded and extracted,
```
cd XMLPImageDataWriter/build 
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
./XMLPImageDataWriter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

