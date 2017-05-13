[VTKExamples](Home)/[Cxx](Cxx)/Images/ImageRFFT

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Images/TestImageRFFT.png" width="256" />

**ImageRFFT.cxx**
```c++
#include <vtkImageData.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageFFT.h>
#include <vtkImageRFFT.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageMapper3D.h>
#include <vtkImageActor.h>
#include <vtkImageEllipsoidSource.h>
#include <vtkImageCast.h>
#include <vtkJPEGReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkXMLImageDataWriter.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageEllipsoidSource> source =
    vtkSmartPointer<vtkImageEllipsoidSource>::New();
  source->SetWholeExtent(0, 20, 0, 20, 0, 0);
  source->SetCenter(10,10,0);
  source->SetRadius(3,4,0);
  source->Update();
  
  vtkSmartPointer<vtkImageFFT> fftFilter = 
    vtkSmartPointer<vtkImageFFT>::New();
  fftFilter->SetInputConnection(source->GetOutputPort());
  fftFilter->Update();

  vtkSmartPointer<vtkImageCast> fftCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  fftCastFilter->SetInputConnection(fftFilter->GetOutputPort());
  fftCastFilter->SetOutputScalarTypeToUnsignedChar();
  fftCastFilter->Update();
  
  vtkSmartPointer<vtkImageRFFT> rfftFilter =
    vtkSmartPointer<vtkImageRFFT>::New();
  rfftFilter->SetInputConnection(fftFilter->GetOutputPort());
  rfftFilter->Update();

  vtkSmartPointer<vtkImageExtractComponents> extractRealFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractRealFilter->SetInputConnection(rfftFilter->GetOutputPort());
  extractRealFilter->SetComponents(0);
  extractRealFilter->Update();

  vtkSmartPointer<vtkImageCast> rfftCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  rfftCastFilter->SetInputConnection(extractRealFilter->GetOutputPort());
  rfftCastFilter->SetOutputScalarTypeToUnsignedChar();
  rfftCastFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(source->GetOutputPort());

  vtkSmartPointer<vtkImageActor> fftActor =
    vtkSmartPointer<vtkImageActor>::New();
  fftActor->GetMapper()->SetInputConnection(fftCastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> rfftActor =
    vtkSmartPointer<vtkImageActor>::New();
  rfftActor->GetMapper()->SetInputConnection(rfftCastFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.33, 1.0};
  double fftViewport[4] = {0.33, 0.0, 0.66, 1.0};
  double rfftViewport[4] = {0.66, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> fftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  fftRenderer->SetViewport(fftViewport);
  fftRenderer->AddActor(fftActor);
  fftRenderer->ResetCamera();
  fftRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderer> rfftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  rfftRenderer->SetViewport(rfftViewport);
  rfftRenderer->AddActor(rfftActor);
  rfftRenderer->ResetCamera();
  rfftRenderer->SetBackground(.3, .5, .8);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(900, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(fftRenderer);
  renderWindow->AddRenderer(rfftRenderer);

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
 
PROJECT(ImageRFFT)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageRFFT MACOSX_BUNDLE ImageRFFT.cxx)
 
target_link_libraries(ImageRFFT ${VTK_LIBRARIES})
```

**Download and Build ImageRFFT**

Click [here to download ImageRFFT](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageRFFT.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageRFFT.tar* has been downloaded and extracted,
```
cd ImageRFFT/build 
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
./ImageRFFT
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

