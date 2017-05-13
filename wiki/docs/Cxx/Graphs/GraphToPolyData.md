[VTKExamples](/home/)/[Cxx](/Cxx)/Graphs/GraphToPolyData

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Graphs/TestGraphToPolyData.png?raw=true" width="256" />

### Description
This example creates a simple graph and then converts it to a polydata for visualization using Paraview.

**GraphToPolyData.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkGraphToPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create a graph
  vtkSmartPointer<vtkMutableUndirectedGraph> g = 
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  // Add 4 vertices to the graph
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  vtkIdType v3 = g->AddVertex();
  vtkIdType v4 = g->AddVertex();

  // Add 3 edges to the graph
  g->AddEdge ( v1, v2 );
  g->AddEdge ( v1, v3 );
  g->AddEdge ( v1, v4 );

  // Create 4 points - one for each vertex
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 0.0, 1.0);
  
  // Add the coordinates of the points to the graph
  g->SetPoints(points);
  
  // Convert the graph to a polydata
  vtkSmartPointer<vtkGraphToPolyData> graphToPolyData = 
      vtkSmartPointer<vtkGraphToPolyData>::New();
  graphToPolyData->SetInput(g);
  graphToPolyData->Update();
  
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(graphToPolyData->GetOutputPort());
 
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
 
PROJECT(GraphToPolyData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GraphToPolyData MACOSX_BUNDLE GraphToPolyData.cxx)
 
target_link_libraries(GraphToPolyData ${VTK_LIBRARIES})
```

**Download and Build GraphToPolyData**

Click [here to download GraphToPolyData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GraphToPolyData.tar) and its *CMakeLists.txt* file.
Once the *tarball GraphToPolyData.tar* has been downloaded and extracted,
```
cd GraphToPolyData/build 
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
./GraphToPolyData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

