[VTKExamples](/index/)/[Cxx](/Cxx)/SimpleOperations/ProjectPointPlane

### Description
This example projects a point onto a plane. To use this example, you must have the CVSHEAD version of VTK (as of 2/2/2010).

**ProjectPointPlane.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPlane.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPlane> plane = 
      vtkSmartPointer<vtkPlane>::New();
  plane->SetOrigin(0.0, 0.0, 0.0);
  plane->SetNormal(0.0, 0.0, 1.0);
  
  double p[3] = {23.1, 54.6, 9.2};
  double origin[3] = {0.0, 0.0, 0.0};
  double normal[3] = {0.0, 0.0, 1.0};
  double projected[3];
  
  plane->ProjectPoint(p, origin, normal, projected);
 
  std::cout << "Projected: " << projected[0] << " " 
            << projected[1] << " " << projected[2] << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ProjectPointPlane)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ProjectPointPlane MACOSX_BUNDLE ProjectPointPlane.cxx)
 
target_link_libraries(ProjectPointPlane ${VTK_LIBRARIES})
```

**Download and Build ProjectPointPlane**

Click [here to download ProjectPointPlane](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ProjectPointPlane.tar) and its *CMakeLists.txt* file.
Once the *tarball ProjectPointPlane.tar* has been downloaded and extracted,
```
cd ProjectPointPlane/build 
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
./ProjectPointPlane
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

