[VTKExamples](/home/)/[Cxx](/Cxx)/Filtering/WarpTo

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestWarpTo.png?raw=true" width="256" />

**WarpTo.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkLineSource.h>
#include <vtkTubeFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkWarpTo.h>

int main(int, char*[])
{
  // Create the RenderWindow, Renderer and both Actors
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Create a line
  vtkSmartPointer<vtkLineSource> lineSource = 
    vtkSmartPointer<vtkLineSource>::New();
  lineSource->SetPoint1(0.0, 0.0, 0.0);
  lineSource->SetPoint2(0.0, 1.0, 0.0);
  lineSource->SetResolution(20);
  lineSource->Update();

  // Create a tube (cylinder) around the line
  vtkSmartPointer<vtkTubeFilter> tubeFilter = 
    vtkSmartPointer<vtkTubeFilter>::New();
  tubeFilter->SetInputConnection(lineSource->GetOutputPort());
  tubeFilter->SetRadius(.01); //default is .5
  tubeFilter->SetNumberOfSides(50);
  tubeFilter->Update();
  
  vtkSmartPointer<vtkWarpTo> warpTo = 
    vtkSmartPointer<vtkWarpTo>::New();
  warpTo->SetInputConnection(tubeFilter->GetOutputPort());
  warpTo->SetPosition(10, 1, 0);
  warpTo->SetScaleFactor(5);
  warpTo->AbsoluteOn();

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(warpTo->GetOutputPort());
  mapper->ScalarVisibilityOff();
  
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  renderer->AddActor(actor);

  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(WarpTo)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(WarpTo MACOSX_BUNDLE WarpTo.cxx)
 
target_link_libraries(WarpTo ${VTK_LIBRARIES})
```

**Download and Build WarpTo**

Click [here to download WarpTo](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/WarpTo.tar) and its *CMakeLists.txt* file.
Once the *tarball WarpTo.tar* has been downloaded and extracted,
```
cd WarpTo/build 
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
./WarpTo
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

