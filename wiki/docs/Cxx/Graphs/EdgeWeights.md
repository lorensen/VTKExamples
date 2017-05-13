[VTKExamples](Home)/[Cxx](Cxx)/Graphs/EdgeWeights

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Graphs/TestEdgeWeights.png" width="256" />

**EdgeWeights.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkDataSetAttributes.h>
#include <vtkDoubleArray.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkCircularLayoutStrategy.h>
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

  // Add the edge weight array to the graph
  g->GetEdgeData()->AddArray(weights);

  std::cout << "Number of Weights: "
            << vtkDoubleArray::SafeDownCast(
              g->GetEdgeData()->GetArray("Weights"))->GetNumberOfTuples()
            << std::endl;

  for(vtkIdType i = 0; i < weights->GetNumberOfTuples(); i++)
  {
    double w = weights->GetValue(i);
    std::cout << "Weight " << i << " : " << w << std::endl;
  }

  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(g);
  graphLayoutView->SetEdgeLabelVisibility(true);
  graphLayoutView->SetEdgeLabelArrayName("Weights");
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(EdgeWeights)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(EdgeWeights MACOSX_BUNDLE EdgeWeights.cxx)
 
target_link_libraries(EdgeWeights ${VTK_LIBRARIES})
```

**Download and Build EdgeWeights**

Click [here to download EdgeWeights](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/EdgeWeights.tar) and its *CMakeLists.txt* file.
Once the *tarball EdgeWeights.tar* has been downloaded and extracted,
```
cd EdgeWeights/build 
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
./EdgeWeights
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

