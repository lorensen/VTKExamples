[VTKExamples](/home/)/[Cxx](/Cxx)/Graphs/TreeBFSIterator

**TreeBFSIterator.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkTree.h>
#include <vtkTreeBFSIterator.h>

int main(int argc, char *argv[])
{
  //create a tree
  vtkSmartPointer<vtkMutableDirectedGraph> g =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();

  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  vtkIdType v3 = g->AddVertex();

  g->AddEdge(v1, v2);
  g->AddEdge(v1, v3);

  vtkSmartPointer<vtkTree> tree =
    vtkSmartPointer<vtkTree>::New();
  tree->CheckedShallowCopy(g);

  //setup the iterator
  vtkIdType root = 0;

  vtkSmartPointer<vtkTreeBFSIterator> bfsIterator =
      vtkSmartPointer<vtkTreeBFSIterator>::New();
  bfsIterator->SetStartVertex(root);
  bfsIterator->SetTree(tree);

  //traverse the tree in a breadth first fashion
  while(bfsIterator->HasNext())
  {
    vtkIdType nextVertex = bfsIterator->Next();
    std::cout << "Next vertex: " << nextVertex << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TreeBFSIterator)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TreeBFSIterator MACOSX_BUNDLE TreeBFSIterator.cxx)
 
target_link_libraries(TreeBFSIterator ${VTK_LIBRARIES})
```

**Download and Build TreeBFSIterator**

Click [here to download TreeBFSIterator](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TreeBFSIterator.tar) and its *CMakeLists.txt* file.
Once the *tarball TreeBFSIterator.tar* has been downloaded and extracted,
```
cd TreeBFSIterator/build 
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
./TreeBFSIterator
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

