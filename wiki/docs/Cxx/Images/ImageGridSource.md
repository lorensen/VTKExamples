[VTKExamples](/home/)/[Cxx](/Cxx)/Images/ImageGridSource

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageGridSource.png?raw=true" width="256" />

**ImageGridSource.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageGridSource.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>
 
int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageGridSource> source =
    vtkSmartPointer<vtkImageGridSource>::New();
  source->SetFillValue(122);
  source->Update();
 
  vtkSmartPointer<vtkImageCast> castFilter =
    vtkSmartPointer<vtkImageCast>::New();
  castFilter->SetInputConnection(source->GetOutputPort());
  castFilter->SetOutputScalarTypeToUnsignedChar();
  castFilter->Update();
 
  // Create an actor
  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(castFilter->GetOutputPort());
 
  // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();
 
  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
 
  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
 
  renderWindowInteractor->SetInteractorStyle(style);
 
  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();
 
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageGridSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageGridSource MACOSX_BUNDLE ImageGridSource.cxx)
 
target_link_libraries(ImageGridSource ${VTK_LIBRARIES})
```

**Download and Build ImageGridSource**

Click [here to download ImageGridSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageGridSource.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageGridSource.tar* has been downloaded and extracted,
```
cd ImageGridSource/build 
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
./ImageGridSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

