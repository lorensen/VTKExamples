[VTKExamples](Home)/[Cxx](Cxx)/DataStructures/KdTreePointLocatorClosestPoint

### Description
This example creates a set of three points, builds a KDTree from them, then demonstrates how to find the closest point to a query point.

**KdTreePointLocatorClosestPoint.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkIdList.h>
#include <vtkKdTreePointLocator.h>

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
  vtkSmartPointer<vtkKdTreePointLocator> kDTree = 
    vtkSmartPointer<vtkKdTreePointLocator>::New();
  kDTree->SetDataSet(polydata);
  kDTree->BuildLocator();
  
  double testPoint[3] = {2.0, 0.0, 0.0};
	
  // Find the closest points to TestPoint
  vtkIdType iD = kDTree->FindClosestPoint(testPoint);
  std::cout << "The closest point is point " << iD << std::endl;
  
  //Get the coordinates of the closest point
  double closestPoint[3];
  kDTree->GetDataSet()->GetPoint(iD, closestPoint);
  std::cout << "Coordinates: " << closestPoint[0] << " " << closestPoint[1] << " " << closestPoint[2] << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(KdTreePointLocatorClosestPoint)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(KdTreePointLocatorClosestPoint MACOSX_BUNDLE KdTreePointLocatorClosestPoint.cxx)
 
target_link_libraries(KdTreePointLocatorClosestPoint ${VTK_LIBRARIES})
```

**Download and Build KdTreePointLocatorClosestPoint**

Click [here to download KdTreePointLocatorClosestPoint](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/KdTreePointLocatorClosestPoint.tar) and its *CMakeLists.txt* file.
Once the *tarball KdTreePointLocatorClosestPoint.tar* has been downloaded and extracted,
```
cd KdTreePointLocatorClosestPoint/build 
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
./KdTreePointLocatorClosestPoint
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

