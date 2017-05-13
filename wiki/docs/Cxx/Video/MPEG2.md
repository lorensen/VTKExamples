[VTKExamples](Home)/[Cxx](Cxx)/Video/MPEG2

### Description
You must set
VTK_USE_MPEG2_ENCODER ON
VTK_USE_OGGTHEORA_ENCODER ON
in your VTK build.

CMake won't find MPEG2?

When compiling: cannot find -lvtkoggtheora

**MPEG2.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkMPEG2Writer.h>

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkImageCanvasSource2D> source =
      vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetScalarTypeToUnsignedChar();
  source->SetNumberOfScalarComponents(3);
  source->SetExtent(0, 100, 0, 100, 0, 0);

  vtkSmartPointer<vtkMPEG2Writer> writer =
      vtkSmartPointer<vtkMPEG2Writer>::New();

  writer->SetInputConnection(source->GetOutputPort());
  writer->SetFileName("test.avi");
  writer->Start();

  for(unsigned int i = 0; i < 100; i++)
  {
    source->SetDrawColor(0,0,0,1); //black
    source->FillBox(0, 100, 0, 100); //clear image
    source->SetDrawColor(255,0,0,1); //red
    source->FillBox(i, 20, 10, 20);
    source->Update();

    writer->Write();
  }
  writer->End();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MPEG2)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MPEG2 MACOSX_BUNDLE MPEG2.cxx)
 
target_link_libraries(MPEG2 ${VTK_LIBRARIES})
```

**Download and Build MPEG2**

Click [here to download MPEG2](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MPEG2.tar) and its *CMakeLists.txt* file.
Once the *tarball MPEG2.tar* has been downloaded and extracted,
```
cd MPEG2/build 
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
./MPEG2
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

