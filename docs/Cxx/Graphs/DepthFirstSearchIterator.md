[VTKExamples](/index/)/[Cxx](/Cxx)/Graphs/DepthFirstSearchIterator

### Description
This example traverses a tree in a depth first fashion.

**DepthFirstSearchIterator.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkMutableUndirectedGraph.h>
#include <vtkBoostPrimMinimumSpanningTree.h>
#include <vtkBoostBreadthFirstSearch.h>
#include <vtkTree.h>
#include <vtkDoubleArray.h>
#include <vtkDataSetAttributes.h>
#include <vtkTreeDFSIterator.h>

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
  std::cout << "Original Graph" << std::endl << "----------" << std::endl;
  std::cout << "Number of vertices: "
            << g->GetNumberOfVertices() << std::endl;
  std::cout << "Number of edges: "
            << g->GetNumberOfEdges() << std::endl;

  // Setup the minimum spanning tree filter
  vtkSmartPointer<vtkBoostPrimMinimumSpanningTree> minimumSpanningTreeFilter =
    vtkSmartPointer<vtkBoostPrimMinimumSpanningTree>::New();
  minimumSpanningTreeFilter->SetOriginVertex(v1);
  minimumSpanningTreeFilter->SetInput(g);
  minimumSpanningTreeFilter->SetEdgeWeightArrayName("Weights");

  // Compute the minimum spanning tree
  minimumSpanningTreeFilter->Update();

  // Get the output tree
  vtkSmartPointer<vtkTree> minimumSpanningTree =
    vtkSmartPointer<vtkTree>::New();
  minimumSpanningTree->ShallowCopy(minimumSpanningTreeFilter->GetOutput());

  // Output information about the minimum spanning tree
  std::cout << std::endl;
  std::cout << "Minimum spanning tree" << std::endl
            << "----------" << std::endl;
  std::cout << "Number of vertices: "
            << minimumSpanningTree->GetNumberOfVertices() << std::endl;
  std::cout << "Number of edges: "
            << minimumSpanningTree->GetNumberOfEdges() << std::endl;

  vtkIdType root = minimumSpanningTree->GetRoot();
  std::cout << "Root: " << root << std::endl;

  vtkSmartPointer<vtkTreeDFSIterator> dFS =
    vtkSmartPointer<vtkTreeDFSIterator>::New();
  dFS->SetStartVertex(root);
  dFS->SetTree(minimumSpanningTree);

  // Traverse the tree in a depth first fashion
  while(dFS->HasNext())
  {
    vtkIdType NextVertex = dFS->Next();
    std::cout << "Next vertex: "
              << NextVertex
              << " level: "
              << minimumSpanningTree->GetLevel(NextVertex)
              << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DepthFirstSearchIterator)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DepthFirstSearchIterator MACOSX_BUNDLE DepthFirstSearchIterator.cxx)
 
target_link_libraries(DepthFirstSearchIterator ${VTK_LIBRARIES})
```

**Download and Build DepthFirstSearchIterator**

Click [here to download DepthFirstSearchIterator](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DepthFirstSearchIterator.tar) and its *CMakeLists.txt* file.
Once the *tarball DepthFirstSearchIterator.tar* has been downloaded and extracted,
```
cd DepthFirstSearchIterator/build 
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
./DepthFirstSearchIterator
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

