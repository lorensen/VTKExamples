[VTKExamples](Home)/[Cxx](Cxx)/Utilities/PointInPolygon

**PointInPolygon.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolygon.h>

int main(int, char *[])
{
  // Create the polygon
  vtkSmartPointer<vtkPolygon> polygon =
    vtkSmartPointer<vtkPolygon>::New();
  polygon->GetPoints()->InsertNextPoint(0.0, 0.0, 0.0);
  polygon->GetPoints()->InsertNextPoint(1.0, 0.0, 0.0);
  polygon->GetPoints()->InsertNextPoint(1.0, 1.0, 0.0);
  polygon->GetPoints()->InsertNextPoint(0.0, 1.0, 0.0);

  double testIn[3] = {0.5, 0.5, 0.0};
  double testOut[3] = {2.0, 0.5, 0.0};

  double n[3];
  polygon->ComputeNormal(polygon->GetPoints()->GetNumberOfPoints(),
          static_cast<double*>(polygon->GetPoints()->GetData()->GetVoidPointer(0)), n);

  double bounds[6];
  polygon->GetPoints()->GetBounds(bounds);

  std::cout << "testIn in polygon? " << polygon->PointInPolygon(testIn,
      polygon->GetPoints()->GetNumberOfPoints(), static_cast<double*>(
      polygon->GetPoints()->GetData()->GetVoidPointer(0)), bounds, n) << std::endl;

  std::cout << "testOut in polygon? " << polygon->PointInPolygon(testOut,
      polygon->GetPoints()->GetNumberOfPoints(), static_cast<double*>(
      polygon->GetPoints()->GetData()->GetVoidPointer(0)), bounds, n) << std::endl;

  /*
  std::cout << "New functions:" << std::endl;

  std::cout << "testIn in polygon? " << polygon->PointInPolygon(testIn) << std::endl;

  std::cout << "testOut in polygon? " << polygon->PointInPolygon(testOut) << std::endl;
  */
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PointInPolygon)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PointInPolygon MACOSX_BUNDLE PointInPolygon.cxx)
 
target_link_libraries(PointInPolygon ${VTK_LIBRARIES})
```

**Download and Build PointInPolygon**

Click [here to download PointInPolygon](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PointInPolygon.tar) and its *CMakeLists.txt* file.
Once the *tarball PointInPolygon.tar* has been downloaded and extracted,
```
cd PointInPolygon/build 
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
./PointInPolygon
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

