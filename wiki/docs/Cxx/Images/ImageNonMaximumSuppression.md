[VTKExamples](/home/)/[Cxx](/Cxx)/Images/ImageNonMaximumSuppression

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageNonMaximumSuppression.png?raw=true" width="256" />

**ImageNonMaximumSuppression.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkImageSinusoidSource.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageGradient.h>
#include <vtkImageGradientMagnitude.h>
#include <vtkImageNonMaximumSuppression.h>
#include <vtkImageCast.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkImageSinusoidSource> source =
    vtkSmartPointer<vtkImageSinusoidSource>::New();
  source->Update();

  vtkSmartPointer<vtkImageCast> sourceCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  sourceCastFilter->SetOutputScalarTypeToUnsignedChar();
  sourceCastFilter->SetInputConnection(source->GetOutputPort());
  sourceCastFilter->Update();

  vtkSmartPointer<vtkImageGradient> gradientFilter =
    vtkSmartPointer<vtkImageGradient>::New();
  gradientFilter->SetInputConnection(source->GetOutputPort());

  vtkSmartPointer<vtkImageGradientMagnitude> gradientMagnitudeFilter =
    vtkSmartPointer<vtkImageGradientMagnitude>::New();
  gradientMagnitudeFilter->SetInputConnection(source->GetOutputPort());

  vtkSmartPointer<vtkImageCast> gradientMagnitudeCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  gradientMagnitudeCastFilter->SetOutputScalarTypeToUnsignedChar();
  gradientMagnitudeCastFilter->SetInputConnection(gradientMagnitudeFilter->GetOutputPort());
  gradientMagnitudeCastFilter->Update();
  
  vtkSmartPointer<vtkImageNonMaximumSuppression> suppressionFilter =
    vtkSmartPointer<vtkImageNonMaximumSuppression>::New();
  suppressionFilter->SetInputConnection(
    0, gradientMagnitudeFilter->GetOutputPort());
  suppressionFilter->SetInputConnection(
    1, gradientFilter->GetOutputPort());
  suppressionFilter->SetDimensionality(2);
  suppressionFilter->Update();

  vtkSmartPointer<vtkImageCast> suppressionCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  suppressionCastFilter->SetOutputScalarTypeToUnsignedChar();
  suppressionCastFilter->SetInputConnection(suppressionFilter->GetOutputPort());
  suppressionCastFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    sourceCastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> gradientMagnitudeActor =
    vtkSmartPointer<vtkImageActor>::New();
  gradientMagnitudeActor->GetMapper()->SetInputConnection(
    gradientMagnitudeCastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> suppressionActor =
    vtkSmartPointer<vtkImageActor>::New();
  suppressionActor->GetMapper()->SetInputConnection(
    suppressionCastFilter->GetOutputPort());
  
  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.33, 1.0};
  double gradientMagnitudeViewport[4] = {0.33, 0.0, 0.66, 1.0};
  double suppressionViewport[4] = {0.66, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> gradientMagnitudeRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  gradientMagnitudeRenderer->SetViewport(gradientMagnitudeViewport);
  gradientMagnitudeRenderer->AddActor(gradientMagnitudeActor);
  gradientMagnitudeRenderer->ResetCamera();
  gradientMagnitudeRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderer> suppressionRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  suppressionRenderer->SetViewport(suppressionViewport);
  suppressionRenderer->AddActor(suppressionActor);
  suppressionRenderer->ResetCamera();
  suppressionRenderer->SetBackground(.3, .5, .8);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(900, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(gradientMagnitudeRenderer);
  renderWindow->AddRenderer(suppressionRenderer);

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
 
PROJECT(ImageNonMaximumSuppression)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageNonMaximumSuppression MACOSX_BUNDLE ImageNonMaximumSuppression.cxx)
 
target_link_libraries(ImageNonMaximumSuppression ${VTK_LIBRARIES})
```

**Download and Build ImageNonMaximumSuppression**

Click [here to download ImageNonMaximumSuppression](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageNonMaximumSuppression.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageNonMaximumSuppression.tar* has been downloaded and extracted,
```
cd ImageNonMaximumSuppression/build 
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
./ImageNonMaximumSuppression
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

