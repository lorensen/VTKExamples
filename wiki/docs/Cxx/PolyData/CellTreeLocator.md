[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/CellTreeLocator

**CellTreeLocator.cxx**
```c++
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCellTreeLocator.h>
#include "vtkGenericCell.h"

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(1.0);
  sphereSource->Update();


  // Create the tree
  vtkSmartPointer<vtkCellTreeLocator> cellTree =
    vtkSmartPointer<vtkCellTreeLocator>::New();
  cellTree->SetDataSet(sphereSource->GetOutput());
  cellTree->BuildLocator();

  double testInside[3] = {.5, 0.0, 0.0};
  double testOutside[3] = {10.0, 0.0, 0.0};

  double pcoords[3], weights[3];

  vtkIdType cellId;

  vtkSmartPointer<vtkGenericCell> cell = vtkSmartPointer<vtkGenericCell>::New();

  int returnValue = EXIT_SUCCESS;

  // Should be inside
  cellId = cellTree->FindCell(testInside,0,
                              cell, pcoords, weights);
  if (cellId>=0)
  {
    std::cout << "First point: in cell " << cellId << std::endl;
  }
  else
  {
    std::cout << "ERROR: Cell was not found but should have been." << std::endl;
    returnValue = EXIT_FAILURE;
  }

  // Should be outside
  cellId = cellTree->FindCell(testOutside,0,
                            cell, pcoords, weights);
  if (cellId>=0)
  {
    std::cout << "ERROR: Found point in cell " << cellId
              << " but it should be outside the domain." << std::endl;
    returnValue = EXIT_FAILURE;
  }
  else
  {
    std::cout << "Second point: outside" << std::endl;
  }

  return returnValue;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CellTreeLocator)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CellTreeLocator MACOSX_BUNDLE CellTreeLocator.cxx)
 
target_link_libraries(CellTreeLocator ${VTK_LIBRARIES})
```

**Download and Build CellTreeLocator**

Click [here to download CellTreeLocator](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CellTreeLocator.tar) and its *CMakeLists.txt* file.
Once the *tarball CellTreeLocator.tar* has been downloaded and extracted,
```
cd CellTreeLocator/build 
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
./CellTreeLocator
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

