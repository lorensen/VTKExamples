[VTKExamples](Home)/[Cxx](Cxx)/DataStructures/OctreeClosestPoint

**OctreeClosestPoint.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkIdList.h>
#include <vtkOctreePointLocator.h>

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
  vtkSmartPointer<vtkOctreePointLocator> octree =
    vtkSmartPointer<vtkOctreePointLocator>::New();
  octree->SetDataSet(polydata);
  octree->BuildLocator();
  
  double testPoint[3] = {2.0, 0.0, 0.0};
	
  // Find the closest points to TestPoint
  vtkIdType iD = octree->FindClosestPoint(testPoint);
  std::cout << "The closest point is point " << iD << std::endl;
  
  // Get the coordinates of the closest point
  double closestPoint[3];
  octree->GetDataSet()->GetPoint(iD, closestPoint);
  std::cout << "Coordinates: " << closestPoint[0] << " " 
            << closestPoint[1] << " " << closestPoint[2] << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(OctreeClosestPoint)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(OctreeClosestPoint MACOSX_BUNDLE OctreeClosestPoint.cxx)
 
target_link_libraries(OctreeClosestPoint ${VTK_LIBRARIES})
```

**Download and Build OctreeClosestPoint**

Click [here to download OctreeClosestPoint](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/OctreeClosestPoint.tar) and its *CMakeLists.txt* file.
Once the *tarball OctreeClosestPoint.tar* has been downloaded and extracted,
```
cd OctreeClosestPoint/build 
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
./OctreeClosestPoint
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

