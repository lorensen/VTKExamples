[VTKExamples](/home/)/[Cxx](/Cxx)/DataStructures/OBBTreeIntersectWithLine

### Description
vtkOBBTree returns ALL intersections with a line and the dataset. If you want the closest intersection, you must manually find it. In this example, we create a sphere and intersect a single line with it.

**OBBTreeIntersectWithLine.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkLine.h>
#include <vtkOBBTree.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  // Create the locator
  vtkSmartPointer<vtkOBBTree> tree = 
    vtkSmartPointer<vtkOBBTree>::New();
  tree->SetDataSet(sphereSource->GetOutput());
  tree->BuildLocator();
  
  // Intersect the locator with the line
  double lineP0[3] = {0.0, 0.0, 0.0};
  double lineP1[3] = {0.0, 0.0, 2.0};
  vtkSmartPointer<vtkPoints> intersectPoints = 
    vtkSmartPointer<vtkPoints>::New();
  
  tree->IntersectWithLine(lineP0, lineP1, intersectPoints, NULL);

  std::cout << "NumPoints: " << intersectPoints->GetNumberOfPoints()
            << std::endl;

  // Display list of intersections
  double intersection[3];
  for(int i = 0; i < intersectPoints->GetNumberOfPoints(); i++ )
  {
    intersectPoints->GetPoint(i, intersection);
    std::cout << "Intersection " << i << ": "
              << intersection[0] << ", "
              << intersection[1] << ", "
              << intersection[2] << std::endl;
  }
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(OBBTreeIntersectWithLine)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(OBBTreeIntersectWithLine MACOSX_BUNDLE OBBTreeIntersectWithLine.cxx)
 
target_link_libraries(OBBTreeIntersectWithLine ${VTK_LIBRARIES})
```

**Download and Build OBBTreeIntersectWithLine**

Click [here to download OBBTreeIntersectWithLine](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/OBBTreeIntersectWithLine.tar) and its *CMakeLists.txt* file.
Once the *tarball OBBTreeIntersectWithLine.tar* has been downloaded and extracted,
```
cd OBBTreeIntersectWithLine/build 
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
./OBBTreeIntersectWithLine
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

