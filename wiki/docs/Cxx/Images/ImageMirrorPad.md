[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageMirrorPad

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageMirrorPad.png?raw=true" width="256" />

### Description
This example shows how to enlarge an image and fill in the padded edges by mirroring the original pixels.

**ImageMirrorPad.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageMirrorPad.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> source = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetExtent(0, 20, 0, 20, 0, 0);
  source->SetScalarTypeToUnsignedChar();
  source->SetDrawColor(0.0, 0.0, 0.0, 1.0);
  source->FillBox(-VTK_INT_MAX, VTK_INT_MAX, -VTK_INT_MAX, VTK_INT_MAX);
  source->SetDrawColor(255.0, 0.0, 0.0, 0.5);
  source->DrawCircle(10, 10, 5);
  source->Update();
  
  vtkSmartPointer<vtkImageMirrorPad> mirrorPadFilter = 
    vtkSmartPointer<vtkImageMirrorPad>::New();
  mirrorPadFilter->SetInputConnection(source->GetOutputPort());
  mirrorPadFilter->SetOutputWholeExtent(-10, 30, -10, 30, 0, 0);
  mirrorPadFilter->Update();
  
  // Create an actor
  vtkSmartPointer<vtkImageActor> actor = 
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(
    mirrorPadFilter->GetOutputPort());
 
  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
      vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();
 
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer ( renderer );
 
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
 
  renderWindowInteractor->SetRenderWindow ( renderWindow );
  renderWindowInteractor->Initialize();
 
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageMirrorPad)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageMirrorPad MACOSX_BUNDLE ImageMirrorPad.cxx)
 
target_link_libraries(ImageMirrorPad ${VTK_LIBRARIES})
```

**Download and Build ImageMirrorPad**

Click [here to download ImageMirrorPad](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageMirrorPad.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageMirrorPad.tar* has been downloaded and extracted,
```
cd ImageMirrorPad/build 
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
./ImageMirrorPad
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

