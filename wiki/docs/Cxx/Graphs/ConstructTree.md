[VTKExamples](Home)/[Cxx](Cxx)/Graphs/ConstructTree

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Graphs/TestConstructTree.png" width="256" />

**ConstructTree.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkGraphLayoutView.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTree.h>

int main (int, char *[] )
{

  vtkSmartPointer<vtkMutableDirectedGraph> graph = 
    vtkSmartPointer<vtkMutableDirectedGraph>::New();
  
  vtkIdType v1 = graph->AddVertex();
  vtkIdType v2 = graph->AddChild(v1);
  graph->AddChild(v1);
  graph->AddChild(v2);
  
  /*
  //equivalent to:
  
  vtkIdType V1 = g->AddVertex();
  vtkIdType V2 = g->AddVertex();
  vtkIdType V3 = g->AddVertex();
  vtkIdType V4 = g->AddVertex();

  g->AddEdge ( V1, V2 );
  g->AddEdge ( V1, V3 );
  g->AddEdge ( V2, V4 );
  */
  
  vtkSmartPointer<vtkTree> tree = 
    vtkSmartPointer<vtkTree>::New();
  bool success = tree->CheckedShallowCopy(graph);
  std::cout << "Success? " << success << std::endl;
  
  vtkSmartPointer<vtkGraphLayoutView> treeLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  treeLayoutView->AddRepresentationFromInput(tree);
  treeLayoutView->SetLayoutStrategyToTree();
  treeLayoutView->ResetCamera();
  treeLayoutView->Render();
  treeLayoutView->GetInteractor()->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ConstructTree)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ConstructTree MACOSX_BUNDLE ConstructTree.cxx)
 
target_link_libraries(ConstructTree ${VTK_LIBRARIES})
```

**Download and Build ConstructTree**

Click [here to download ConstructTree](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ConstructTree.tar) and its *CMakeLists.txt* file.
Once the *tarball ConstructTree.tar* has been downloaded and extracted,
```
cd ConstructTree/build 
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
./ConstructTree
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

