[VTKExamples](/home/)/[Cxx](/Cxx)/Developers/GraphAlgorithmFilter

### Description
This example demonstrates how to create a filter that takes a vtkGraph as input and produces a vtkGraph as output.

**GraphAlgorithmFilter.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkGraph.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkMutableDirectedGraph.h>

#include "vtkTestGraphAlgorithmFilter.h"

void TestDirected();
void TestUndirected();

int main(int, char *[])
{
  TestDirected();
  TestUndirected();
  
  return EXIT_SUCCESS;
}

void TestDirected()
{
  
  vtkSmartPointer<vtkMutableDirectedGraph> g =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();

  g->AddEdge(v1, v2);
  std::cout << "Input type: " << g->GetClassName() << std::endl;

  vtkSmartPointer<vtkTestGraphAlgorithmFilter> filter =
    vtkSmartPointer<vtkTestGraphAlgorithmFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  filter->SetInput(g);
#else
  filter->SetInputData(g);
#endif
  filter->Update();

  std::cout << "Output type: " << filter->GetOutput()->GetClassName() << std::endl;
  std::cout << "Output has " << filter->GetOutput()->GetNumberOfVertices() << " vertices." << std::endl;
  std::cout << std::endl;
}

void TestUndirected()
{
  std::cout << "TestUndirected" << std::endl;
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();

  g->AddEdge(v1, v2);
  std::cout << "Input type: " << g->GetClassName() << std::endl;

  vtkSmartPointer<vtkTestGraphAlgorithmFilter> filter =
    vtkSmartPointer<vtkTestGraphAlgorithmFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  filter->SetInput(g);
#else
  filter->SetInputData(g);
#endif
  filter->Update();

  std::cout << "Output type: " << filter->GetOutput()->GetClassName() << std::endl;
  std::cout << "Output has " << filter->GetOutput()->GetNumberOfVertices() << " vertices." << std::endl;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GraphAlgorithmFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GraphAlgorithmFilter MACOSX_BUNDLE GraphAlgorithmFilter.cxx)
 
target_link_libraries(GraphAlgorithmFilter ${VTK_LIBRARIES})
```

**Download and Build GraphAlgorithmFilter**

Click [here to download GraphAlgorithmFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GraphAlgorithmFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball GraphAlgorithmFilter.tar* has been downloaded and extracted,
```
cd GraphAlgorithmFilter/build 
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
./GraphAlgorithmFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

