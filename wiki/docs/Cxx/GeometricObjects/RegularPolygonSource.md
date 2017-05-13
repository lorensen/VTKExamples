[VTKExamples](/home/)/[Cxx](/Cxx)/GeometricObjects/RegularPolygonSource

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestRegularPolygonSource.png?raw=true" width="256" />

### Description
 
This example creates a pentagon.

**RegularPolygonSource.cxx**
```c++
#include <vtkRegularPolygonSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
 
int main(int , char *[])
{
  // Create a pentagon
  vtkSmartPointer<vtkRegularPolygonSource> polygonSource = 
    vtkSmartPointer<vtkRegularPolygonSource>::New();
  
  //polygonSource->GeneratePolygonOff();
  polygonSource->SetNumberOfSides(5);
  polygonSource->SetRadius(5);
  polygonSource->SetCenter(0,0,0);
  polygonSource->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(polygonSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(actor);
  renderer->SetBackground(.3,.3,.5); // Background color purple
 
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RegularPolygonSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RegularPolygonSource MACOSX_BUNDLE RegularPolygonSource.cxx)
 
target_link_libraries(RegularPolygonSource ${VTK_LIBRARIES})
```

**Download and Build RegularPolygonSource**

Click [here to download RegularPolygonSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RegularPolygonSource.tar) and its *CMakeLists.txt* file.
Once the *tarball RegularPolygonSource.tar* has been downloaded and extracted,
```
cd RegularPolygonSource/build 
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
./RegularPolygonSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

