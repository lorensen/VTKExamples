[VTKExamples](/home/)/[Cxx](/Cxx)/Images/ImageMathematics

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageMathematics.png?raw=true" width="256" />

**ImageMathematics.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageMapper3D.h>
#include <vtkMath.h>
#include <vtkImageData.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageMathematics.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetNumberOfScalarComponents(3);
  imageSource->SetScalarTypeToUnsignedChar();
  imageSource->SetExtent(0, 4, 0, 4, 0, 0);
  imageSource->SetDrawColor(100.0, 0, 0);
  imageSource->FillBox(0, 4, 0, 4);
  imageSource->Update();
  
  vtkSmartPointer<vtkImageMathematics> imageMath = 
    vtkSmartPointer<vtkImageMathematics>::New();
  imageMath->SetOperationToMultiplyByK();
  imageMath->SetConstantK(2.0);
  imageMath->SetInputConnection(imageSource->GetOutputPort());
  imageMath->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    imageSource->GetOutputPort());

  vtkSmartPointer<vtkImageActor> mathActor =
    vtkSmartPointer<vtkImageActor>::New();
  mathActor->GetMapper()->SetInputConnection(
    imageMath->GetOutputPort());

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

  vtkSmartPointer<vtkRenderer> mathRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  mathRenderer->SetViewport(rightViewport);
  mathRenderer->AddActor(mathActor);
  mathRenderer->ResetCamera();
  mathRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(mathRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageMathematics)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageMathematics MACOSX_BUNDLE ImageMathematics.cxx)
 
target_link_libraries(ImageMathematics ${VTK_LIBRARIES})
```

**Download and Build ImageMathematics**

Click [here to download ImageMathematics](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageMathematics.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageMathematics.tar* has been downloaded and extracted,
```
cd ImageMathematics/build 
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
./ImageMathematics
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

