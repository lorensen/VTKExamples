[VTKExamples](Home)/[Cxx](Cxx)/SimpleOperations/DistanceBetweenPoints

### Description
This example finds the squared distance and the Euclidean distance between two 3D points.

**DistanceBetweenPoints.cxx**
```c++
#include <vtkMath.h>
 
int main(int, char *[])
{
  // Create two points.
  double p0[3] = {0.0, 0.0, 0.0};
  double p1[3] = {1.0, 1.0, 1.0};
 
  // Find the squared distance between the points.
  double squaredDistance = vtkMath::Distance2BetweenPoints(p0, p1);

  // Take the square root to get the Euclidean distance between the points.
  double distance = sqrt(squaredDistance);
 
  // Output the results.
  std::cout << "SquaredDistance = " << squaredDistance << std::endl;
  std::cout << "Distance = " << distance << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DistanceBetweenPoints)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DistanceBetweenPoints MACOSX_BUNDLE DistanceBetweenPoints.cxx)
 
target_link_libraries(DistanceBetweenPoints ${VTK_LIBRARIES})
```

**Download and Build DistanceBetweenPoints**

Click [here to download DistanceBetweenPoints](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DistanceBetweenPoints.tar) and its *CMakeLists.txt* file.
Once the *tarball DistanceBetweenPoints.tar* has been downloaded and extracted,
```
cd DistanceBetweenPoints/build 
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
./DistanceBetweenPoints
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

