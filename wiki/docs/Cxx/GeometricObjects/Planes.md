[VTKExamples](Home)/[Cxx](Cxx)/GeometricObjects/Planes

**Planes.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPlanes.h>
#include <vtkCamera.h>
#include <vtkSphereSource.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>

int main(int, char *[])
{
  // one way
  {
  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  double planesArray[24];

  camera->GetFrustumPlanes(1, planesArray);

  vtkSmartPointer<vtkPlanes> planes =
    vtkSmartPointer<vtkPlanes>::New();
  planes->SetFrustumPlanes(planesArray);
  }

  // another way
  {
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  double bounds[6];
  sphereSource->GetOutput()->GetBounds(bounds);

  vtkSmartPointer<vtkPlanes> planes =
    vtkSmartPointer<vtkPlanes>::New();
  planes->SetBounds(bounds);
  }
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Planes)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Planes MACOSX_BUNDLE Planes.cxx)
 
target_link_libraries(Planes ${VTK_LIBRARIES})
```

**Download and Build Planes**

Click [here to download Planes](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Planes.tar) and its *CMakeLists.txt* file.
Once the *tarball Planes.tar* has been downloaded and extracted,
```
cd Planes/build 
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
./Planes
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

