[VTKExamples](/home/)/[Cxx](/Cxx)/Filtering/VertexGlyphFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestVertexGlyphFilter.png?raw=true" width="256" />

### Description
This example creates a set of points and adds a vertex at each point using vtkVertexGlyphFilter.

**VertexGlyphFilter.cxx**
```c++
#include <vtkVersion.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
 
int main(int , char *[])
{
 
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,1,1);
  points->InsertNextPoint(2,2,2);
 
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
 
  vtkSmartPointer<vtkVertexGlyphFilter> vertexGlyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  vertexGlyphFilter->AddInput(polydata);
#else
  vertexGlyphFilter->AddInputData(polydata);
#endif
  vertexGlyphFilter->Update();
 
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(vertexGlyphFilter->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(3);
  
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
 
PROJECT(VertexGlyphFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VertexGlyphFilter MACOSX_BUNDLE VertexGlyphFilter.cxx)
 
target_link_libraries(VertexGlyphFilter ${VTK_LIBRARIES})
```

**Download and Build VertexGlyphFilter**

Click [here to download VertexGlyphFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VertexGlyphFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball VertexGlyphFilter.tar* has been downloaded and extracted,
```
cd VertexGlyphFilter/build 
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
./VertexGlyphFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

