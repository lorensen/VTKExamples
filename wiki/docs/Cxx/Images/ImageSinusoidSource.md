[VTKExamples](Home)/[Cxx](Cxx)/Images/ImageSinusoidSource

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Images/TestImageSinusoidSource.png" width="256" />

**ImageSinusoidSource.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkImageSinusoidSource.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkImageSinusoidSource> sinusoidSource =
    vtkSmartPointer<vtkImageSinusoidSource>::New();
  sinusoidSource->Update();

  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(sinusoidSource->GetOutputPort());
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
 
PROJECT(ImageSinusoidSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageSinusoidSource MACOSX_BUNDLE ImageSinusoidSource.cxx)
 
target_link_libraries(ImageSinusoidSource ${VTK_LIBRARIES})
```

**Download and Build ImageSinusoidSource**

Click [here to download ImageSinusoidSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageSinusoidSource.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageSinusoidSource.tar* has been downloaded and extracted,
```
cd ImageSinusoidSource/build 
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
./ImageSinusoidSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

