[VTKExamples](/home/)/[Cxx](/Cxx)/Graphs/Conversions/TreeToMutableDirectedGraph

**TreeToMutableDirectedGraph.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkDirectedGraph.h>
#include <vtkTree.h>

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

  vtkSmartPointer<vtkTree> tree =
    vtkSmartPointer<vtkTree>::New();
  tree->CheckedShallowCopy(mdg);

  std::cout << "Tree: " << std::endl;
  std::cout << "Type: " << tree->GetClassName() << std::endl;
  std::cout << "Vertices: " << tree->GetNumberOfVertices() << std::endl;
  std::cout << "Edges: " << tree->GetNumberOfEdges() << std::endl;

  vtkSmartPointer<vtkMutableDirectedGraph> mdg2 =
      vtkSmartPointer<vtkMutableDirectedGraph>::New();
  if(!mdg2->CheckedShallowCopy(tree))
  {
    std::cerr << "Could not convert!" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "MDG2: " << std::endl;
  std::cout << "Type: " << mdg2->GetClassName() << std::endl;
  std::cout << "Vertices: " << mdg2->GetNumberOfVertices() << std::endl;
  std::cout << "Edges: " << mdg2->GetNumberOfEdges() << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TreeToMutableDirectedGraph)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TreeToMutableDirectedGraph MACOSX_BUNDLE TreeToMutableDirectedGraph.cxx)
 
target_link_libraries(TreeToMutableDirectedGraph ${VTK_LIBRARIES})
```

**Download and Build TreeToMutableDirectedGraph**

Click [here to download TreeToMutableDirectedGraph](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TreeToMutableDirectedGraph.tar) and its *CMakeLists.txt* file.
Once the *tarball TreeToMutableDirectedGraph.tar* has been downloaded and extracted,
```
cd TreeToMutableDirectedGraph/build 
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
./TreeToMutableDirectedGraph
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

