[VTKExamples](/home/)/[Cxx](/Cxx)/IO/PNGWriter

**PNGWriter.cxx**
```c++
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkSmartPointer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageCast.h>

int main(int argc, char *argv[])
{
  std::string outputFilename;
  if( argc > 1)
  {
    outputFilename = argv[1];
  }
  else
  {
    outputFilename = "output.png";
  }

  int extent[6] = {0, 99, 0, 99, 0, 0};
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetExtent(extent);
  imageSource->SetScalarTypeToUnsignedChar();
  imageSource->SetNumberOfScalarComponents(3);
  imageSource->SetDrawColor(127, 45, 255);
  imageSource->FillBox(0, 99, 0, 99);
  imageSource->SetDrawColor(255,255,255);
  imageSource->FillBox(40, 70, 20, 50);
  imageSource->Update();

  vtkSmartPointer<vtkImageCast> castFilter =
    vtkSmartPointer<vtkImageCast>::New();
  castFilter->SetOutputScalarTypeToUnsignedChar ();
  castFilter->SetInputConnection(imageSource->GetOutputPort());
  castFilter->Update();

  vtkSmartPointer<vtkPNGWriter> writer =
    vtkSmartPointer<vtkPNGWriter>::New();
  writer->SetFileName(outputFilename.c_str());
  writer->SetInputConnection(castFilter->GetOutputPort());
  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PNGWriter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PNGWriter MACOSX_BUNDLE PNGWriter.cxx)
 
target_link_libraries(PNGWriter ${VTK_LIBRARIES})
```

**Download and Build PNGWriter**

Click [here to download PNGWriter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PNGWriter.tar) and its *CMakeLists.txt* file.
Once the *tarball PNGWriter.tar* has been downloaded and extracted,
```
cd PNGWriter/build 
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
./PNGWriter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

