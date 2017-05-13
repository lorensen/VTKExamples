[VTKExamples](/index/)/[Cxx](/Cxx)/Graphs/ScaleVertices

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Graphs/TestScaleVertices.png?raw=true" width="256" />

### Description
Scale the vertices based on a data array.

**ScaleVertices.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkRenderedGraphRepresentation.h>
#include <vtkFloatArray.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkGraphWriter.h>
#include <vtkGraphLayoutView.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDataSetAttributes.h>
#include <vtkGraphToGlyphs.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();

  g->AddEdge(v1, v2);
  g->AddEdge(v1, v2);

  vtkSmartPointer<vtkFloatArray> scales =
    vtkSmartPointer<vtkFloatArray>::New();
  scales->SetNumberOfComponents(1);
  scales->SetName("Scales");
  scales->InsertNextValue(1.0);
  scales->InsertNextValue(4.0);

  g->GetVertexData()->AddArray(scales);
 
  vtkSmartPointer<vtkGraphLayoutView> layoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  layoutView->AddRepresentationFromInput(g);
  layoutView->ScaledGlyphsOn();
  layoutView->SetScalingArrayName("Scales");
  vtkRenderedGraphRepresentation::SafeDownCast(layoutView->GetRepresentation())
            ->SetGlyphType(vtkGraphToGlyphs::CIRCLE);
  layoutView->ResetCamera();
  layoutView->Render();
  layoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ScaleVertices)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ScaleVertices MACOSX_BUNDLE ScaleVertices.cxx)
 
target_link_libraries(ScaleVertices ${VTK_LIBRARIES})
```

**Download and Build ScaleVertices**

Click [here to download ScaleVertices](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ScaleVertices.tar) and its *CMakeLists.txt* file.
Once the *tarball ScaleVertices.tar* has been downloaded and extracted,
```
cd ScaleVertices/build 
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
./ScaleVertices
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

