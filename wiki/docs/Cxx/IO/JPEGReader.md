[VTKExamples](/index/)/[Cxx](/Cxx)/IO/JPEGReader

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestJPEGReader.png?raw=true" width="256" />

### Description
This example shows how to read a JPG image file.

**JPEGReader.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkJPEGReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  //Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.jpeg)" << std::endl;
    return EXIT_FAILURE;
  }

  //Read the image
  vtkSmartPointer<vtkJPEGReader> jpegReader =
    vtkSmartPointer<vtkJPEGReader>::New();
  jpegReader->SetFileName ( argv[1] );

  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection( jpegReader->GetOutputPort() );
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(JPEGReader)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(JPEGReader MACOSX_BUNDLE JPEGReader.cxx)
 
target_link_libraries(JPEGReader ${VTK_LIBRARIES})
```

**Download and Build JPEGReader**

Click [here to download JPEGReader](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/JPEGReader.tar) and its *CMakeLists.txt* file.
Once the *tarball JPEGReader.tar* has been downloaded and extracted,
```
cd JPEGReader/build 
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
./JPEGReader
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

