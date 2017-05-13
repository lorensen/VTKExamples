[VTKExamples](/home/)/[Cxx](/Cxx)/Graphs/ConnectedComponents

### Description
This example constructs a graph with 4 vertices and 2 edges. V1 and V2 are not connected to V3 or V4. We wish to obtain all of the connected components of the graph. The output of the example is a list of component IDs. All vertices with the same ID can be reached from any vertex with the same ID.

**ConnectedComponents.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkBoostConnectedComponents.h>
#include <vtkDataArray.h>
#include <vtkDataSetAttributes.h>
#include <vtkGraph.h>
#include <vtkIntArray.h>
#include <vtkMutableUndirectedGraph.h>

int main ( int, char *[] )
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  vtkIdType v3 = g->AddVertex();
  vtkIdType v4 = g->AddVertex();

  g->AddEdge ( v1, v2 );
  g->AddEdge ( v3, v4 );

  vtkSmartPointer<vtkBoostConnectedComponents> connectedComponents =
    vtkSmartPointer<vtkBoostConnectedComponents>::New();
  connectedComponents->SetInput(g);
  connectedComponents->Update();

  vtkGraph* outputGraph = connectedComponents->GetOutput();

  vtkIntArray* components = vtkIntArray::SafeDownCast(
    outputGraph->GetVertexData()->GetArray("component"));

  for(vtkIdType i = 0; i < components->GetNumberOfTuples(); i++)
  {
    int val = components->GetValue(i);
    std::cout << val << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ConnectedComponents)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ConnectedComponents MACOSX_BUNDLE ConnectedComponents.cxx)
 
target_link_libraries(ConnectedComponents ${VTK_LIBRARIES})
```

**Download and Build ConnectedComponents**

Click [here to download ConnectedComponents](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ConnectedComponents.tar) and its *CMakeLists.txt* file.
Once the *tarball ConnectedComponents.tar* has been downloaded and extracted,
```
cd ConnectedComponents/build 
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
./ConnectedComponents
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

