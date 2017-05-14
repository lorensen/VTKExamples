[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageIslandRemoval2D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageIslandRemoval2D.png?raw=true" width="256" />

### Description
This example creates a small white square and a big white square. We want the ImageIslandRemoval2D to turn the small white square black and leave the big white square alone. 

**ImageIslandRemoval2D.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageIslandRemoval2D.h>
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
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetScalarTypeToUnsignedChar();
  imageSource->SetNumberOfScalarComponents(1);
  imageSource->SetExtent(0, 200, 0, 200, 0, 0);
  
  // Blank the image
  imageSource->SetDrawColor(0.0);
  imageSource->FillBox(0,200,0,200);

  // Draw a small box
  imageSource->SetDrawColor(255.0);
  imageSource->FillBox(100, 105, 100, 105);

  // Draw a large box
  imageSource->SetDrawColor(255.0);
  imageSource->FillBox(150, 170, 150, 170);
  
  imageSource->Update();

  vtkSmartPointer<vtkImageIslandRemoval2D> islandRemovalFilter = 
    vtkSmartPointer<vtkImageIslandRemoval2D>::New();
  islandRemovalFilter->SetAreaThreshold(50);
  islandRemovalFilter->SetIslandValue(255.0);
  islandRemovalFilter->SetReplaceValue(0.0);
  islandRemovalFilter->SetInputConnection(imageSource->GetOutputPort());
  islandRemovalFilter->Update();

  // Visualize
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(imageSource->GetOutputPort());

  vtkSmartPointer<vtkImageActor> islandRemovalActor =
    vtkSmartPointer<vtkImageActor>::New();
  islandRemovalActor->GetMapper()->SetInputConnection(
    islandRemovalFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double islandRemovalViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> islandRemovalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  islandRemovalRenderer->SetViewport(islandRemovalViewport);
  islandRemovalRenderer->AddActor(islandRemovalActor);
  islandRemovalRenderer->ResetCamera();
  islandRemovalRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(islandRemovalRenderer);

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
 
PROJECT(ImageIslandRemoval2D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageIslandRemoval2D MACOSX_BUNDLE ImageIslandRemoval2D.cxx)
 
target_link_libraries(ImageIslandRemoval2D ${VTK_LIBRARIES})
```

**Download and Build ImageIslandRemoval2D**

Click [here to download ImageIslandRemoval2D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageIslandRemoval2D.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageIslandRemoval2D.tar* has been downloaded and extracted,
```
cd ImageIslandRemoval2D/build 
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
./ImageIslandRemoval2D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

