[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/BoundingBox

### Description
**See also:** [Outline](Cxx/PolyData/Outline) and [CubeAxesActor2D](Cxx/Visualization/CubeAxesActor2D)

**BoundingBox.cxx**
```c++
#include <vtkBoundingBox.h>

int main(int, char *[])
{
  double p0[3] = {0,0,0};
  double p1[3] = {0.5,0.5,0.5};
  double p2[3] = {1.0,1.0,1.0};

  vtkBoundingBox boundingBox;

  boundingBox.AddPoint(p0);

  double bounds[6];

  boundingBox.GetBounds(bounds);
  std::cout << "Bounds: " << bounds[0] << ", " << bounds[1] << ", " << bounds[2] << ", "
            << bounds[3] << ", " << bounds[4] << ", " << bounds[5] << std::endl;

  // After adding this point, the box gets bigger
  boundingBox.AddPoint(p2);

  boundingBox.GetBounds(bounds);
  std::cout << "Bounds: " << bounds[0] << ", " << bounds[1] << ", " << bounds[2] << ", "
            << bounds[3] << ", " << bounds[4] << ", " << bounds[5] << std::endl;

  // After adding this point, the box size does not change as the point is already inside the box
  boundingBox.AddPoint(p1);

  boundingBox.GetBounds(bounds);
  std::cout << "Bounds: " << bounds[0] << ", " << bounds[1] << ", " << bounds[2] << ", "
            << bounds[3] << ", " << bounds[4] << ", " << bounds[5] << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BoundingBox)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BoundingBox MACOSX_BUNDLE BoundingBox.cxx)
 
target_link_libraries(BoundingBox ${VTK_LIBRARIES})
```

**Download and Build BoundingBox**

Click [here to download BoundingBox](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BoundingBox.tar) and its *CMakeLists.txt* file.
Once the *tarball BoundingBox.tar* has been downloaded and extracted,
```
cd BoundingBox/build 
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
./BoundingBox
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

