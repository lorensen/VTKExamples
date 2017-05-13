[VTKExamples](/home/)/[Cxx](/Cxx)/Graphs/SelectedVerticesAndEdges

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Graphs/TestSelectedVerticesAndEdges.png?raw=true" width="256" />

### Description
* Thanks to Eric Monson

**SelectedVerticesAndEdges.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkAnnotationLink.h>
#include <vtkRenderedGraphRepresentation.h>
#include <vtkRenderer.h>
#include <vtkHardwareSelector.h>
#include <vtkDoubleArray.h>
#include <vtkSelectionNode.h>
#include <vtkIdTypeArray.h>
#include <vtkSelection.h>
#include <vtkRenderWindow.h>
#include <vtkUnsignedCharArray.h>
#include <vtkObjectFactory.h>
#include <vtkGraphLayoutStrategy.h>
#include <vtkGraphLayoutView.h>
#include <vtkGraphWriter.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSimple2DLayoutStrategy.h>
#include <vtkInteractorStyleRubberBand2D.h>

class RubberBandStyle : public vtkInteractorStyleRubberBand2D
{
  public:
    static RubberBandStyle* New();
    vtkTypeMacro(RubberBandStyle, vtkInteractorStyleRubberBand2D);

  virtual void OnLeftButtonUp()
  {
    // Forward events
    vtkInteractorStyleRubberBand2D::OnLeftButtonUp();

    vtkSelection* selection = this->View->GetRepresentation()->GetAnnotationLink()->GetCurrentSelection();
    vtkSelectionNode* vertices;
    vtkSelectionNode* edges;
    if(selection->GetNode(0)->GetFieldType() == vtkSelectionNode::VERTEX)
    {
      vertices = selection->GetNode(0);
    }
    else if(selection->GetNode(0)->GetFieldType() == vtkSelectionNode::EDGE)
    {
      edges = selection->GetNode(0);
    }

    if(selection->GetNode(1)->GetFieldType() == vtkSelectionNode::VERTEX)
    {
      vertices = selection->GetNode(1);
    }
    else if(selection->GetNode(1)->GetFieldType() == vtkSelectionNode::EDGE)
    {
      edges = selection->GetNode(1);
    }

    vtkIdTypeArray* vertexList = vtkIdTypeArray::SafeDownCast(vertices->GetSelectionList());
    std::cout << "There are " << vertexList->GetNumberOfTuples() << " vertices selected." << std::endl;

    if(vertexList->GetNumberOfTuples() > 0)
    {
      std::cout << "Vertex Ids: ";
    }
    for(vtkIdType i = 0; i < vertexList->GetNumberOfTuples(); i++)
    {
      std::cout << vertexList->GetValue(i) << " ";
    }

    std::cout << std::endl;
    vtkIdTypeArray* edgeList = vtkIdTypeArray::SafeDownCast(edges->GetSelectionList());
    std::cout << "There are " << edgeList->GetNumberOfTuples() << " edges selected." << std::endl;
    if(edgeList->GetNumberOfTuples() > 0)
    {
      std::cout << "Edge Ids: ";
    }

    for(vtkIdType i = 0; i < edgeList->GetNumberOfTuples(); i++)
    {
      std::cout << edgeList->GetValue(i) << " ";
    }
    std::cout << std::endl;
  }

  vtkGraphLayoutView* View;
};
vtkStandardNewMacro(RubberBandStyle);


int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();

  g->AddEdge(v1, v2);
  g->AddEdge(v1, v2);

  vtkSmartPointer<vtkGraphLayoutView> view =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  view->AddRepresentationFromInput(g);
  view->SetLayoutStrategy("Simple 2D");

  vtkSmartPointer<RubberBandStyle> style =
    vtkSmartPointer<RubberBandStyle>::New();
  style->View = view;
  view->SetInteractorStyle(style);

  view->ResetCamera();
  view->Render();

  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SelectedVerticesAndEdges)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SelectedVerticesAndEdges MACOSX_BUNDLE SelectedVerticesAndEdges.cxx)
 
target_link_libraries(SelectedVerticesAndEdges ${VTK_LIBRARIES})
```

**Download and Build SelectedVerticesAndEdges**

Click [here to download SelectedVerticesAndEdges](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SelectedVerticesAndEdges.tar) and its *CMakeLists.txt* file.
Once the *tarball SelectedVerticesAndEdges.tar* has been downloaded and extracted,
```
cd SelectedVerticesAndEdges/build 
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
./SelectedVerticesAndEdges
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

