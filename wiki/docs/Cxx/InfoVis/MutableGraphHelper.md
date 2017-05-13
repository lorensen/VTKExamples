[VTKExamples](Home)/[Cxx](Cxx)/InfoVis/MutableGraphHelper

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/InfoVis/TestMutableGraphHelper.png" width="256" />

**MutableGraphHelper.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkMutableGraphHelper.h>
#include <vtkGraphLayoutView.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  vtkSmartPointer<vtkMutableGraphHelper> graphHelper =
    vtkSmartPointer<vtkMutableGraphHelper>::New();
  graphHelper->SetGraph(g);
  vtkIdType v0 = graphHelper->AddVertex();
  vtkIdType v1 = graphHelper->AddVertex();

  graphHelper->AddEdge(v0, v1);

  // Can also do this:
  graphHelper->RemoveEdge(0);
  
  vtkSmartPointer<vtkGraphLayoutView> treeLayoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  treeLayoutView->AddRepresentationFromInput(graphHelper->GetGraph());
  treeLayoutView->SetLayoutStrategyToTree();
  treeLayoutView->ResetCamera();
  treeLayoutView->Render();
  treeLayoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MutableGraphHelper)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MutableGraphHelper MACOSX_BUNDLE MutableGraphHelper.cxx)
 
target_link_libraries(MutableGraphHelper ${VTK_LIBRARIES})
```

**Download and Build MutableGraphHelper**

Click [here to download MutableGraphHelper](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MutableGraphHelper.tar) and its *CMakeLists.txt* file.
Once the *tarball MutableGraphHelper.tar* has been downloaded and extracted,
```
cd MutableGraphHelper/build 
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
./MutableGraphHelper
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

