[VTKExamples](/home/)/[Cxx](/Cxx)/DataStructures/BuildLocatorFromKClosestPoints

**BuildLocatorFromKClosestPoints.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPointSource.h>
#include <vtkIdList.h>
#include <vtkKdTree.h>

int main(int, char *[])
{
  // Create some points
  double origin[3] = {0.0, 0.0, 0.0};
  double x[3] = {1.0, 0.0, 0.0};
  double y[3] = {0.0, 1.0, 0.0};
  double z[3] = {0.0, 0.0, 1.0};

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(origin);
  points->InsertNextPoint(x);
  points->InsertNextPoint(y);
  points->InsertNextPoint(z);

  // Create the tree
  vtkSmartPointer<vtkKdTree> pointTree =
    vtkSmartPointer<vtkKdTree>::New();
  pointTree->BuildLocatorFromPoints(points);

  // Find the 2 closest points to (0.5,0,0)
  vtkIdType k = 2;
  double testPoint[3] = {0.5, 0.0, 0.0};
  vtkSmartPointer<vtkIdList> result =
    vtkSmartPointer<vtkIdList>::New();

  pointTree->FindClosestNPoints(k, testPoint, result);

  for(vtkIdType i = 0; i < k; i++)
  {
    vtkIdType point_ind = result->GetId(i);
    double p[3];
    points->GetPoint(point_ind, p);
    std::cout << "Closest point "
              << i << ": Point " << point_ind << ": ("
              << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BuildLocatorFromKClosestPoints)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BuildLocatorFromKClosestPoints MACOSX_BUNDLE BuildLocatorFromKClosestPoints.cxx)
 
target_link_libraries(BuildLocatorFromKClosestPoints ${VTK_LIBRARIES})
```

**Download and Build BuildLocatorFromKClosestPoints**

Click [here to download BuildLocatorFromKClosestPoints](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BuildLocatorFromKClosestPoints.tar) and its *CMakeLists.txt* file.
Once the *tarball BuildLocatorFromKClosestPoints.tar* has been downloaded and extracted,
```
cd BuildLocatorFromKClosestPoints/build 
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
./BuildLocatorFromKClosestPoints
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

