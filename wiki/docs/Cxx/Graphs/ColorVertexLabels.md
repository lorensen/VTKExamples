[VTKExamples](/home/)/[Cxx](/Cxx)/Graphs/ColorVertexLabels

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Graphs/TestColorVertexLabels.png?raw=true" width="256" />

**ColorVertexLabels.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkIntArray.h>
#include <vtkDataSetAttributes.h>
#include <vtkGraphLayoutView.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderedGraphRepresentation.h>
#include <vtkTextProperty.h>

int main(int, char *[])
{
  // Create a graph
  vtkSmartPointer<vtkMutableDirectedGraph> graph =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();
 
  vtkIdType v1 = graph->AddVertex();
  vtkIdType v2 = graph->AddVertex();
  graph->AddEdge(v1,v2);
  
  // Create an array for the vertex labels
  vtkSmartPointer<vtkIntArray> vertexIDs =
    vtkSmartPointer<vtkIntArray>::New();
  vertexIDs->SetNumberOfComponents(1);
  vertexIDs->SetName("VertexIDs");
 
  // Set the vertex labels
  vertexIDs->InsertNextValue(0);
  vertexIDs->InsertNextValue(1);
  
  // Add the array to the graph
  graph->GetVertexData()->AddArray(vertexIDs);
  
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(graph);
  graphLayoutView->SetVertexLabelVisibility(true);
  vtkRenderedGraphRepresentation::SafeDownCast(graphLayoutView->GetRepresentation())
            ->GetVertexLabelTextProperty()->SetColor(1,0,0);
  graphLayoutView->SetLayoutStrategyToSimple2D();
  graphLayoutView->SetVertexLabelArrayName("VertexIDs");
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ColorVertexLabels)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ColorVertexLabels MACOSX_BUNDLE ColorVertexLabels.cxx)
 
target_link_libraries(ColorVertexLabels ${VTK_LIBRARIES})
```

**Download and Build ColorVertexLabels**

Click [here to download ColorVertexLabels](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ColorVertexLabels.tar) and its *CMakeLists.txt* file.
Once the *tarball ColorVertexLabels.tar* has been downloaded and extracted,
```
cd ColorVertexLabels/build 
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
./ColorVertexLabels
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

