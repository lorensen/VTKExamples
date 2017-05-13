[VTKExamples](Home)/[Cxx](Cxx)/Graphs/ConstructGraph

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Graphs/TestConstructGraph.png" width="256" />

### Description
This example shows how to construct a simple graph.

**ConstructGraph.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkCircularLayoutStrategy.h>
#include <vtkDataSetAttributes.h>
#include <vtkDoubleArray.h>
#include <vtkGraphLayoutView.h>
#include <vtkIntArray.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g = 
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();
 
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
 
  g->AddEdge ( v1, v2 );
 
  std::cout << "Number of vertices: "
            << g->GetNumberOfVertices() << std::endl;
  std::cout << "Number of edges: "
            << g->GetNumberOfEdges() << std::endl;
 
  g->AddEdge ( v1, v2 );
 
  std::cout << "Number of vertices: "
            << g->GetNumberOfVertices() << std::endl;
  std::cout << "Number of edges: "
            << g->GetNumberOfEdges() << std::endl;
 
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(g);
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ConstructGraph)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ConstructGraph MACOSX_BUNDLE ConstructGraph.cxx)
 
target_link_libraries(ConstructGraph ${VTK_LIBRARIES})
```

**Download and Build ConstructGraph**

Click [here to download ConstructGraph](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ConstructGraph.tar) and its *CMakeLists.txt* file.
Once the *tarball ConstructGraph.tar* has been downloaded and extracted,
```
cd ConstructGraph/build 
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
./ConstructGraph
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

