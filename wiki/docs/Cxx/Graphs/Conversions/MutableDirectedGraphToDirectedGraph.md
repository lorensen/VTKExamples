[VTKExamples](Home)/[Cxx](Cxx)/Graphs/Conversions/MutableDirectedGraphToDirectedGraph

**MutableDirectedGraphToDirectedGraph.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkDirectedGraph.h>

int main (int, char *[])
{

  //create a graph
  vtkSmartPointer<vtkMutableDirectedGraph> mdg =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();

  //add 4 vertices to the graph
  vtkIdType v1 = mdg->AddVertex();
  vtkIdType v2 = mdg->AddVertex();
  vtkIdType v3 = mdg->AddVertex();
  vtkIdType v4 = mdg->AddVertex();

  //add 3 edges to the graph
  mdg->AddEdge ( v1, v2 );
  mdg->AddEdge ( v1, v3 );
  mdg->AddEdge ( v1, v4 );

  //create 4 points - one for each vertex
  vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 0.0, 2.0);

  //add the coordinates of the points to the graph
  mdg->SetPoints(points);

  std::cout << "MDG: " << std::endl;
  std::cout << "Type: " << mdg->GetClassName() << std::endl;
  std::cout << "Vertices: " << mdg->GetNumberOfVertices() << std::endl;
  std::cout << "Edges: " << mdg->GetNumberOfEdges() << std::endl;

  vtkSmartPointer<vtkDirectedGraph> dg =
      vtkSmartPointer<vtkDirectedGraph>::New();
  if(!dg->CheckedShallowCopy(mdg))
  {
    std::cerr << "Could not convert graph to tree!" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "DG: " << std::endl;
  std::cout << "Type: " << dg->GetClassName() << std::endl;
  std::cout << "Vertices: " << dg->GetNumberOfVertices() << std::endl;
  std::cout << "Edges: " << dg->GetNumberOfEdges() << std::endl;


  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MutableDirectedGraphToDirectedGraph)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MutableDirectedGraphToDirectedGraph MACOSX_BUNDLE MutableDirectedGraphToDirectedGraph.cxx)
 
target_link_libraries(MutableDirectedGraphToDirectedGraph ${VTK_LIBRARIES})
```

**Download and Build MutableDirectedGraphToDirectedGraph**

Click [here to download MutableDirectedGraphToDirectedGraph](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MutableDirectedGraphToDirectedGraph.tar) and its *CMakeLists.txt* file.
Once the *tarball MutableDirectedGraphToDirectedGraph.tar* has been downloaded and extracted,
```
cd MutableDirectedGraphToDirectedGraph/build 
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
./MutableDirectedGraphToDirectedGraph
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

