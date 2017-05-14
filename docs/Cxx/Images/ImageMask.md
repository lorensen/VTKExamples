[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageMask

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageMask.png?raw=true" width="256" />

### Description
This example creates an all red image. Then it creates a mask of a small rectangle. The red pixels in this rectangle are copied to the output image, while the rest of the output image is black. The black region could be set to a different color using SetMaskedOutputValue.

**ImageMask.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkJPEGWriter.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageMask.h>
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
  // Create an image of a rectangle
  vtkSmartPointer<vtkImageCanvasSource2D> source = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetScalarTypeToUnsignedChar();
  source->SetNumberOfScalarComponents(3);
  source->SetExtent(0, 200, 0, 200, 0, 0);
  
  // Create a red image
  source->SetDrawColor(255,0,0);
  source->FillBox(0,200,0,200);
  
  source->Update();
  
  // Create a rectanglular mask
  vtkSmartPointer<vtkImageCanvasSource2D> maskSource = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  maskSource->SetScalarTypeToUnsignedChar();
  maskSource->SetNumberOfScalarComponents(1);
  maskSource->SetExtent(0, 200, 0, 200, 0, 0);
  
  // Initialize the mask to black
  maskSource->SetDrawColor(0,0,0);
  maskSource->FillBox(0,200,0,200);
  
  // Create a square
  maskSource->SetDrawColor(255,255,255); //anything non-zero means "make the output pixel equal the input pixel." If the mask is zero, the output pixel is set to MaskedValue
  maskSource->FillBox(100,120,100,120);
  maskSource->Update();

  vtkSmartPointer<vtkImageMask> maskFilter = 
    vtkSmartPointer<vtkImageMask>::New();
  maskFilter->SetInputConnection(0, source->GetOutputPort());
  maskFilter->SetInputConnection(1, maskSource->GetOutputPort());
  maskFilter->SetMaskedOutputValue(0,1,0);
  maskFilter->Update();

  vtkSmartPointer<vtkImageMask> inverseMaskFilter =
    vtkSmartPointer<vtkImageMask>::New();
  inverseMaskFilter->SetInputConnection(0, source->GetOutputPort());
  inverseMaskFilter->SetInputConnection(1, maskSource->GetOutputPort());
  inverseMaskFilter->SetMaskedOutputValue(0,1,0);
  inverseMaskFilter->NotMaskOn();
  inverseMaskFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(source->GetOutputPort());

  vtkSmartPointer<vtkImageActor> maskActor =
    vtkSmartPointer<vtkImageActor>::New();
  maskActor->GetMapper()->SetInputConnection(maskSource->GetOutputPort());

  vtkSmartPointer<vtkImageActor> maskedActor =
    vtkSmartPointer<vtkImageActor>::New();
  maskedActor->GetMapper()->SetInputConnection(maskFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> inverseMaskedActor =
    vtkSmartPointer<vtkImageActor>::New();
  inverseMaskedActor->GetMapper()->SetInputConnection(inverseMaskFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.25, 1.0};
  double maskViewport[4] = {0.25, 0.0, 0.5, 1.0};
  double maskedViewport[4] = {0.5, 0.0, 0.75, 1.0};
  double inverseMaskedViewport[4] = {0.75, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> maskRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  maskRenderer->SetViewport(maskViewport);
  maskRenderer->AddActor(maskActor);
  maskRenderer->ResetCamera();
  maskRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> maskedRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  maskedRenderer->SetViewport(maskedViewport);
  maskedRenderer->AddActor(maskedActor);
  maskedRenderer->ResetCamera();
  maskedRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> inverseMaskedRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  inverseMaskedRenderer->SetViewport(inverseMaskedViewport);
  inverseMaskedRenderer->AddActor(inverseMaskedActor);
  inverseMaskedRenderer->ResetCamera();
  inverseMaskedRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(1000, 250);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(maskRenderer);
  renderWindow->AddRenderer(maskedRenderer);
  renderWindow->AddRenderer(inverseMaskedRenderer);

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
 
PROJECT(ImageMask)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageMask MACOSX_BUNDLE ImageMask.cxx)
 
target_link_libraries(ImageMask ${VTK_LIBRARIES})
```

**Download and Build ImageMask**

Click [here to download ImageMask](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageMask.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageMask.tar* has been downloaded and extracted,
```
cd ImageMask/build 
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
./ImageMask
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

