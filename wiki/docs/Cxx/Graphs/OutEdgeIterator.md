[VTKExamples](/index/)/[Cxx](/Cxx)/Graphs/OutEdgeIterator

**OutEdgeIterator.cxx**
```c++
#include <vtkMutableUndirectedGraph.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkSmartPointer.h>
#include <vtkOutEdgeIterator.h>

static void Undirected();
static void Directed();

int main(int, char *[])
{
  Undirected();
  Directed();

  return EXIT_SUCCESS;
}

void Undirected()
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  // Create a graph
  vtkIdType v0 = g->AddVertex();
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();

  g->AddEdge(v0, v1);
  g->AddEdge(v1, v2);
  g->AddEdge(v0, v2);

  // Find all outgoing edges connected to a vertex
  vtkSmartPointer<vtkOutEdgeIterator> it =
    vtkSmartPointer<vtkOutEdgeIterator>::New();
  g->GetOutEdges(0, it); // Get the edges connected to vertex 0

  while(it->HasNext())
  {
    vtkOutEdgeType edge = it->Next();
    std::cout << "Edge id: " << edge.Id << " Target: " << edge.Target << std::endl;
  }
}

void Directed()
{
  vtkSmartPointer<vtkMutableDirectedGraph> g =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();

  // Create a graph
  vtkIdType v0 = g->AddVertex();
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();

  g->AddEdge(v1, v0);
  g->AddEdge(v2, v0);

  {
  std::cout << "Finding edges connected to vertex 0" << std::endl;
  vtkSmartPointer<vtkOutEdgeIterator> it =
    vtkSmartPointer<vtkOutEdgeIterator>::New();
  g->GetOutEdges(0, it);

  while(it->HasNext())
  {
    vtkOutEdgeType edge = it->Next();
    std::cout << "Edge id: " << edge.Id << " Target: " << edge.Target << std::endl;
  }

  std::cout << "Nothing should be output, vertex 0 has no outgoing edges!" << std::endl;
  }

  {
  std::cout << "Finding edges connected to vertex 1" << std::endl;
  vtkSmartPointer<vtkOutEdgeIterator> it =
    vtkSmartPointer<vtkOutEdgeIterator>::New();
  g->GetOutEdges(1, it);

  while(it->HasNext())
  {
    vtkOutEdgeType edge = it->Next();
    std::cout << "Edge id: " << edge.Id << " Target: " << edge.Target << std::endl;
  }
  }

}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(OutEdgeIterator)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(OutEdgeIterator MACOSX_BUNDLE OutEdgeIterator.cxx)
 
target_link_libraries(OutEdgeIterator ${VTK_LIBRARIES})
```

**Download and Build OutEdgeIterator**

Click [here to download OutEdgeIterator](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/OutEdgeIterator.tar) and its *CMakeLists.txt* file.
Once the *tarball OutEdgeIterator.tar* has been downloaded and extracted,
```
cd OutEdgeIterator/build 
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
./OutEdgeIterator
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

