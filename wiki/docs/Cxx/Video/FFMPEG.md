[VTKExamples](/home/)/[Cxx](/Cxx)/Video/FFMPEG

### Description
You must set
VTK_USE_FFMPEG_ENCODER ON
in your VTK build.

CMake won't find FFMPEG headers?

**FFMPEG.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkFFMPEGWriter.h>

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkImageCanvasSource2D> source =
      vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetScalarTypeToUnsignedChar();
  source->SetNumberOfScalarComponents(3);
  source->SetExtent(0, 100, 0, 100, 0, 0);

  vtkSmartPointer<vtkFFMPEGWriter> writer =
      vtkSmartPointer<vtkFFMPEGWriter>::New();

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
 
PROJECT(FFMPEG)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FFMPEG MACOSX_BUNDLE FFMPEG.cxx)
 
target_link_libraries(FFMPEG ${VTK_LIBRARIES})
```

**Download and Build FFMPEG**

Click [here to download FFMPEG](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/FFMPEG.tar) and its *CMakeLists.txt* file.
Once the *tarball FFMPEG.tar* has been downloaded and extracted,
```
cd FFMPEG/build 
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
./FFMPEG
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

