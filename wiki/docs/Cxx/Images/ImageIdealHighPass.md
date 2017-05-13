[VTKExamples](/home/)/[Cxx](/Cxx)/Images/ImageIdealHighPass

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageIdealHighPass.png?raw=true" width="256" />

**ImageIdealHighPass.cxx**
```c++
#include <vtkImageExtractComponents.h>
#include <vtkImageData.h>
#include <vtkImageFFT.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkImageIdealHighPass.h>
#include <vtkImageShiftScale.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageSlice.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageEllipsoidSource.h>
#include <vtkImageCast.h>
#include <vtkImageRFFT.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageMandelbrotSource> mandelbrotSource =
          vtkSmartPointer<vtkImageMandelbrotSource>::New();
  mandelbrotSource->Update();

  // Display the original image
  vtkSmartPointer<vtkImageCast> originalCastFilter =
          vtkSmartPointer<vtkImageCast>::New();
  originalCastFilter->SetInputConnection(mandelbrotSource->GetOutputPort());
  originalCastFilter->SetOutputScalarTypeToUnsignedChar();
  originalCastFilter->Update();
  
  vtkSmartPointer<vtkImageSliceMapper> originalSliceMapper =
          vtkSmartPointer<vtkImageSliceMapper>::New();
  originalSliceMapper->SetInputConnection(originalCastFilter->GetOutputPort());
  
  vtkSmartPointer<vtkImageSlice> originalSlice =
          vtkSmartPointer<vtkImageSlice>::New();
  originalSlice->SetMapper(originalSliceMapper);

  // Compute the FFT of the image
  vtkSmartPointer<vtkImageFFT> fftFilter =
          vtkSmartPointer<vtkImageFFT>::New();
  fftFilter->SetInputConnection(originalCastFilter->GetOutputPort());
  fftFilter->Update();

  // High pass filter the FFT
  vtkSmartPointer<vtkImageIdealHighPass> highPassFilter =
          vtkSmartPointer<vtkImageIdealHighPass>::New();
  highPassFilter->SetInputConnection(fftFilter->GetOutputPort());
  highPassFilter->SetXCutOff(.1);
  highPassFilter->SetYCutOff(.1);
  highPassFilter->Update();

  // Compute the IFFT of the high pass filtered image
  vtkSmartPointer<vtkImageRFFT> rfftFilter =
          vtkSmartPointer<vtkImageRFFT>::New();
  rfftFilter->SetInputConnection(highPassFilter->GetOutputPort());
  rfftFilter->Update();

  vtkSmartPointer<vtkImageExtractComponents> extractRealFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractRealFilter->SetInputConnection(rfftFilter->GetOutputPort());
  extractRealFilter->SetComponents(0);
  extractRealFilter->Update();

  vtkSmartPointer<vtkImageShiftScale> shiftScaleFilter =
    vtkSmartPointer<vtkImageShiftScale>::New();
  shiftScaleFilter->SetOutputScalarTypeToUnsignedChar();
  shiftScaleFilter->SetInputConnection(extractRealFilter->GetOutputPort());
  shiftScaleFilter->SetShift(-1.0f * extractRealFilter->GetOutput()->GetScalarRange()[0]); // brings the lower bound to 0
  float oldRange = extractRealFilter->GetOutput()->GetScalarRange()[1] -
          extractRealFilter->GetOutput()->GetScalarRange()[0];
  float newRange = 100; // We want the output [0,100] (the same as the original image)
  shiftScaleFilter->SetScale(newRange/oldRange);
  shiftScaleFilter->Update();

  // Cast the output back to unsigned char
  vtkSmartPointer<vtkImageCast> outputCastFilter =
          vtkSmartPointer<vtkImageCast>::New();
  outputCastFilter->SetInputConnection(shiftScaleFilter->GetOutputPort());
  outputCastFilter->SetOutputScalarTypeToUnsignedChar();
  outputCastFilter->Update();

  // Display the high pass filtered image
  vtkSmartPointer<vtkImageSliceMapper> highPassSliceMapper =
          vtkSmartPointer<vtkImageSliceMapper>::New();
  highPassSliceMapper->SetInputConnection(outputCastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageSlice> highPassSlice =
          vtkSmartPointer<vtkImageSlice>::New();
  highPassSlice->SetMapper(highPassSliceMapper);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double highPassViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddViewProp(originalSlice);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> highPassRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  highPassRenderer->SetViewport(highPassViewport);
  highPassRenderer->AddViewProp(highPassSlice);
  highPassRenderer->ResetCamera();
  highPassRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(highPassRenderer);

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
 
PROJECT(ImageIdealHighPass)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageIdealHighPass MACOSX_BUNDLE ImageIdealHighPass.cxx)
 
target_link_libraries(ImageIdealHighPass ${VTK_LIBRARIES})
```

**Download and Build ImageIdealHighPass**

Click [here to download ImageIdealHighPass](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageIdealHighPass.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageIdealHighPass.tar* has been downloaded and extracted,
```
cd ImageIdealHighPass/build 
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
./ImageIdealHighPass
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

