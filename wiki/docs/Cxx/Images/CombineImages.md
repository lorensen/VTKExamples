[VTKExamples](/index/)/[Cxx](/Cxx)/Images/CombineImages

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestCombineImages.png?raw=true" width="256" />

### Description
This example takes two images and super imposes them. The opacity of each image can be set to control how they are combined.

**CombineImages.cxx**
```c++
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkImageBlend.h>
#include <string>

int main ( int argc, char* argv[] )
{
  // Parse input arguments
  if ( argc != 3 )
  {
    std::cerr << "Usage: " << argv[0]
              << " Input1Filename Input2Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string input1Filename = argv[1];
  std::string input2Filename = argv[2];

  // Read the images
  vtkSmartPointer<vtkJPEGReader> jPEGReader1 =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader1->SetFileName ( input1Filename.c_str() );

  vtkSmartPointer<vtkJPEGReader> jPEGReader2 =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader2->SetFileName ( input2Filename.c_str() );

  // Combine the images (blend takes multiple connections on the 0th input port)
  vtkSmartPointer<vtkImageBlend> blend =
    vtkSmartPointer<vtkImageBlend>::New();
  blend->AddInputConnection(jPEGReader1->GetOutputPort());
  blend->AddInputConnection(jPEGReader2->GetOutputPort());
  blend->SetOpacity(0,.5);
  blend->SetOpacity(1,.5);

  // Display the result
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(blend->GetOutputPort());
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->GetRenderer()->SetBackground(1,0,0); //red

  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CombineImages)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CombineImages MACOSX_BUNDLE CombineImages.cxx)
 
target_link_libraries(CombineImages ${VTK_LIBRARIES})
```

**Download and Build CombineImages**

Click [here to download CombineImages](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CombineImages.tar) and its *CMakeLists.txt* file.
Once the *tarball CombineImages.tar* has been downloaded and extracted,
```
cd CombineImages/build 
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
./CombineImages
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

