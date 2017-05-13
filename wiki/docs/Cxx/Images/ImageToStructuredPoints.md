[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageToStructuredPoints

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageToStructuredPoints.png?raw=true" width="256" />

**ImageToStructuredPoints.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkStructuredPoints.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageToStructuredPoints.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> source =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetExtent(0, 20, 0, 20, 0, 0);
  source->SetScalarTypeToUnsignedChar();
  source->SetNumberOfScalarComponents(3);
  source->SetDrawColor(127,127,127);
  source->FillBox(0,20,0,20);
  source->SetDrawColor(255,127,127);
  source->FillBox(0,15,0,20);
  source->Update();

  vtkSmartPointer<vtkImageToStructuredPoints> convertFilter =
    vtkSmartPointer<vtkImageToStructuredPoints>::New();
  convertFilter->SetInputConnection(source->GetOutputPort());
  convertFilter->Update();

//  vtkStructuredPoints* structuredPoints = convertFilter->GetStructuredPointsOutput();

  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(convertFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageToStructuredPoints)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageToStructuredPoints MACOSX_BUNDLE ImageToStructuredPoints.cxx)
 
target_link_libraries(ImageToStructuredPoints ${VTK_LIBRARIES})
```

**Download and Build ImageToStructuredPoints**

Click [here to download ImageToStructuredPoints](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageToStructuredPoints.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageToStructuredPoints.tar* has been downloaded and extracted,
```
cd ImageToStructuredPoints/build 
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
./ImageToStructuredPoints
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

