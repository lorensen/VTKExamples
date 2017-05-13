[VTKExamples](/home/)/[Cxx](/Cxx)/SimpleOperations/PerspectiveTransform

### Description
The perspective transform automatically appends the "homogeneous 1" to the point before it is multiplied by the matrix. It then divides the first 3 coordinates of the result by the 4th coordinate of the result. For comparison, the standard projection (vtkTransform) is also performed with the same matrix and the same point. Note that the results are much different.

**PerspectiveTransform.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPerspectiveTransform.h>
#include <vtkTransform.h>
#include <vtkMatrix4x4.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMatrix4x4> m =
    vtkSmartPointer<vtkMatrix4x4>::New();
  m->SetElement(0,0,1);
  m->SetElement(0,1,2);
  m->SetElement(0,2,3);
  m->SetElement(0,3,4);
  m->SetElement(1,0,2);
  m->SetElement(1,1,2);
  m->SetElement(1,2,3);
  m->SetElement(1,3,4);
  m->SetElement(2,0,3);
  m->SetElement(2,1,2);
  m->SetElement(2,2,3);
  m->SetElement(2,3,4);
  m->SetElement(3,0,4);
  m->SetElement(3,1,2);
  m->SetElement(3,2,3);
  m->SetElement(3,3,4);
  
  vtkSmartPointer<vtkPerspectiveTransform> perspectiveTransform = 
      vtkSmartPointer<vtkPerspectiveTransform>::New();
  perspectiveTransform->SetMatrix(m);

  vtkSmartPointer<vtkTransform> transform =
      vtkSmartPointer<vtkTransform>::New();
  transform->SetMatrix(m);

  double p[3];
  p[0] = 1.0;
  p[1] = 2.0;
  p[2] = 3.0;
  
  double normalProjection[3];
  transform->TransformPoint(p, normalProjection);
  
  std::cout << "Standard projection: "
    << normalProjection[0] << " " 
    << normalProjection[1] << " " 
    << normalProjection[2] << std::endl;
  
  double perspectiveProjection[3];
  perspectiveTransform->TransformPoint(p, perspectiveProjection);
  std::cout << "Perspective projection: "
    << perspectiveProjection[0] 
    << " " << perspectiveProjection[1] << " " 
    << perspectiveProjection[2] << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PerspectiveTransform)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PerspectiveTransform MACOSX_BUNDLE PerspectiveTransform.cxx)
 
target_link_libraries(PerspectiveTransform ${VTK_LIBRARIES})
```

**Download and Build PerspectiveTransform**

Click [here to download PerspectiveTransform](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PerspectiveTransform.tar) and its *CMakeLists.txt* file.
Once the *tarball PerspectiveTransform.tar* has been downloaded and extracted,
```
cd PerspectiveTransform/build 
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
./PerspectiveTransform
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

