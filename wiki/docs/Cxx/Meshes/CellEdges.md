[VTKExamples](/home/)/[Cxx](/Cxx)/Meshes/CellEdges

**CellEdges.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkIdList.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkTriangle> triangle =
    vtkSmartPointer<vtkTriangle>::New();
  triangle->GetPoints()->SetPoint(0, 1.0, 0.0, 0.0);
  triangle->GetPoints()->SetPoint(1, 0.0, 0.0, 0.0);
  triangle->GetPoints()->SetPoint(2, 0.0, 1.0, 0.0);
  triangle->GetPointIds()->SetId ( 0, 0 );
  triangle->GetPointIds()->SetId ( 1, 1 );
  triangle->GetPointIds()->SetId ( 2, 2 );

  std::cout << "The cell has " << triangle->GetNumberOfEdges()
            << " edges." << std::endl;

  for(vtkIdType i = 0; i < triangle->GetNumberOfEdges(); i++)
  {
    vtkCell* edge = triangle->GetEdge(i);

    vtkIdList* pointIdList = edge->GetPointIds();
    std::cout << "Edge " << i << " has " << pointIdList->GetNumberOfIds()
              << " points."  << std::endl;

    for(vtkIdType p = 0; p < pointIdList->GetNumberOfIds(); p++)
    {
      std::cout << "Edge " << i << " uses point " << pointIdList->GetId(p)
                << std::endl;
    }

  }


  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CellEdges)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CellEdges MACOSX_BUNDLE CellEdges.cxx)
 
target_link_libraries(CellEdges ${VTK_LIBRARIES})
```

**Download and Build CellEdges**

Click [here to download CellEdges](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CellEdges.tar) and its *CMakeLists.txt* file.
Once the *tarball CellEdges.tar* has been downloaded and extracted,
```
cd CellEdges/build 
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
./CellEdges
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

