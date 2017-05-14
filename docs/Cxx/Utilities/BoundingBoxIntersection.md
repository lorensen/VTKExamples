[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/BoundingBoxIntersection

**BoundingBoxIntersection.cxx**
```c++
#include <vtkBoundingBox.h>

int main(int, char *[])
{
  vtkBoundingBox boundingBox0;
  boundingBox0.SetBounds(0, 1, 0, 1, 0, 1);
  
  vtkBoundingBox boundingBox1;
  boundingBox1.SetBounds(5, 6, 5, 6, 5, 6);
  
  vtkBoundingBox boundingBox2;
  boundingBox2.SetBounds(0.5, 1.5, 0.5, 1.5, 0.5, 1.5);
  
  std::cout << boundingBox0.IntersectBox(boundingBox1) << std::endl; // Should be 0
  std::cout << boundingBox0.IntersectBox(boundingBox2) << std::endl; // Should be 1
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BoundingBoxIntersection)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BoundingBoxIntersection MACOSX_BUNDLE BoundingBoxIntersection.cxx)
 
target_link_libraries(BoundingBoxIntersection ${VTK_LIBRARIES})
```

**Download and Build BoundingBoxIntersection**

Click [here to download BoundingBoxIntersection](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BoundingBoxIntersection.tar) and its *CMakeLists.txt* file.
Once the *tarball BoundingBoxIntersection.tar* has been downloaded and extracted,
```
cd BoundingBoxIntersection/build 
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
./BoundingBoxIntersection
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

