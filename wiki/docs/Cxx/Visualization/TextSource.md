[VTKExamples](Home)/[Cxx](Cxx)/Visualization/TextSource

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestTextSource.png" width="256" />

### Description
This example displays a 3D polygonal text saying "Hello", using the 9x15 font from [Window System|X Windows]]. That is a raster (pixelized) font, so characters are formed by converting the pixels on each character into quadrilaterals. {{class|vtkVectorText}} generates higher quality polygonal representations of text, so it is recommended instead -- see [[../VectorText]]([wikipedia:X) for an example of this.

**TextSource.cxx**
```c++
#include <vtkTextSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create text
  vtkSmartPointer<vtkTextSource> textSource = 
    vtkSmartPointer<vtkTextSource>::New();
  textSource->SetText("Hello");
  textSource->SetForegroundColor(1.0, 0.0, 0.0);
  textSource->BackingOff();
  textSource->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(textSource->GetOutputPort());

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
  renderer->SetBackground(1,1,1); // Background color white

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TextSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TextSource MACOSX_BUNDLE TextSource.cxx)
 
target_link_libraries(TextSource ${VTK_LIBRARIES})
```

**Download and Build TextSource**

Click [here to download TextSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TextSource.tar) and its *CMakeLists.txt* file.
Once the *tarball TextSource.tar* has been downloaded and extracted,
```
cd TextSource/build 
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
./TextSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

