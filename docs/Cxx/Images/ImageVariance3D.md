[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageVariance3D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageVariance3D.png?raw=true" width="256" />

**ImageVariance3D.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageVariance3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
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

  vtkSmartPointer<vtkImageVariance3D> varianceFilter = 
    vtkSmartPointer<vtkImageVariance3D>::New();
  varianceFilter->SetInputConnection(source->GetOutputPort());
  varianceFilter->SetKernelSize (5,4,3);
  varianceFilter->Update();

  vtkSmartPointer<vtkImageCast> varianceCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  varianceCastFilter->SetOutputScalarTypeToFloat();
  varianceCastFilter->SetInputConnection(varianceFilter->GetOutputPort());
  varianceCastFilter->Update();
    
   // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    source->GetOutputPort());

  vtkSmartPointer<vtkImageActor> varianceActor =
    vtkSmartPointer<vtkImageActor>::New();
  varianceActor->GetMapper()->SetInputConnection(
    varianceCastFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double varianceViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> varianceRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  varianceRenderer->SetViewport(varianceViewport);
  varianceRenderer->AddActor(varianceActor);
  varianceRenderer->ResetCamera();
  varianceRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(varianceRenderer);

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
 
PROJECT(ImageVariance3D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageVariance3D MACOSX_BUNDLE ImageVariance3D.cxx)
 
target_link_libraries(ImageVariance3D ${VTK_LIBRARIES})
```

**Download and Build ImageVariance3D**

Click [here to download ImageVariance3D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageVariance3D.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageVariance3D.tar* has been downloaded and extracted,
```
cd ImageVariance3D/build 
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
./ImageVariance3D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

