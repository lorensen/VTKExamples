[VTKExamples](/index/)/[Cxx](/Cxx)/Images/StaticImage

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestStaticImage.png?raw=true" width="256" />

### Description
This example displays an image in a non-interactable window.

**StaticImage.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkImageViewer2.h>
#include <vtkJPEGReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  // Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.jpeg)" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkJPEGReader> jpegReader =
    vtkSmartPointer<vtkJPEGReader>::New();
  if(!jpegReader->CanReadFile(argv[1]))
  {
    std::cout << argv[0]
              << ": Error reading file " << argv[1] << std::endl
              << " Exiting..." << std::endl;
    return EXIT_FAILURE;
  }

  jpegReader->SetFileName ( argv[1] );

  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection( jpegReader->GetOutputPort() );
  imageViewer->GetRenderWindow()->SetSize( 500, 500 );
  imageViewer->GetRenderer()->ResetCamera();

  // Set up an interactor that does not respond to mouse events
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  imageViewer->GetRenderWindow()->SetInteractor( renderWindowInteractor );
  renderWindowInteractor->SetInteractorStyle( 0 );
  imageViewer->Render();

  // Start the event loop
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(StaticImage)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(StaticImage MACOSX_BUNDLE StaticImage.cxx)
 
target_link_libraries(StaticImage ${VTK_LIBRARIES})
```

**Download and Build StaticImage**

Click [here to download StaticImage](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/StaticImage.tar) and its *CMakeLists.txt* file.
Once the *tarball StaticImage.tar* has been downloaded and extracted,
```
cd StaticImage/build 
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
./StaticImage
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

