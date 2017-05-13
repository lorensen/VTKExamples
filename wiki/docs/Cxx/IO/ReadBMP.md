[VTKExamples](Home)/[Cxx](Cxx)/IO/ReadBMP

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/IO/TestReadBMP.png" width="256" />

**ReadBMP.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkBMPReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  //Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.bmp)" << std::endl;
    return EXIT_FAILURE;
  }

  //Read the image
  vtkSmartPointer<vtkBMPReader> reader =
    vtkSmartPointer<vtkBMPReader>::New();
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
 
PROJECT(ReadBMP)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadBMP MACOSX_BUNDLE ReadBMP.cxx)
 
target_link_libraries(ReadBMP ${VTK_LIBRARIES})
```

**Download and Build ReadBMP**

Click [here to download ReadBMP](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ReadBMP.tar) and its *CMakeLists.txt* file.
Once the *tarball ReadBMP.tar* has been downloaded and extracted,
```
cd ReadBMP/build 
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
./ReadBMP
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

