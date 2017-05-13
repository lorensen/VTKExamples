[VTKExamples](Home)/[Cxx](Cxx)/Images/ImageThreshold

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Images/TestImageThreshold.png" width="256" />

### Description
The image on the left is the input image and the image on the right is the thresholded version.

**ImageThreshold.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageThreshold.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageMapper3D.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>
#include <vtkImageMandelbrotSource.h>
 
int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageMandelbrotSource> imageSource =
    vtkSmartPointer<vtkImageMandelbrotSource>::New();
  imageSource->Update();
 
  vtkSmartPointer<vtkImageThreshold> imageThreshold = 
    vtkSmartPointer<vtkImageThreshold>::New();
  imageThreshold->SetInputConnection(imageSource->GetOutputPort());
  unsigned char lower = 100;
  unsigned char upper = 200;
 
  imageThreshold->ThresholdBetween(lower, upper);
  imageThreshold->ReplaceInOn();
  imageThreshold->SetInValue(255);
  imageThreshold->Update();
 
  // Create actors
  vtkSmartPointer<vtkImageActor> inputActor =
    vtkSmartPointer<vtkImageActor>::New();
  inputActor->GetMapper()->SetInputConnection(
    imageSource->GetOutputPort());
 
  vtkSmartPointer<vtkImageActor> thresholdedActor =
    vtkSmartPointer<vtkImageActor>::New();
  thresholdedActor->GetMapper()->SetInputConnection(
    imageThreshold->GetOutputPort());
 
  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
 
  // And one interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
 
  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};
 
  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);
 
  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);
 
  leftRenderer->AddActor(inputActor);
  rightRenderer->AddActor(thresholdedActor);
 
  leftRenderer->ResetCamera();
  rightRenderer->ResetCamera();
 
  renderWindow->Render();
  interactor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageThreshold)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageThreshold MACOSX_BUNDLE ImageThreshold.cxx)
 
target_link_libraries(ImageThreshold ${VTK_LIBRARIES})
```

**Download and Build ImageThreshold**

Click [here to download ImageThreshold](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageThreshold.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageThreshold.tar* has been downloaded and extracted,
```
cd ImageThreshold/build 
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
./ImageThreshold
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

