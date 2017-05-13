[VTKExamples](/home/)/[Cxx](/Cxx)/ImageData/ImageNormalize

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/ImageData/TestImageNormalize.png?raw=true" width="256" />

**ImageNormalize.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageSinusoidSource.h>
#include <vtkImageNormalize.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageSinusoidSource> source =
    vtkSmartPointer<vtkImageSinusoidSource>::New();
  source->Update();

  vtkSmartPointer<vtkImageNormalize> normalizeFilter =
    vtkSmartPointer<vtkImageNormalize>::New();

  normalizeFilter->SetInputConnection(source->GetOutputPort());
  normalizeFilter->Update();

  vtkSmartPointer<vtkImageCast> inputCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  inputCastFilter->SetInputConnection(source->GetOutputPort());
  inputCastFilter->SetOutputScalarTypeToUnsignedChar();
  inputCastFilter->Update();

  vtkSmartPointer<vtkImageCast> normalizeCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  normalizeCastFilter->SetInputConnection(normalizeFilter->GetOutputPort());
  normalizeCastFilter->SetOutputScalarTypeToUnsignedChar();
  normalizeCastFilter->Update();
  
  // Create actors
  vtkSmartPointer<vtkImageActor> inputActor =
    vtkSmartPointer<vtkImageActor>::New();
  inputActor->GetMapper()->SetInputConnection(
    inputCastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> normalizedActor =
    vtkSmartPointer<vtkImageActor>::New();
  normalizedActor->GetMapper()->SetInputConnection(
    normalizeCastFilter->GetOutputPort());

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
  rightRenderer->AddActor(normalizedActor);

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
 
PROJECT(ImageNormalize)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageNormalize MACOSX_BUNDLE ImageNormalize.cxx)
 
target_link_libraries(ImageNormalize ${VTK_LIBRARIES})
```

**Download and Build ImageNormalize**

Click [here to download ImageNormalize](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageNormalize.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageNormalize.tar* has been downloaded and extracted,
```
cd ImageNormalize/build 
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
./ImageNormalize
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

