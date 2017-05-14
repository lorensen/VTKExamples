[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageMedian3D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageMedian3D.png?raw=true" width="256" />

**ImageMedian3D.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageMedian3D.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetNumberOfScalarComponents(1);
  imageSource->SetScalarTypeToUnsignedChar();
  unsigned int xmin = 0;
  unsigned int xmax = 20;
  unsigned int ymin = 0;
  unsigned int ymax = 20;
  imageSource->SetExtent(xmin, xmax, ymin, ymax, 0, 0);
  
  // Make the image all black
  imageSource->SetDrawColor(0.0);
  imageSource->FillBox(xmin, xmax, ymin, ymax);

  // Draw a big white square
  imageSource->SetDrawColor(255.0);
  imageSource->FillBox(5, 15, 5, 15);

  // Add some single white pixels
  imageSource->SetDrawColor(255.0);
  imageSource->FillBox(1, 1, 1, 1);
  imageSource->FillBox(17, 17, 17, 17);

  imageSource->Update();
  
  vtkSmartPointer<vtkImageMedian3D> medianFilter = 
    vtkSmartPointer<vtkImageMedian3D>::New();
  medianFilter->SetInputConnection(imageSource->GetOutputPort());
  medianFilter->SetKernelSize(3,3,1);
  medianFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    imageSource->GetOutputPort());

  vtkSmartPointer<vtkImageActor> medianActor =
    vtkSmartPointer<vtkImageActor>::New();
  medianActor->GetMapper()->SetInputConnection(
    medianFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(leftViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> gradientMagnitudeRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  gradientMagnitudeRenderer->SetViewport(rightViewport);
  gradientMagnitudeRenderer->AddActor(medianActor);
  gradientMagnitudeRenderer->ResetCamera();
  gradientMagnitudeRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(gradientMagnitudeRenderer);

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
 
PROJECT(ImageMedian3D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageMedian3D MACOSX_BUNDLE ImageMedian3D.cxx)
 
target_link_libraries(ImageMedian3D ${VTK_LIBRARIES})
```

**Download and Build ImageMedian3D**

Click [here to download ImageMedian3D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageMedian3D.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageMedian3D.tar* has been downloaded and extracted,
```
cd ImageMedian3D/build 
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
./ImageMedian3D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

