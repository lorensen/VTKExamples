[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageDivergence

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageDivergence.png?raw=true" width="256" />

**ImageDivergence.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageCast.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageDivergence.h>
#include <vtkImageGradient.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageCorrelation.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageActor.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageMandelbrotSource.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageMandelbrotSource> source =
    vtkSmartPointer<vtkImageMandelbrotSource>::New();
  source->Update();

  vtkSmartPointer<vtkImageCast> originalCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  originalCastFilter->SetInputConnection(source->GetOutputPort());
  originalCastFilter->SetOutputScalarTypeToFloat();
  originalCastFilter->Update();
  
  // Compute the gradient (to produce a vector field)
  vtkSmartPointer<vtkImageGradient> gradientFilter =
    vtkSmartPointer<vtkImageGradient>::New();
  gradientFilter->SetInputConnection(source->GetOutputPort());
  gradientFilter->Update();
  
  vtkSmartPointer<vtkImageDivergence> divergenceFilter = 
    vtkSmartPointer<vtkImageDivergence>::New();
  divergenceFilter->SetInputConnection(gradientFilter->GetOutputPort());
  divergenceFilter->Update();

  vtkSmartPointer<vtkImageCast> divergenceCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  divergenceCastFilter->SetInputConnection(divergenceFilter->GetOutputPort());
  divergenceCastFilter->SetOutputScalarTypeToFloat();
  divergenceCastFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    originalCastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> divergenceActor =
    vtkSmartPointer<vtkImageActor>::New();
  divergenceActor->GetMapper()->SetInputConnection(
    divergenceCastFilter->GetOutputPort());

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

  vtkSmartPointer<vtkRenderer> divergenceRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  divergenceRenderer->SetViewport(rightViewport);
  divergenceRenderer->AddActor(divergenceActor);
  divergenceRenderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600,300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(divergenceRenderer);

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
 
PROJECT(ImageDivergence)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageDivergence MACOSX_BUNDLE ImageDivergence.cxx)
 
target_link_libraries(ImageDivergence ${VTK_LIBRARIES})
```

**Download and Build ImageDivergence**

Click [here to download ImageDivergence](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageDivergence.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageDivergence.tar* has been downloaded and extracted,
```
cd ImageDivergence/build 
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
./ImageDivergence
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

