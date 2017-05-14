[VTKExamples](/index/)/[Cxx](/Cxx)/InfoVis/GraphPoints

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/InfoVis/TestGraphPoints.png?raw=true" width="256" />

**GraphPoints.cxx**
```c++
#include <vtkMutableUndirectedGraph.h>
#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include <vtkGraphLayoutView.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  // Create 3 vertices
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  vtkIdType v3 = g->AddVertex();
  g->AddEdge(v1, v2);
  g->AddEdge(v1, v3);

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);

  g->SetPoints(points);

  std::cout << "Number of output points: " << g->GetPoints()->GetNumberOfPoints() << std::endl;

  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(g);
  graphLayoutView->SetLayoutStrategy("Pass Through");
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GraphPoints)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GraphPoints MACOSX_BUNDLE GraphPoints.cxx)
 
target_link_libraries(GraphPoints ${VTK_LIBRARIES})
```

**Download and Build GraphPoints**

Click [here to download GraphPoints](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GraphPoints.tar) and its *CMakeLists.txt* file.
Once the *tarball GraphPoints.tar* has been downloaded and extracted,
```
cd GraphPoints/build 
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
./GraphPoints
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

