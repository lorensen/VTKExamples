[VTKExamples](/home/)/[Cxx](/Cxx)/Graphs/RemoveIsolatedVertices

**RemoveIsolatedVertices.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkMutableUndirectedGraph.h>
#include <vtkPoints.h>
#include <vtkRemoveIsolatedVertices.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g = 
      vtkSmartPointer<vtkMutableUndirectedGraph>::New();
  
  // Create 3 vertices
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  g->AddVertex();
  
  g->AddEdge ( v1, v2 );
  
  std::cout << "Graph has "
            << g->GetNumberOfVertices()
            << " vertices and " 
            << g->GetNumberOfEdges() << " edge before." << std::endl;
  
  vtkSmartPointer<vtkRemoveIsolatedVertices> filter = 
    vtkSmartPointer<vtkRemoveIsolatedVertices>::New();
  filter->SetInputConnection(g->GetProducerPort());
  filter->Update();
  
  std::cout << "Graph has "
            << filter->GetOutput()->GetNumberOfVertices() 
            << " vertices and "
            << filter->GetOutput()->GetNumberOfEdges()
            << " edge after." << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RemoveIsolatedVertices)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RemoveIsolatedVertices MACOSX_BUNDLE RemoveIsolatedVertices.cxx)
 
target_link_libraries(RemoveIsolatedVertices ${VTK_LIBRARIES})
```

**Download and Build RemoveIsolatedVertices**

Click [here to download RemoveIsolatedVertices](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RemoveIsolatedVertices.tar) and its *CMakeLists.txt* file.
Once the *tarball RemoveIsolatedVertices.tar* has been downloaded and extracted,
```
cd RemoveIsolatedVertices/build 
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
./RemoveIsolatedVertices
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

