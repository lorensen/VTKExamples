[VTKExamples](Home)/[Cxx](Cxx)/GeometricObjects/PolygonIntersection

**PolygonIntersection.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolygon.h>

int main(int, char*[])
{
  // Create a square in the XY plane
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);
 
  // Create the polygon
  vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();
  polygon->GetPoints()->DeepCopy(points);
  polygon->GetPointIds()->SetNumberOfIds(4); // 4 corners of the square
  polygon->GetPointIds()->SetId(0, 0);
  polygon->GetPointIds()->SetId(1, 1);
  polygon->GetPointIds()->SetId(2, 2);
  polygon->GetPointIds()->SetId(3, 3);

  // Inputs
  double p1[3] = {0.1, 0, -1.0};
  double p2[3] = {0.1, 0, 1.0};
  double tolerance = 0.001;
  // Outputs
  double t; // Parametric coordinate of intersection (0 (corresponding to p1) to 1 (corresponding to p2))
  double x[3]; // The coordinate of the intersection
  double pcoords[3];
  int subId;

  vtkIdType iD = polygon->IntersectWithLine(p1, p2, tolerance, t, x, pcoords, subId);

  std::cout << "intersected? " << iD << std::endl;
  std::cout << "intersection: " << x[0] << " " << x[1] << " " << x[2] << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PolygonIntersection)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PolygonIntersection MACOSX_BUNDLE PolygonIntersection.cxx)
 
target_link_libraries(PolygonIntersection ${VTK_LIBRARIES})
```

**Download and Build PolygonIntersection**

Click [here to download PolygonIntersection](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PolygonIntersection.tar) and its *CMakeLists.txt* file.
Once the *tarball PolygonIntersection.tar* has been downloaded and extracted,
```
cd PolygonIntersection/build 
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
./PolygonIntersection
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

