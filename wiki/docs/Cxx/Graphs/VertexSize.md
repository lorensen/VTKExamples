[VTKExamples](/home/)/[Cxx](/Cxx)/Graphs/VertexSize

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Graphs/TestVertexSize.png?raw=true" width="256" />

### Description
Change the size of all vertices.

**VertexSize.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkRenderedGraphRepresentation.h>
#include <vtkObjectFactory.h>
#include <vtkFloatArray.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkGraphWriter.h>
#include <vtkGraphLayoutView.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDataSetAttributes.h>
#include <vtkGraphToGlyphs.h>

class CustomRepresentation : public vtkRenderedGraphRepresentation
{
 public:
    static CustomRepresentation* New();
    vtkTypeMacro(CustomRepresentation, vtkRenderedGraphRepresentation);

    void SetVertexSize(int vertexSize)
    {
      this->VertexGlyph->SetScreenSize(vertexSize);
      this->VertexGlyph->Modified();
    }
};
vtkStandardNewMacro(CustomRepresentation);

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();

  g->AddEdge(v1, v2);
  g->AddEdge(v1, v2);

  // Specify coordinates so the graph is always the same for testing
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);
  g->SetPoints(points);

  vtkSmartPointer<CustomRepresentation> representation =
    vtkSmartPointer<CustomRepresentation>::New();
  representation->SetInputConnection(g->GetProducerPort());
  representation->SetVertexSize(100);
  representation->SetGlyphType(vtkGraphToGlyphs::CIRCLE);

  vtkSmartPointer<vtkGraphLayoutView> layoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  layoutView->AddRepresentation(representation);
  layoutView->SetLayoutStrategy("Pass Through");
  layoutView->ResetCamera();
  layoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(VertexSize)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VertexSize MACOSX_BUNDLE VertexSize.cxx)
 
target_link_libraries(VertexSize ${VTK_LIBRARIES})
```

**Download and Build VertexSize**

Click [here to download VertexSize](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VertexSize.tar) and its *CMakeLists.txt* file.
Once the *tarball VertexSize.tar* has been downloaded and extracted,
```
cd VertexSize/build 
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
./VertexSize
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

