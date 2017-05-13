[VTKExamples](Home)/[Cxx](Cxx)/DataStructures/KdTree

### Description
This example demonstrates how to use vtkKdTree to build a tree from a vtkPoints object. Note that since AddDataSet or SetDataSet were not called, you cannot use GetDataSet.

**KdTree.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkIdList.h>
#include <vtkKdTree.h>
#include <vtkVertexGlyphFilter.h>

int main(int, char *[])
{
  //Setup point coordinates
  double x[3] = {1.0, 0.0, 0.0};
  double y[3] = {0.0, 1.0, 0.0};
  double z[3] = {0.0, 0.0, 1.0};

  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(x);
  points->InsertNextPoint(y);
  points->InsertNextPoint(z);
  
  //Create the tree
  vtkSmartPointer<vtkKdTree> kDTree = 
    vtkSmartPointer<vtkKdTree>::New();
  kDTree->BuildLocatorFromPoints(points);
  
  double testPoint[3] = {2.0, 0.0, 0.0};
  
  //Find the closest points to TestPoint
  double closestPointDist;
  vtkIdType id = kDTree->FindClosestPoint(testPoint, closestPointDist); //vtkKdTree::FindClosestPoint: must build locator first
  std::cout << "The closest point is point " << id << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(KdTree)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(KdTree MACOSX_BUNDLE KdTree.cxx)
 
target_link_libraries(KdTree ${VTK_LIBRARIES})
```

**Download and Build KdTree**

Click [here to download KdTree](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/KdTree.tar) and its *CMakeLists.txt* file.
Once the *tarball KdTree.tar* has been downloaded and extracted,
```
cd KdTree/build 
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
./KdTree
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

