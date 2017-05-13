[VTKExamples](/home/)/[Cxx](/Cxx)/Images/ImageLaplacian

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageLaplacian.png?raw=true" width="256" />

**ImageLaplacian.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkImageLaplacian.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageCast.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageMandelbrotSource> source = 
    vtkSmartPointer<vtkImageMandelbrotSource>::New();
  source->Update();

  vtkSmartPointer<vtkImageCast> castOriginal =
    vtkSmartPointer<vtkImageCast>::New();
  castOriginal->SetInputConnection(source->GetOutputPort());
  castOriginal->SetOutputScalarTypeToFloat();
  castOriginal->Update();
  
  vtkSmartPointer<vtkImageLaplacian> laplacianFilter = 
    vtkSmartPointer<vtkImageLaplacian>::New();
  laplacianFilter->SetInputConnection(source->GetOutputPort());
  laplacianFilter->Update();

  vtkSmartPointer<vtkImageCast> castLaplacian =
    vtkSmartPointer<vtkImageCast>::New();
  castLaplacian->SetInputConnection(laplacianFilter->GetOutputPort());
  castLaplacian->SetOutputScalarTypeToFloat();
  castLaplacian->Update();
  
  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};
  
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    castOriginal->GetOutputPort());

  vtkSmartPointer<vtkImageActor> laplacianActor =
    vtkSmartPointer<vtkImageActor>::New();
  laplacianActor->GetMapper()->SetInputConnection(
    castLaplacian->GetOutputPort());
  
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600,300);
  
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle( style );

  interactor->SetRenderWindow(renderWindow);

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(leftViewport);

  vtkSmartPointer<vtkRenderer> laplacianRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  laplacianRenderer->SetViewport(rightViewport);
  
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(laplacianRenderer);

  originalRenderer->AddActor(originalActor);
  laplacianRenderer->AddActor(laplacianActor);

  originalRenderer->ResetCamera();
  laplacianRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageLaplacian)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageLaplacian MACOSX_BUNDLE ImageLaplacian.cxx)
 
target_link_libraries(ImageLaplacian ${VTK_LIBRARIES})
```

**Download and Build ImageLaplacian**

Click [here to download ImageLaplacian](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageLaplacian.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageLaplacian.tar* has been downloaded and extracted,
```
cd ImageLaplacian/build 
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
./ImageLaplacian
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

