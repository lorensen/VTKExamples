[VTKExamples](Home)/[Cxx](Cxx)/DataStructures/OctreeFindPointsWithinRadius

**OctreeFindPointsWithinRadius.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkIdList.h>
#include <vtkOctreePointLocator.h>

int main(int, char *[])
{
  // Create some random points
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(10);
  pointSource->Update();

  // Create the tree
  vtkSmartPointer<vtkOctreePointLocator> octree =
    vtkSmartPointer<vtkOctreePointLocator>::New();
  octree->SetDataSet(pointSource->GetOutput());
  octree->BuildLocator();

  // Find the k closest points to (0,0,0)
  vtkIdType k = 1;
  double testPoint[3] = {0.0, 0.0, 0.0};
  vtkSmartPointer<vtkIdList> result =
    vtkSmartPointer<vtkIdList>::New();

  octree->FindPointsWithinRadius(1.0, testPoint, result);

  for(vtkIdType i = 0; i < k; i++)
  {
    vtkIdType point_ind = result->GetId(i);
    double p[3];
    pointSource->GetOutput()->GetPoint(point_ind, p);
    std::cout << "Closest point " << i << ": Point "
              << point_ind << ": (" << p[0] << ", "
              << p[1] << ", " << p[2] << ")" << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(OctreeFindPointsWithinRadius)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(OctreeFindPointsWithinRadius MACOSX_BUNDLE OctreeFindPointsWithinRadius.cxx)
 
target_link_libraries(OctreeFindPointsWithinRadius ${VTK_LIBRARIES})
```

**Download and Build OctreeFindPointsWithinRadius**

Click [here to download OctreeFindPointsWithinRadius](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/OctreeFindPointsWithinRadius.tar) and its *CMakeLists.txt* file.
Once the *tarball OctreeFindPointsWithinRadius.tar* has been downloaded and extracted,
```
cd OctreeFindPointsWithinRadius/build 
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
./OctreeFindPointsWithinRadius
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

