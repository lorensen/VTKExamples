[VTKExamples](/home/)/[Cxx](/Cxx)/Images/ImageLuminance

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageLuminance.png?raw=true" width="256" />

### Description
There are two ways to convert images to greyscale:
* {{class|vtkImageLuminance}} uses the [(video)|luminance equation]]([wikipedia:Luma) for properly weighting the R, G, and B components;
* {{class|vtkImageMagnitude}} does a simple sum-of-squares computation of the components (i.e. the [(mathematics)#Euclidean vector space|Euclidean norm]] -- not the [[wikipedia:Root mean square|quadratic mean]]([wikipedia:Magnitude)!), and is meant for vector data.

For an example of usage of the vtkImageMagnitude filter, see []([../ImageMagnitude]).

**ImageLuminance.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageLuminance.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>

int main(int, char *[])
{
  // Create an image of a rectangle
  vtkSmartPointer<vtkImageCanvasSource2D> source =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetScalarTypeToUnsignedChar();
  source->SetNumberOfScalarComponents(3);
  source->SetExtent(0, 200, 0, 200, 0, 0);

  // Clear the image
  source->SetDrawColor(0,0,0);
  source->FillBox(0,200,0,200);

  // Draw a red box
  source->SetDrawColor(255,0,0);
  source->FillBox(100,120,100,120);
  source->Update();

  vtkSmartPointer<vtkImageLuminance> luminanceFilter = 
      vtkSmartPointer<vtkImageLuminance>::New();
  luminanceFilter->SetInputConnection(source->GetOutputPort());
  luminanceFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    source->GetOutputPort());

  vtkSmartPointer<vtkImageActor> luminanceActor =
    vtkSmartPointer<vtkImageActor>::New();
  luminanceActor->GetMapper()->SetInputConnection(
    luminanceFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double luminanceViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> luminanceRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  luminanceRenderer->SetViewport(luminanceViewport);
  luminanceRenderer->AddActor(luminanceActor);
  luminanceRenderer->ResetCamera();
  luminanceRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(luminanceRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageLuminance)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageLuminance MACOSX_BUNDLE ImageLuminance.cxx)
 
target_link_libraries(ImageLuminance ${VTK_LIBRARIES})
```

**Download and Build ImageLuminance**

Click [here to download ImageLuminance](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageLuminance.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageLuminance.tar* has been downloaded and extracted,
```
cd ImageLuminance/build 
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
./ImageLuminance
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

