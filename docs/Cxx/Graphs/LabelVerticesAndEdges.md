[VTKExamples](/index/)/[Cxx](/Cxx)/Graphs/LabelVerticesAndEdges

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Graphs/TestLabelVerticesAndEdges.png?raw=true" width="256" />

### Description
This example sets and displays labels of vertices and edges of a graph.

**LabelVerticesAndEdges.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkCircularLayoutStrategy.h>
#include <vtkDataSetAttributes.h>
#include <vtkDoubleArray.h>
#include <vtkGraphLayoutView.h>
#include <vtkIntArray.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkRenderWindowInteractor.h>

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
  
  // Create an array for the vertex labels
  vtkSmartPointer<vtkIntArray> vertexIDs =
    vtkSmartPointer<vtkIntArray>::New();
  vertexIDs->SetNumberOfComponents(1);
  vertexIDs->SetName("VertexIDs");
  
  // Set the vertex labels
  vertexIDs->InsertNextValue(0);
  vertexIDs->InsertNextValue(1);
  vertexIDs->InsertNextValue(2);
  
  // Add the edge weight array to the graph
  g->GetEdgeData()->AddArray(weights);
  g->GetVertexData()->AddArray(vertexIDs);
  
  vtkSmartPointer<vtkCircularLayoutStrategy> circularLayoutStrategy = 
    vtkSmartPointer<vtkCircularLayoutStrategy>::New();
  
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(g);
  
  graphLayoutView->SetLayoutStrategy(circularLayoutStrategy);
  graphLayoutView->SetVertexLabelVisibility(true);
  graphLayoutView->SetEdgeLabelVisibility(true);
  graphLayoutView->SetEdgeLabelArrayName("Weights"); //default is "labels"
  graphLayoutView->SetVertexLabelArrayName("VertexIDs"); //default is "labels"
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(LabelVerticesAndEdges)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(LabelVerticesAndEdges MACOSX_BUNDLE LabelVerticesAndEdges.cxx)
 
target_link_libraries(LabelVerticesAndEdges ${VTK_LIBRARIES})
```

**Download and Build LabelVerticesAndEdges**

Click [here to download LabelVerticesAndEdges](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/LabelVerticesAndEdges.tar) and its *CMakeLists.txt* file.
Once the *tarball LabelVerticesAndEdges.tar* has been downloaded and extracted,
```
cd LabelVerticesAndEdges/build 
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
./LabelVerticesAndEdges
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

