[VTKExamples](/home/)/[Cxx](/Cxx)/Graphs/NOVCAGraph

### Description
[]([File:graphCXX.png])
*This example shows how to construct a graph to visualize it in ParaView/VisIt using the VTK output file testVertex.vtu.
* Contributed by Sanjaya Gajurel, Case Western Reserve University

**NOVCAGraph.cxx**
```c++
#include <vtkVersion.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyLine.h>
#include <vtkTriangle.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkSmartPointer.h>

int main ( int, char *[] )
{
  // Create 8 Vertices.
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  for ( unsigned int i = 0; i < 2; ++i )
     for ( unsigned int j = 0; j < 4; ++j )
          points->InsertNextPoint( i, j, 0);

   //Create Edges
    vtkSmartPointer<vtkPolyLine> line =
    vtkSmartPointer<vtkPolyLine>::New();
    line->GetPointIds()->SetNumberOfIds(8);
  for ( unsigned int i = 0; i < 8; ++i )
      line->GetPointIds()->SetId(i,i);

   vtkSmartPointer<vtkCellArray> cellArray =
    vtkSmartPointer<vtkCellArray>::New();
   cellArray->InsertNextCell(line);

  // Create a Graph with Vertices and Edges.
  vtkSmartPointer<vtkUnstructuredGrid> grid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  grid->SetPoints(points);
  grid->SetCells(VTK_POLY_LINE,cellArray);

  // Write the file
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName("testVertex.vtu");
#if VTK_MAJOR_VERSION <= 5
  writer->SetInput(grid);
#else
  writer->SetInputData(grid);
#endif

  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(NOVCAGraph)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(NOVCAGraph MACOSX_BUNDLE NOVCAGraph.cxx)
 
target_link_libraries(NOVCAGraph ${VTK_LIBRARIES})
```

**Download and Build NOVCAGraph**

Click [here to download NOVCAGraph](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/NOVCAGraph.tar) and its *CMakeLists.txt* file.
Once the *tarball NOVCAGraph.tar* has been downloaded and extracted,
```
cd NOVCAGraph/build 
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
./NOVCAGraph
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

