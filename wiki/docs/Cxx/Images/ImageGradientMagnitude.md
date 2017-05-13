[VTKExamples](/home/)/[Cxx](/Cxx)/Images/ImageGradientMagnitude

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageGradientMagnitude.png?raw=true" width="256" />

**ImageGradientMagnitude.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageGradientMagnitude.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <vtkImageEllipsoidSource.h>
#include <vtkImageCast.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageEllipsoidSource> source = 
    vtkSmartPointer<vtkImageEllipsoidSource>::New();
  source->SetWholeExtent(0, 20, 0, 20, 0, 0);
  source->SetCenter(10,10,0);
  source->SetRadius(3,4,0);
  source->Update();
  
  vtkSmartPointer<vtkImageGradientMagnitude> gradientMagnitudeFilter = 
      vtkSmartPointer<vtkImageGradientMagnitude>::New();
  gradientMagnitudeFilter->SetInputConnection(source->GetOutputPort());
  gradientMagnitudeFilter->Update();

  vtkSmartPointer<vtkImageCast> gradientMagnitudeCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  gradientMagnitudeCastFilter->SetInputConnection(gradientMagnitudeFilter->GetOutputPort());
  gradientMagnitudeCastFilter->SetOutputScalarTypeToUnsignedChar();
  gradientMagnitudeCastFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(source->GetOutputPort());

  vtkSmartPointer<vtkImageActor> gradientMagnitudeActor =
    vtkSmartPointer<vtkImageActor>::New();
  gradientMagnitudeActor->GetMapper()->SetInputConnection(
    gradientMagnitudeCastFilter->GetOutputPort());

   // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double gradientMagnitudeViewport[4] = {0.5, 0.0, 1.0, 1.0};

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
 
PROJECT(ImageGradientMagnitude)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageGradientMagnitude MACOSX_BUNDLE ImageGradientMagnitude.cxx)
 
target_link_libraries(ImageGradientMagnitude ${VTK_LIBRARIES})
```

**Download and Build ImageGradientMagnitude**

Click [here to download ImageGradientMagnitude](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageGradientMagnitude.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageGradientMagnitude.tar* has been downloaded and extracted,
```
cd ImageGradientMagnitude/build 
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
./ImageGradientMagnitude
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

