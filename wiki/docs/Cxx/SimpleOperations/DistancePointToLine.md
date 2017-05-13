[VTKExamples](Home)/[Cxx](Cxx)/SimpleOperations/DistancePointToLine

### Description
This example computes the distance from a point to a line.

**DistancePointToLine.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkLine.h>
#include <vtkPoints.h>

int main(int, char *[])
{
  double lineP0[3] = {0.0, 0.0, 0.0};
  double lineP1[3] = {2.0, 0.0, 0.0};
  
  double p0[3] = {1.0, 0, 0};
  double p1[3] = {1.0, 2.0, 0};
  
  /*
  vtkSmartPointer<vtkLine> line = 
    vtkSmartPointer<vtkLine>::New();
  line->GetPoints()->SetPoint(0, lineP0);
  line->GetPoints()->SetPoint(0, lineP1);
  */
  
  {
  double dist0 = vtkLine::DistanceToLine(p0, lineP0, lineP1);
  std::cout << "Dist0: " << dist0 << std::endl;
  
  double dist1 = vtkLine::DistanceToLine(p1, lineP0, lineP1);
  std::cout << "Dist1: " << dist1 << std::endl;
  }
  
  {
  double t;
  double closest[3];
  double dist0 = vtkLine::DistanceToLine(p0, lineP0, lineP1, t, closest);
  std::cout << "Dist0: " << dist0 << " closest point: " << closest[0] << " " << closest[1] << " " << closest[2] << std::endl;
  
  double dist1 = vtkLine::DistanceToLine(p1, lineP0, lineP1, t, closest);
  std::cout << "Dist1: " << dist1 << " closest point: " << closest[0] << " " << closest[1] << " " << closest[2] << std::endl;
  } 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DistancePointToLine)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DistancePointToLine MACOSX_BUNDLE DistancePointToLine.cxx)
 
target_link_libraries(DistancePointToLine ${VTK_LIBRARIES})
```

**Download and Build DistancePointToLine**

Click [here to download DistancePointToLine](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DistancePointToLine.tar) and its *CMakeLists.txt* file.
Once the *tarball DistancePointToLine.tar* has been downloaded and extracted,
```
cd DistancePointToLine/build 
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
./DistancePointToLine
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

