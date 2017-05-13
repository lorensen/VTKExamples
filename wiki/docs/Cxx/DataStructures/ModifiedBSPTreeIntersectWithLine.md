[VTKExamples](Home)/[Cxx](Cxx)/DataStructures/ModifiedBSPTreeIntersectWithLine

**ModifiedBSPTreeIntersectWithLine.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkModifiedBSPTree.h>
#include <vtkSphereSource.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  // Create the tree
  vtkSmartPointer<vtkModifiedBSPTree> bspTree =
    vtkSmartPointer<vtkModifiedBSPTree>::New();
  bspTree->SetDataSet(sphereSource->GetOutput());
  bspTree->BuildLocator();

  // Inputs
  double p1[3] = {-2,0,0};
  double p2[3] = {2,0,0};
  double tolerance = .001;
  
  // Outputs
  double t; // Parametric coordinate of intersection (0 (corresponding to p1) to 1 (corresponding to p2))
  double x[3]; // The coordinate of the intersection
  double pcoords[3];
  int subId;
  
  // Note: for a typical use case (ray-triangle intersection), pcoords and subId will not be used
  vtkIdType iD = bspTree->IntersectWithLine(p1, p2, tolerance, t, x, pcoords, subId);

  std::cout << "iD: " << iD << std::endl;
  std::cout << "t: " << t << std::endl;
  std::cout << "x: " << x[0] << " " << x[1] << " " << x[2] << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ModifiedBSPTreeIntersectWithLine)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ModifiedBSPTreeIntersectWithLine MACOSX_BUNDLE ModifiedBSPTreeIntersectWithLine.cxx)
 
target_link_libraries(ModifiedBSPTreeIntersectWithLine ${VTK_LIBRARIES})
```

**Download and Build ModifiedBSPTreeIntersectWithLine**

Click [here to download ModifiedBSPTreeIntersectWithLine](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ModifiedBSPTreeIntersectWithLine.tar) and its *CMakeLists.txt* file.
Once the *tarball ModifiedBSPTreeIntersectWithLine.tar* has been downloaded and extracted,
```
cd ModifiedBSPTreeIntersectWithLine/build 
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
./ModifiedBSPTreeIntersectWithLine
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

