[VTKExamples](Home)/[Cxx](Cxx)/IO/JPEGWriter

**JPEGWriter.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkJPEGWriter.h>

int main(int vtkNotUsed(argc), char* vtkNotUsed(argv)[])
{
  std::string outputFilename = "output.jpg";

  // Create a 100x100 image to save into the jpeg file
  int extent[6] = { 0, 99, 0, 99, 0, 0 };
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetExtent( extent );
  imageSource->SetScalarTypeToUnsignedChar(); // vtkJPEGWriter only accepts unsigned char input
  imageSource->SetNumberOfScalarComponents( 3 ); // 3 color channels: Red, Green and Blue

  // Fill the whole image with a blue background
  imageSource->SetDrawColor( 0, 127, 255 );
  imageSource->FillBox( extent[0], extent[1], extent[2], extent[3] );

  // Paint a 30x30 white square into the image
  imageSource->SetDrawColor( 255, 255, 255 );
  imageSource->FillBox( 40, 70, 20, 50 );

  vtkSmartPointer<vtkJPEGWriter> writer =
    vtkSmartPointer<vtkJPEGWriter>::New();
  writer->SetFileName( outputFilename.c_str() );
  writer->SetInputConnection( imageSource->GetOutputPort() );
  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(JPEGWriter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(JPEGWriter MACOSX_BUNDLE JPEGWriter.cxx)
 
target_link_libraries(JPEGWriter ${VTK_LIBRARIES})
```

**Download and Build JPEGWriter**

Click [here to download JPEGWriter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/JPEGWriter.tar) and its *CMakeLists.txt* file.
Once the *tarball JPEGWriter.tar* has been downloaded and extracted,
```
cd JPEGWriter/build 
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
./JPEGWriter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

