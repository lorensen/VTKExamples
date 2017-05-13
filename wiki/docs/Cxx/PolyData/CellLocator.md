[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/CellLocator

### Description
This example creates a sphere and then finds the closest point on the sphere to a test point.

**CellLocator.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkCellLocator.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  // Create the tree
  vtkSmartPointer<vtkCellLocator> cellLocator = 
    vtkSmartPointer<vtkCellLocator>::New();
  cellLocator->SetDataSet(sphereSource->GetOutput());
  cellLocator->BuildLocator();
  
  double testPoint[3] = {2.0, 0.0, 0.0};
  
  //Find the closest points to TestPoint
  double closestPoint[3];//the coordinates of the closest point will be returned here
  double closestPointDist2; //the squared distance to the closest point will be returned here
  vtkIdType cellId; //the cell id of the cell containing the closest point will be returned here
  int subId; //this is rarely used (in triangle strips only, I believe)
  cellLocator->FindClosestPoint(testPoint, closestPoint, cellId, subId, closestPointDist2);
  
  std::cout << "Coordinates of closest point: " << closestPoint[0] << " " << closestPoint[1] << " " << closestPoint[2] << std::endl;
  std::cout << "Squared distance to closest point: " << closestPointDist2 << std::endl;
  std::cout << "CellId: " << cellId << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CellLocator)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CellLocator MACOSX_BUNDLE CellLocator.cxx)
 
target_link_libraries(CellLocator ${VTK_LIBRARIES})
```

**Download and Build CellLocator**

Click [here to download CellLocator](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CellLocator.tar) and its *CMakeLists.txt* file.
Once the *tarball CellLocator.tar* has been downloaded and extracted,
```
cd CellLocator/build 
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
./CellLocator
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

