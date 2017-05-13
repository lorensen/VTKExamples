[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/DijkstraGraphGeodesicPath

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestDijkstraGraphGeodesicPath.png?raw=true" width="256" />

**DijkstraGraphGeodesicPath.cxx**
```c++
#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDijkstraGraphGeodesicPath.h>

int main(int , char *[])
{ 
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  vtkSmartPointer<vtkDijkstraGraphGeodesicPath> dijkstra = 
    vtkSmartPointer<vtkDijkstraGraphGeodesicPath>::New();
  dijkstra->SetInputConnection(sphereSource->GetOutputPort());
  dijkstra->SetStartVertex(0);
  dijkstra->SetEndVertex(10);
  dijkstra->Update();
  
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> pathMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pathMapper->SetInputConnection(dijkstra->GetOutputPort());
 
  vtkSmartPointer<vtkActor> pathActor = 
    vtkSmartPointer<vtkActor>::New();
  pathActor->SetMapper(pathMapper);
  pathActor->GetProperty()->SetColor(1,0,0); // Red
  pathActor->GetProperty()->SetLineWidth(4);
    
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  //Add the actor to the scene
  renderer->AddActor(actor);
  renderer->AddActor(pathActor);
  renderer->SetBackground(.3, .6, .3); // Background color green
 
  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DijkstraGraphGeodesicPath)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DijkstraGraphGeodesicPath MACOSX_BUNDLE DijkstraGraphGeodesicPath.cxx)
 
target_link_libraries(DijkstraGraphGeodesicPath ${VTK_LIBRARIES})
```

**Download and Build DijkstraGraphGeodesicPath**

Click [here to download DijkstraGraphGeodesicPath](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DijkstraGraphGeodesicPath.tar) and its *CMakeLists.txt* file.
Once the *tarball DijkstraGraphGeodesicPath.tar* has been downloaded and extracted,
```
cd DijkstraGraphGeodesicPath/build 
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
./DijkstraGraphGeodesicPath
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

