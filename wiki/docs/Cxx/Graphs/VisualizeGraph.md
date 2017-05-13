[VTKExamples](/index/)/[Cxx](/Cxx)/Graphs/VisualizeGraph

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Graphs/TestVisualizeGraph.png?raw=true" width="256" />

### Description
This example shows how to construct a graph and visualize it. You can select edges and vertices with the mouse.

**VisualizeGraph.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkGraphLayoutStrategy.h>
#include <vtkGraphLayoutView.h>
#include <vtkGraphWriter.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSimple2DLayoutStrategy.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g = 
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();

  g->AddEdge(v1, v2);
  g->AddEdge(v1, v2);
  
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(g);
  graphLayoutView->SetLayoutStrategy("Simple 2D");
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  
  vtkSimple2DLayoutStrategy::SafeDownCast(graphLayoutView->GetLayoutStrategy())->SetRandomSeed(0);
  graphLayoutView->GetInteractor()->Start();
     
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(VisualizeGraph)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VisualizeGraph MACOSX_BUNDLE VisualizeGraph.cxx)
 
target_link_libraries(VisualizeGraph ${VTK_LIBRARIES})
```

**Download and Build VisualizeGraph**

Click [here to download VisualizeGraph](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VisualizeGraph.tar) and its *CMakeLists.txt* file.
Once the *tarball VisualizeGraph.tar* has been downloaded and extracted,
```
cd VisualizeGraph/build 
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
./VisualizeGraph
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

