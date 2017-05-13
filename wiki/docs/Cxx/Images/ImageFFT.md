[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageFFT

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageFFT.png?raw=true" width="256" />

**ImageFFT.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageFFT.h>
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
  
  vtkSmartPointer<vtkImageFFT> fftFilter = 
    vtkSmartPointer<vtkImageFFT>::New();
  fftFilter->SetInputConnection(source->GetOutputPort());
  fftFilter->Update();

  vtkSmartPointer<vtkImageCast> fftCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  fftCastFilter->SetInputConnection(fftFilter->GetOutputPort());
  fftCastFilter->SetOutputScalarTypeToUnsignedChar();
  fftCastFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(source->GetOutputPort());

  vtkSmartPointer<vtkImageActor> fftActor =
    vtkSmartPointer<vtkImageActor>::New();
  fftActor->GetMapper()->SetInputConnection(fftCastFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double fftViewport[4] = {0.5, 0.0, 1.0, 1.0};

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

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(fftRenderer);

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
 
PROJECT(ImageFFT)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageFFT MACOSX_BUNDLE ImageFFT.cxx)
 
target_link_libraries(ImageFFT ${VTK_LIBRARIES})
```

**Download and Build ImageFFT**

Click [here to download ImageFFT](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageFFT.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageFFT.tar* has been downloaded and extracted,
```
cd ImageFFT/build 
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
./ImageFFT
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

