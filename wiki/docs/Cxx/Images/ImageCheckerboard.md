[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageCheckerboard

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageCheckerboard.png?raw=true" width="256" />

### Description
This example compares two images using a checkerboard pattern.

**ImageCheckerboard.cxx**
```c++
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkImageCheckerboard.h>

int main ( int argc, char* argv[] )
{
  // Verify input arguments
  if ( argc != 3 )
  {
    std::cerr << "Usage: " << argv[0]
              << " Input1Filename Input2Filename" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse input arguments
  std::string inputFilename1 = argv[1];
  std::string inputFilename2 = argv[2];

  // Read the images
  vtkSmartPointer<vtkJPEGReader> jPEGReader1 =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader1->SetFileName ( inputFilename1.c_str() );

  vtkSmartPointer<vtkJPEGReader> jPEGReader2 =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader2->SetFileName ( inputFilename2.c_str() );

  vtkSmartPointer<vtkImageCheckerboard> checkerboardFilter =
    vtkSmartPointer<vtkImageCheckerboard>::New();
  checkerboardFilter->SetInputConnection(0, jPEGReader1->GetOutputPort());
  checkerboardFilter->SetInputConnection(1, jPEGReader2->GetOutputPort());
  checkerboardFilter->SetNumberOfDivisions(3,3,1);

  // Visualize
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(checkerboardFilter->GetOutputPort());
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->GetRenderer()->SetBackground(1,0,0);
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageCheckerboard)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageCheckerboard MACOSX_BUNDLE ImageCheckerboard.cxx)
 
target_link_libraries(ImageCheckerboard ${VTK_LIBRARIES})
```

**Download and Build ImageCheckerboard**

Click [here to download ImageCheckerboard](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageCheckerboard.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageCheckerboard.tar* has been downloaded and extracted,
```
cd ImageCheckerboard/build 
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
./ImageCheckerboard
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

