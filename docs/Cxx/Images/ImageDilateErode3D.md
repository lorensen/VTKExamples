[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageDilateErode3D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageDilateErode3D.png?raw=true" width="256" />

### Description
This example reads in a binary image and dilates one value and erodes another (morphological operations).

**ImageDilateErode3D.cxx**
```c++
#include <vtkImageActor.h>
#include <vtkImageCast.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageDilateErode3D.h>
#include <vtkImageThreshold.h>

int main(int argc, char *argv[])
{
  // Handle the arguments
  if( argc < 2 )
  {
    std::cout << "Required arguments: filename.png" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkPNGReader> reader =
    vtkSmartPointer<vtkPNGReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  vtkSmartPointer<vtkImageDilateErode3D> dilateErode =
    vtkSmartPointer<vtkImageDilateErode3D>::New();
  dilateErode->SetInputConnection(reader->GetOutputPort());
  dilateErode->SetDilateValue(0);
  dilateErode->SetErodeValue(255);
  dilateErode->SetKernelSize(5, 5, 3);
  dilateErode->ReleaseDataFlagOff();

  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> openCloseActor =
    vtkSmartPointer<vtkImageActor>::New();
  openCloseActor->GetMapper()->SetInputConnection(dilateErode->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double openCloseViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> dilateErodeRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  dilateErodeRenderer->SetViewport(openCloseViewport);
  dilateErodeRenderer->AddActor(openCloseActor);
  dilateErodeRenderer->ResetCamera();
  dilateErodeRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(dilateErodeRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return  EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageDilateErode3D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageDilateErode3D MACOSX_BUNDLE ImageDilateErode3D.cxx)
 
target_link_libraries(ImageDilateErode3D ${VTK_LIBRARIES})
```

**Download and Build ImageDilateErode3D**

Click [here to download ImageDilateErode3D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageDilateErode3D.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageDilateErode3D.tar* has been downloaded and extracted,
```
cd ImageDilateErode3D/build 
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
./ImageDilateErode3D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

