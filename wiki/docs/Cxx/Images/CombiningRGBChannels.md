[VTKExamples](Home)/[Cxx](Cxx)/Images/CombiningRGBChannels

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Images/TestCombiningRGBChannels.png" width="256" />

### Description
This example creates three images of a square. Each square slightly overlaps the previous square. These three layers are then interpreted as the R, G, and B channel of an RGB image, by the use of {{class|vtkImageAppendComponents}}.

Note that you MUST add 3 inputs or no output will be produced.

For the reverse operation, see []([../ExtractComponents]).

**CombiningRGBChannels.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageAppendComponents.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>

int main(int, char *[])
{
  // Create an image (will be used as the R channel)
  vtkSmartPointer<vtkImageCanvasSource2D> red =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  red->SetScalarTypeToUnsignedChar();
  red->SetNumberOfScalarComponents(1);
  red->SetExtent(0, 100, 0, 100, 0, 0);
  red->SetDrawColor(0, 0, 0, 0);
  red->FillBox(0,100,0,100);
  red->SetDrawColor(255, 0, 0, 0);
  red->FillBox(20,40,20,40);
  red->Update();

  // Create an image (will be used as the G channel)
  vtkSmartPointer<vtkImageCanvasSource2D> green =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  green->SetScalarTypeToUnsignedChar();
  green->SetNumberOfScalarComponents(1);
  green->SetExtent(0, 100, 0, 100, 0, 0);
  green->SetDrawColor(0, 0, 0, 0);
  green->FillBox(0,100,0,100);
  green->SetDrawColor(255, 0, 0, 0);
  green->FillBox(30,50,30,50);
  green->Update();

  // Create an image (will be used as the B channel)
  vtkSmartPointer<vtkImageCanvasSource2D> blue =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  blue->SetScalarTypeToUnsignedChar();
  blue->SetNumberOfScalarComponents(1);
  blue->SetExtent(0, 100, 0, 100, 0, 0);
  blue->SetDrawColor(0, 0, 0, 0);
  blue->FillBox(0,100,0,100);
  blue->SetDrawColor(255, 0, 0, 0);
  blue->FillBox(40,60,40,60);
  blue->Update();

  vtkSmartPointer<vtkImageAppendComponents> appendFilter =
    vtkSmartPointer<vtkImageAppendComponents>::New();
  appendFilter->SetInputConnection(0, red->GetOutputPort());
  appendFilter->AddInputConnection(0, green->GetOutputPort());
  appendFilter->AddInputConnection(0, blue->GetOutputPort());
  appendFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> redActor =
    vtkSmartPointer<vtkImageActor>::New();
  redActor->GetMapper()->SetInputConnection(red->GetOutputPort());

  vtkSmartPointer<vtkImageActor> greenActor =
    vtkSmartPointer<vtkImageActor>::New();
  greenActor->GetMapper()->SetInputConnection(green->GetOutputPort());

  vtkSmartPointer<vtkImageActor> blueActor =
    vtkSmartPointer<vtkImageActor>::New();
  blueActor->GetMapper()->SetInputConnection(blue->GetOutputPort());

  vtkSmartPointer<vtkImageActor> combinedActor =
    vtkSmartPointer<vtkImageActor>::New();
  combinedActor->GetMapper()->SetInputConnection(appendFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double redViewport[4] = {0.0, 0.0, 0.25, 1.0};
  double greenViewport[4] = {0.25, 0.0, 0.5, 1.0};
  double blueViewport[4] = {0.5, 0.0, 0.75, 1.0};
  double combinedViewport[4] = {0.75, 0.0, 1.0, 1.0};
  
  // Setup renderers
  vtkSmartPointer<vtkRenderer> redRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  redRenderer->SetViewport(redViewport);
  redRenderer->AddActor(redActor);
  redRenderer->ResetCamera();
  redRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> greenRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  greenRenderer->SetViewport(greenViewport);
  greenRenderer->AddActor(greenActor);
  greenRenderer->ResetCamera();
  greenRenderer->SetBackground(.4, .5, .7);
  
  vtkSmartPointer<vtkRenderer> blueRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  blueRenderer->SetViewport(blueViewport);
  blueRenderer->AddActor(blueActor);
  blueRenderer->ResetCamera();
  blueRenderer->SetBackground(.4, .5, .8);
  
  vtkSmartPointer<vtkRenderer> combinedRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  combinedRenderer->SetViewport(combinedViewport);
  combinedRenderer->AddActor(combinedActor);
  combinedRenderer->ResetCamera();
  combinedRenderer->SetBackground(.4, .5, .9);

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(1000, 250);
  renderWindow->AddRenderer(redRenderer);
  renderWindow->AddRenderer(greenRenderer);
  renderWindow->AddRenderer(blueRenderer);
  renderWindow->AddRenderer(combinedRenderer);

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
 
PROJECT(CombiningRGBChannels)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CombiningRGBChannels MACOSX_BUNDLE CombiningRGBChannels.cxx)
 
target_link_libraries(CombiningRGBChannels ${VTK_LIBRARIES})
```

**Download and Build CombiningRGBChannels**

Click [here to download CombiningRGBChannels](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CombiningRGBChannels.tar) and its *CMakeLists.txt* file.
Once the *tarball CombiningRGBChannels.tar* has been downloaded and extracted,
```
cd CombiningRGBChannels/build 
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
./CombiningRGBChannels
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

