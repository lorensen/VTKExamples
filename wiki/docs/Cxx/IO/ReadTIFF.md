[VTKExamples](Home)/[Cxx](Cxx)/IO/ReadTIFF

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/IO/TestReadTIFF.png" width="256" />

**ReadTIFF.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkTIFFReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  //Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.tif)" << std::endl;
    return EXIT_FAILURE;
  }

  //Read the image
  vtkSmartPointer<vtkTIFFReader> reader =
    vtkSmartPointer<vtkTIFFReader>::New();
  reader->SetFileName ( argv[1] );

  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(reader->GetOutputPort());
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
 
PROJECT(ReadTIFF)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadTIFF MACOSX_BUNDLE ReadTIFF.cxx)
 
target_link_libraries(ReadTIFF ${VTK_LIBRARIES})
```

**Download and Build ReadTIFF**

Click [here to download ReadTIFF](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ReadTIFF.tar) and its *CMakeLists.txt* file.
Once the *tarball ReadTIFF.tar* has been downloaded and extracted,
```
cd ReadTIFF/build 
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
./ReadTIFF
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

