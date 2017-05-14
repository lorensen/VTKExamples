[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/Box

**Box.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkBox.h>

int main(int, char *[])
{
  // Define a box
  double bounds[6] = {-1,1,-1,1,-1,1};

  // Define a ray
  double rayOrigin[3] = {-5.0, 0, 0};
  double rayDirection[3] = {1.0, 0, 0};

  double intersection[3];
  double t;

  char hit = vtkBox::IntersectBox(bounds, rayOrigin, rayDirection, intersection, t);

  if(!hit)
  {
    std::cout << "Not hit!" << std::endl;
  }
  else
  {
    // Intersection should be (-1.0, 0, 0)
    std::cout << "Intersection is " << intersection[0] << " " << intersection[1] << " " << intersection[2] << std::endl;
    std::cout << "t is " << t << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Box)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Box MACOSX_BUNDLE Box.cxx)
 
target_link_libraries(Box ${VTK_LIBRARIES})
```

**Download and Build Box**

Click [here to download Box](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Box.tar) and its *CMakeLists.txt* file.
Once the *tarball Box.tar* has been downloaded and extracted,
```
cd Box/build 
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
./Box
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

