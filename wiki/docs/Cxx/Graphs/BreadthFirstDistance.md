[VTKExamples](/home/)/[Cxx](/Cxx)/Graphs/BreadthFirstDistance

### Description
This example shows how to get the distance from a vertex to the root vertex.

**BreadthFirstDistance.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkBoostBreadthFirstSearch.h>
#include <vtkDataSetAttributes.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
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
  vtkIdType v4 = g->AddVertex();

  // Create a graph
  g->AddEdge(v1, v2);
  g->AddEdge(v1, v3);
  g->AddEdge(v2, v4);

  vtkSmartPointer<vtkBoostBreadthFirstSearch> BFS =
    vtkSmartPointer<vtkBoostBreadthFirstSearch>::New();
  BFS->SetOriginVertex(v1);
  BFS->SetInput(g);
  BFS->Update();

  vtkIntArray* level = vtkIntArray::SafeDownCast(
    BFS->GetOutput()->GetVertexData()->GetArray("BFS"));
  for(vtkIdType i = 0; i < level->GetNumberOfTuples(); i++)
  {
    std::cout << "id " << i << " : " << level->GetValue(i) << std::endl;
  }
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BreadthFirstDistance)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BreadthFirstDistance MACOSX_BUNDLE BreadthFirstDistance.cxx)
 
target_link_libraries(BreadthFirstDistance ${VTK_LIBRARIES})
```

**Download and Build BreadthFirstDistance**

Click [here to download BreadthFirstDistance](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BreadthFirstDistance.tar) and its *CMakeLists.txt* file.
Once the *tarball BreadthFirstDistance.tar* has been downloaded and extracted,
```
cd BreadthFirstDistance/build 
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
./BreadthFirstDistance
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

