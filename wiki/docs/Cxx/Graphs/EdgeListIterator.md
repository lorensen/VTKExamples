[VTKExamples](/index/)/[Cxx](/Cxx)/Graphs/EdgeListIterator

**EdgeListIterator.cxx**
```c++
#include <vtkMutableUndirectedGraph.h>
#include <vtkSmartPointer.h>
#include <vtkEdgeListIterator.h>

int main(int, char *[])
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

  vtkSmartPointer<vtkEdgeListIterator> edgeListIterator =
      vtkSmartPointer<vtkEdgeListIterator>::New();
  g->GetEdges(edgeListIterator);

  while(edgeListIterator->HasNext())
  {
    vtkEdgeType edge = edgeListIterator->Next();
    std::cout << "Edge: " << edge.Id << " is from "
	      << "Source: " << edge.Source << " to Target: " << edge.Target << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(EdgeListIterator)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(EdgeListIterator MACOSX_BUNDLE EdgeListIterator.cxx)
 
target_link_libraries(EdgeListIterator ${VTK_LIBRARIES})
```

**Download and Build EdgeListIterator**

Click [here to download EdgeListIterator](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/EdgeListIterator.tar) and its *CMakeLists.txt* file.
Once the *tarball EdgeListIterator.tar* has been downloaded and extracted,
```
cd EdgeListIterator/build 
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
./EdgeListIterator
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

