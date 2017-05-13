[VTKExamples](/home/)/[Cxx](/Cxx)/Graphs/InEdgeIterator

**InEdgeIterator.cxx**
```c++
#include <vtkMutableUndirectedGraph.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkSmartPointer.h>
#include <vtkInEdgeIterator.h>

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

  // Find all incoming edges connected to a vertex
  vtkSmartPointer<vtkInEdgeIterator> it =
    vtkSmartPointer<vtkInEdgeIterator>::New();
  g->GetInEdges(0, it);

  while(it->HasNext())
  {
    vtkInEdgeType edge = it->Next();
    std::cout << "Edge id: " << edge.Id << " Source: " << edge.Source << std::endl;
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

  g->AddEdge(v0, v1);
  g->AddEdge(v0, v2);

  {
  std::cout << "Finding edges connected to vertex 0" << std::endl;
  vtkSmartPointer<vtkInEdgeIterator> it =
    vtkSmartPointer<vtkInEdgeIterator>::New();
  g->GetInEdges(0, it);

  while(it->HasNext())
  {
    vtkInEdgeType edge = it->Next();
    std::cout << "Edge id: " << edge.Id << " " << "Source: " << edge.Source << std::endl;
  }

  std::cout << "Nothing should be output, vertex 0 has no incoming edges!" << std::endl;
  }

  {
  std::cout << "Finding edges connected to vertex 1" << std::endl;
  vtkSmartPointer<vtkInEdgeIterator> it =
    vtkSmartPointer<vtkInEdgeIterator>::New();
  g->GetInEdges(1, it);

  while(it->HasNext())
  {
    vtkInEdgeType edge = it->Next();
    std::cout << "Edge id: " << edge.Id << " " << "Source: " << edge.Source << std::endl;
  }
  }

}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(InEdgeIterator)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(InEdgeIterator MACOSX_BUNDLE InEdgeIterator.cxx)
 
target_link_libraries(InEdgeIterator ${VTK_LIBRARIES})
```

**Download and Build InEdgeIterator**

Click [here to download InEdgeIterator](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/InEdgeIterator.tar) and its *CMakeLists.txt* file.
Once the *tarball InEdgeIterator.tar* has been downloaded and extracted,
```
cd InEdgeIterator/build 
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
./InEdgeIterator
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

