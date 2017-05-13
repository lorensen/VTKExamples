[VTKExamples](Home)/[Cxx](Cxx)/Graphs/MinimumSpanningTree

### Description
This example shows how to find the minimum spanning tree. The input graph is:
 []([Image:3_vertex_fully_connected_graph.svg]) 
and the minimum spanning tree computed is 
[]([Image:Minimum_spanning_tree.svg]).

You must have compiled VTK with VTK_USE_BOOST=ON to use this functionality. You must also link to vtkInfovis.

**MinimumSpanningTree.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkBoostPrimMinimumSpanningTree.h>
#include <vtkDataSetAttributes.h>
#include <vtkDoubleArray.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkTree.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g = 
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();
  
  // Create 3 vertices
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  vtkIdType v3 = g->AddVertex();
  
  // Create a fully connected graph
  g->AddEdge(v1, v2);
  g->AddEdge(v2, v3);
  g->AddEdge(v1, v3);
  
  // Create the edge weight array
  vtkSmartPointer<vtkDoubleArray> weights = 
    vtkSmartPointer<vtkDoubleArray>::New();
  weights->SetNumberOfComponents(1);
  weights->SetName("Weights");
  
  // Set the edge weights
  weights->InsertNextValue(1.0);
  weights->InsertNextValue(1.0);
  weights->InsertNextValue(2.0);
  
  // Add the edge weight array to the graph
  g->GetEdgeData()->AddArray(weights);
  
  // Output original graph info
  std::cout << "Number of vertices: "
            << g->GetNumberOfVertices() << std::endl;
  std::cout << "Number of edges: "
            << g->GetNumberOfEdges() << std::endl;
  g->Dump();

  // Setup the minimum spanning tree filter
  vtkSmartPointer<vtkBoostPrimMinimumSpanningTree> minimumSpanningTreeFilter = 
    vtkSmartPointer<vtkBoostPrimMinimumSpanningTree>::New();
  minimumSpanningTreeFilter->SetOriginVertex(v1);
  minimumSpanningTreeFilter->SetInput(g);
  minimumSpanningTreeFilter->SetEdgeWeightArrayName("Weights");
  
  // Compute the minimum spanning tree
  minimumSpanningTreeFilter->Update();
  
  // Get the output tree
  vtkSmartPointer<vtkTree> minimumSpanningTree = vtkSmartPointer<vtkTree>::New();
  minimumSpanningTree->ShallowCopy(minimumSpanningTreeFilter->GetOutput());
  
  // Output information about the minimum spanning tree
  std::cout << "Number of vertices: "
            << minimumSpanningTree->GetNumberOfVertices() << std::endl;
  std::cout << "Number of edges: "
            << minimumSpanningTree->GetNumberOfEdges() << std::endl;
  minimumSpanningTree->Dump();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MinimumSpanningTree)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MinimumSpanningTree MACOSX_BUNDLE MinimumSpanningTree.cxx)
 
target_link_libraries(MinimumSpanningTree ${VTK_LIBRARIES})
```

**Download and Build MinimumSpanningTree**

Click [here to download MinimumSpanningTree](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MinimumSpanningTree.tar) and its *CMakeLists.txt* file.
Once the *tarball MinimumSpanningTree.tar* has been downloaded and extracted,
```
cd MinimumSpanningTree/build 
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
./MinimumSpanningTree
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

