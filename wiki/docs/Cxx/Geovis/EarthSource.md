[VTKExamples](/home/)/[Cxx](/Cxx)/Geovis/EarthSource

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Geovis/TestEarthSource.png?raw=true" width="256" />

**EarthSource.cxx**
```c++
#include <vtkEarthSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  
  //Create a sphere
  vtkSmartPointer<vtkEarthSource> earthSource = vtkSmartPointer<vtkEarthSource>::New();
  earthSource->OutlineOff();
  earthSource->Update();
  
  //Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(earthSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(EarthSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(EarthSource MACOSX_BUNDLE EarthSource.cxx)
 
target_link_libraries(EarthSource ${VTK_LIBRARIES})
```

**Download and Build EarthSource**

Click [here to download EarthSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/EarthSource.tar) and its *CMakeLists.txt* file.
Once the *tarball EarthSource.tar* has been downloaded and extracted,
```
cd EarthSource/build 
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
./EarthSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

