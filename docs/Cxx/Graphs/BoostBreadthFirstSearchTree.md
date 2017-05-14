[VTKExamples](/index/)/[Cxx](/Cxx)/Graphs/BoostBreadthFirstSearchTree

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Graphs/TestBoostBreadthFirstSearchTree.png?raw=true" width="256" />

**BoostBreadthFirstSearchTree.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkBoostBreadthFirstSearchTree.h>
#include <vtkDataSetAttributes.h>
#include <vtkDoubleArray.h>
#include <vtkGraphLayoutView.h>
#include <vtkIntArray.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTree.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g = 
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();
  
  // Create 5 vertices
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  vtkIdType v3 = g->AddVertex();
  vtkIdType v4 = g->AddVertex();
  vtkIdType v5 = g->AddVertex();
  
  // Create a graph
  g->AddEdge(v1, v2);
  g->AddEdge(v1, v3);
  g->AddEdge(v2, v4);
  g->AddEdge(v4, v5);
  
  vtkSmartPointer<vtkBoostBreadthFirstSearchTree> bfsTree = 
    vtkSmartPointer<vtkBoostBreadthFirstSearchTree>::New();
  bfsTree->SetOriginVertex(v5);
  bfsTree->SetInput(g);
  bfsTree->Update();
  
  {
  // Original graph
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(g);
  graphLayoutView->SetLayoutStrategyToTree();
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();
  }
  
  {
  // BFS tree
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->SetLayoutStrategyToTree();
  graphLayoutView->AddRepresentationFromInput(bfsTree->GetOutput());
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();
  }
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BoostBreadthFirstSearchTree)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BoostBreadthFirstSearchTree MACOSX_BUNDLE BoostBreadthFirstSearchTree.cxx)
 
target_link_libraries(BoostBreadthFirstSearchTree ${VTK_LIBRARIES})
```

**Download and Build BoostBreadthFirstSearchTree**

Click [here to download BoostBreadthFirstSearchTree](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BoostBreadthFirstSearchTree.tar) and its *CMakeLists.txt* file.
Once the *tarball BoostBreadthFirstSearchTree.tar* has been downloaded and extracted,
```
cd BoostBreadthFirstSearchTree/build 
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
./BoostBreadthFirstSearchTree
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

