[VTKExamples](/home/)/[Cxx](/Cxx)/DataStructures/IncrementalOctreePointLocator

**IncrementalOctreePointLocator.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkIdList.h>
#include <vtkIncrementalOctreePointLocator.h>

int main(int, char *[])
{
  // Setup point coordinates
  double x[3] = {1.0, 0.0, 0.0};
  double y[3] = {0.0, 1.0, 0.0};
  double z[3] = {0.0, 0.0, 1.0};

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(x);
  points->InsertNextPoint(y);
  points->InsertNextPoint(z);

  vtkSmartPointer<vtkPolyData> polydata =
      vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Create the tree
  vtkSmartPointer<vtkIncrementalOctreePointLocator> octree =
    vtkSmartPointer<vtkIncrementalOctreePointLocator>::New();
  octree->SetDataSet(polydata);
  octree->BuildLocator();

  double testPoint[3] = {2.0, 0.0, 0.0};

  {
  // Find the closest points to TestPoint
//  double closestPointDist;
  vtkIdType iD = octree->FindClosestPoint(testPoint);
  std::cout << "The closest point is point " << iD << std::endl;

  // Get the coordinates of the closest point
  double closestPoint[3];
  octree->GetDataSet()->GetPoint(iD, closestPoint);
  std::cout << "Coordinates: " << closestPoint[0] << " " << closestPoint[1] << " " << closestPoint[2] << std::endl;
  }

  // Insert a point
  double pnew[3] = {2.1, 0, 0};
  octree->InsertNextPoint(pnew);
  
  {
  // Find the closest points to TestPoint
//  double closestPointDist;
  vtkIdType iD = octree->FindClosestPoint(testPoint);
  std::cout << "The closest point is point " << iD << std::endl;

  // Get the coordinates of the closest point
  double closestPoint[3];
  octree->GetDataSet()->GetPoint(iD, closestPoint);
  std::cout << "Coordinates: " << closestPoint[0] << " " << closestPoint[1] << " " << closestPoint[2] << std::endl;
  }
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(IncrementalOctreePointLocator)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(IncrementalOctreePointLocator MACOSX_BUNDLE IncrementalOctreePointLocator.cxx)
 
target_link_libraries(IncrementalOctreePointLocator ${VTK_LIBRARIES})
```

**Download and Build IncrementalOctreePointLocator**

Click [here to download IncrementalOctreePointLocator](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/IncrementalOctreePointLocator.tar) and its *CMakeLists.txt* file.
Once the *tarball IncrementalOctreePointLocator.tar* has been downloaded and extracted,
```
cd IncrementalOctreePointLocator/build 
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
./IncrementalOctreePointLocator
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

