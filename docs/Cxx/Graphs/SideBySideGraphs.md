[VTKExamples](/index/)/[Cxx](/Cxx)/Graphs/SideBySideGraphs

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Graphs/TestSideBySideGraphs.png?raw=true" width="256" />

### Description
This currently crashes - still trying to decide how to best display these graphs.

**SideBySideGraphs.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkGraphToPolyData.h>
#include <vtkDataSetAttributes.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkGraphLayoutView.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int, char *[])
{
  // Create the first graph
  vtkSmartPointer<vtkMutableUndirectedGraph> g0 = 
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();
  {
  vtkIdType v1 = g0->AddVertex();
  vtkIdType v2 = g0->AddVertex();
  vtkIdType v3 = g0->AddVertex();
 
  g0->AddEdge(v1, v2);
  g0->AddEdge(v2, v3);
  g0->AddEdge(v1, v3);
  
  // Create points
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);
    
  // Add the coordinates of the points to the graph
  g0->SetPoints(points);
  }
  
  // Create the second graph
  vtkSmartPointer<vtkMutableUndirectedGraph> g1 = 
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();
 
  vtkIdType v1 = g1->AddVertex();
  vtkIdType v2 = g1->AddVertex();
   
  g1->AddEdge(v1, v2);
   
  // Create points
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
      
  // Add the coordinates of the points to the graph
  g1->SetPoints(points);
  
  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
 
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  
  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};
   
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView0 = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView0->SetRenderWindow(renderWindow);
  graphLayoutView0->SetInteractor(renderWindowInteractor);
  graphLayoutView0->GetRenderer()->SetViewport(leftViewport);
  graphLayoutView0->AddRepresentationFromInput(g0);
  graphLayoutView0->ResetCamera();
  graphLayoutView0->Render();
  
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView1 = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView1->SetRenderWindow(renderWindow);
  graphLayoutView1->SetInteractor(renderWindowInteractor);
  graphLayoutView1->GetRenderer()->SetViewport(rightViewport);
  graphLayoutView1->AddRepresentationFromInput(g1);
  graphLayoutView1->ResetCamera();
  graphLayoutView1->Render();
    
  //graphLayoutView0->GetInteractor()->Start();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SideBySideGraphs)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SideBySideGraphs MACOSX_BUNDLE SideBySideGraphs.cxx)
 
target_link_libraries(SideBySideGraphs ${VTK_LIBRARIES})
```

**Download and Build SideBySideGraphs**

Click [here to download SideBySideGraphs](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SideBySideGraphs.tar) and its *CMakeLists.txt* file.
Once the *tarball SideBySideGraphs.tar* has been downloaded and extracted,
```
cd SideBySideGraphs/build 
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
./SideBySideGraphs
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

