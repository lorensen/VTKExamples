[VTKExamples](Home)/[Cxx](Cxx)/Graphs/AdjacentVertexIterator

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Graphs/TestAdjacentVertexIterator.png" width="256" />

### Description
The visualization in is example is currently broken. vtkGraphLayoutView does not currently allow coloring with a vtkUnsignedCharArray.

**AdjacentVertexIterator.cxx**
```c++
#include <vtkMutableUndirectedGraph.h>
#include <vtkSmartPointer.h>
#include <vtkAdjacentVertexIterator.h>
#include <vtkUnsignedCharArray.h>
#include <vtkLookupTable.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkViewTheme.h>
#include <vtkDataSetAttributes.h>
#include <vtkGraphLayoutView.h>

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  //create 3 vertices
  vtkIdType v0 = g->AddVertex();
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  vtkIdType v3 = g->AddVertex();

  //add edges
  g->AddEdge(v0, v1);
  g->AddEdge(v0, v2);
  g->AddEdge(v2, v3);

  // Create the color array
  vtkSmartPointer<vtkUnsignedCharArray> vertexColors =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  vertexColors->SetNumberOfComponents(3);
  vertexColors->SetName("color");

  //setup colors
  unsigned char red[3] = {255, 0, 0};
  unsigned char green[3] = {0, 255, 0};
  unsigned char blue[3] = {0, 0, 255};

  for(unsigned int i = 0; i < 4; i++)
  {
    vertexColors->InsertNextTupleValue(blue);//not connected vertices
  }


  vtkSmartPointer<vtkAdjacentVertexIterator> iterator =
    vtkSmartPointer<vtkAdjacentVertexIterator>::New();
  g->GetAdjacentVertices(0, iterator);

  vertexColors->SetTupleValue(0, red);//origin

  while(iterator->HasNext())
  {
    vtkIdType nextVertex = iterator->Next();
    std::cout << "Next vertex: " << nextVertex << std::endl;
    vertexColors->SetTupleValue(nextVertex, green);//connected vertices
  }

  // Add the color array to the graph
  g->GetVertexData()->AddArray(vertexColors);

  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(g);
  graphLayoutView->SetLayoutStrategyToTree();

  graphLayoutView->SetVertexColorArrayName("color");
  graphLayoutView->ColorVerticesOn();

  vtkSmartPointer<vtkViewTheme> theme =
    vtkSmartPointer<vtkViewTheme>::New();
  //theme->SetPointLookupTable(lookupTable);
  theme->ScalePointLookupTableOff();
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
 
PROJECT(AdjacentVertexIterator)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(AdjacentVertexIterator MACOSX_BUNDLE AdjacentVertexIterator.cxx)
 
target_link_libraries(AdjacentVertexIterator ${VTK_LIBRARIES})
```

**Download and Build AdjacentVertexIterator**

Click [here to download AdjacentVertexIterator](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/AdjacentVertexIterator.tar) and its *CMakeLists.txt* file.
Once the *tarball AdjacentVertexIterator.tar* has been downloaded and extracted,
```
cd AdjacentVertexIterator/build 
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
./AdjacentVertexIterator
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

