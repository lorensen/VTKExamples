[VTKExamples](/home/)/[Cxx](/Cxx)/GeometricObjects/Polyhedron

**Polyhedron.cxx**
```c++
#include "vtkSmartPointer.h"

#include "vtkVersion.h"
#include "vtkUnstructuredGrid.h"
#include "vtkPolyhedron.h"
#include "vtkCellArray.h"
#include "vtkPointData.h"
#include "vtkCellData.h"
#include "vtkIdList.h"
#include "vtkPoints.h"
#include "vtkDataArray.h"
#include "vtkXMLUnstructuredGridWriter.h"

int main( int, char*[] )
{
  // create polyhedron (cube)
  vtkIdType pointIds[8] = {0, 1, 2, 3, 4, 5, 6, 7};

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(-1.0,-1.0,-1.0);
  points->InsertNextPoint( 1.0,-1.0,-1.0);
  points->InsertNextPoint( 1.0, 1.0,-1.0);
  points->InsertNextPoint(-1.0, 1.0,-1.0);
  points->InsertNextPoint(-1.0,-1.0, 1.0);
  points->InsertNextPoint( 1.0,-1.0, 1.0);
  points->InsertNextPoint( 1.0, 1.0, 1.0);
  points->InsertNextPoint(-1.0, 1.0, 1.0);

  vtkSmartPointer<vtkCellArray> faces =
    vtkSmartPointer<vtkCellArray>::New();
  vtkIdType face0[4] = {0, 3, 2, 1};
  vtkIdType face1[4] = {0, 4, 7, 3};
  vtkIdType face2[4] = {4, 5, 6, 7};
  vtkIdType face3[4] = {5, 1, 2, 6};
  vtkIdType face4[4] = {0, 1, 5, 4};
  vtkIdType face5[4] = {2, 3, 7, 6};

  faces->InsertNextCell(4, face0);
  faces->InsertNextCell(4, face1);
  faces->InsertNextCell(4, face2);
  faces->InsertNextCell(4, face3);
  faces->InsertNextCell(4, face4);
  faces->InsertNextCell(4, face5);

  vtkSmartPointer<vtkUnstructuredGrid> ugrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ugrid->SetPoints(points);
  ugrid->InsertNextCell(
    VTK_POLYHEDRON, 8, pointIds,
    6, faces->GetPointer());

  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
#if VTK_MAJOR_VERSION <= 5
  writer->SetInput(ugrid);
#else
  writer->SetInputData(ugrid);
#endif
  writer->SetFileName("polyhedron.vtu");
  writer->SetDataModeToAscii();
  writer->Update();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Polyhedron)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Polyhedron MACOSX_BUNDLE Polyhedron.cxx)
 
target_link_libraries(Polyhedron ${VTK_LIBRARIES})
```

**Download and Build Polyhedron**

Click [here to download Polyhedron](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Polyhedron.tar) and its *CMakeLists.txt* file.
Once the *tarball Polyhedron.tar* has been downloaded and extracted,
```
cd Polyhedron/build 
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
./Polyhedron
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

