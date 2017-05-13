[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageHybridMedian2D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageHybridMedian2D.png?raw=true" width="256" />

### Description
This example reads in an image and performs median filtering on it. The input and output are displayed.

**ImageHybridMedian2D.cxx**
```c++
#include <vtkImageActor.h>
#include <vtkImageCast.h>
#include <vtkImageMapper3D.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageHybridMedian2D.h>
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

  vtkSmartPointer<vtkImageHybridMedian2D> hybridMedian =
    vtkSmartPointer<vtkImageHybridMedian2D>::New();
  hybridMedian->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> hybridMedianActor =
    vtkSmartPointer<vtkImageActor>::New();
  hybridMedianActor->GetMapper()->SetInputConnection(
    hybridMedian->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double hybridMedianViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> hybridMedianRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  hybridMedianRenderer->SetViewport(hybridMedianViewport);
  hybridMedianRenderer->AddActor(hybridMedianActor);
  hybridMedianRenderer->ResetCamera();
  hybridMedianRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(hybridMedianRenderer);

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
 
PROJECT(ImageHybridMedian2D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageHybridMedian2D MACOSX_BUNDLE ImageHybridMedian2D.cxx)
 
target_link_libraries(ImageHybridMedian2D ${VTK_LIBRARIES})
```

**Download and Build ImageHybridMedian2D**

Click [here to download ImageHybridMedian2D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageHybridMedian2D.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageHybridMedian2D.tar* has been downloaded and extracted,
```
cd ImageHybridMedian2D/build 
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
./ImageHybridMedian2D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

