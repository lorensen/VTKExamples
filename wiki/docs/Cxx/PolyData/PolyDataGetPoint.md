[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/PolyDataGetPoint

### Description
This example demonstrates how to obtain the coordinates of a point in a vtkPolyData object.

* Suggested by Sara Rolfe

**PolyDataGetPoint.cxx**
```c++
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>

int main(int, char*[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkPolyData* polydata = sphereSource->GetOutput();

  // Write all of the coordinates of the points in the vtkPolyData to the console.
  for(vtkIdType i = 0; i < polydata->GetNumberOfPoints(); i++)
  {
    double p[3];
    polydata->GetPoint(i,p);
    // This is identical to:
    // polydata->GetPoints()->GetPoint(i,p);
    std::cout << "Point " << i << " : (" << p[0] << " " << p[1] << " " << p[2] << ")" << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PolyDataGetPoint)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PolyDataGetPoint MACOSX_BUNDLE PolyDataGetPoint.cxx)
 
target_link_libraries(PolyDataGetPoint ${VTK_LIBRARIES})
```

**Download and Build PolyDataGetPoint**

Click [here to download PolyDataGetPoint](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PolyDataGetPoint.tar) and its *CMakeLists.txt* file.
Once the *tarball PolyDataGetPoint.tar* has been downloaded and extracted,
```
cd PolyDataGetPoint/build 
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
./PolyDataGetPoint
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

