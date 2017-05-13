[VTKExamples](/home/)/[Cxx](/Cxx)/Graphs/ColorEdges

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Graphs/TestColorEdges.png?raw=true" width="256" />

**ColorEdges.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkDataSetAttributes.h>
#include <vtkGraphLayoutView.h>
#include <vtkIntArray.h>
#include <vtkLookupTable.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkViewTheme.h>
 
int main(int, char *[])
{
  vtkSmartPointer<vtkMutableDirectedGraph> graph = 
    vtkSmartPointer<vtkMutableDirectedGraph>::New();
 
  // Create a graph
  vtkIdType v1 = graph->AddVertex();
  vtkIdType v2 = graph->AddVertex();
  vtkIdType v3 = graph->AddVertex();
  graph->AddEdge(v1,v2);
  graph->AddEdge(v2,v3);
  
  // Create the color array
  vtkSmartPointer<vtkIntArray> edgeColors = 
    vtkSmartPointer<vtkIntArray>::New();
  edgeColors->SetNumberOfComponents(1);
  edgeColors->SetName("Color");
 
  vtkSmartPointer<vtkLookupTable> lookupTable = 
    vtkSmartPointer<vtkLookupTable>::New();
  lookupTable->SetNumberOfTableValues(2);
  lookupTable->SetTableValue(0, 1.0, 0.0, 0.0); // red
  lookupTable->SetTableValue(1, 0.0, 1.0, 0.0); // green
  lookupTable->Build();
 
  edgeColors->InsertNextValue(0);
  edgeColors->InsertNextValue(1);
     
  // Add the color array to the graph
  graph->GetEdgeData()->AddArray(edgeColors);
 
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(graph);
  graphLayoutView->SetLayoutStrategyToTree();
 
  graphLayoutView->SetEdgeColorArrayName("Color");
  graphLayoutView->ColorEdgesOn();
 
  vtkSmartPointer<vtkViewTheme> theme = 
    vtkSmartPointer<vtkViewTheme>::New();
  theme->SetCellLookupTable(lookupTable);
 
  graphLayoutView->ApplyViewTheme(theme);
  graphLayoutView->ResetCamera();
  graphLayoutView->GetInteractor()->Initialize();
  graphLayoutView->GetInteractor()->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ColorEdges)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ColorEdges MACOSX_BUNDLE ColorEdges.cxx)
 
target_link_libraries(ColorEdges ${VTK_LIBRARIES})
```

**Download and Build ColorEdges**

Click [here to download ColorEdges](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ColorEdges.tar) and its *CMakeLists.txt* file.
Once the *tarball ColorEdges.tar* has been downloaded and extracted,
```
cd ColorEdges/build 
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
./ColorEdges
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

