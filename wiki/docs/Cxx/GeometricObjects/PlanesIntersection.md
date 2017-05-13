[VTKExamples](Home)/[Cxx](Cxx)/GeometricObjects/PlanesIntersection

**PlanesIntersection.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPlanesIntersection.h>
#include <vtkSphereSource.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  double bounds[6];
  sphereSource->GetOutput()->GetBounds(bounds);

  vtkSmartPointer<vtkPoints> box =
    vtkSmartPointer<vtkPoints>::New();

  box->SetNumberOfPoints(8);

  double xMin, xMax, yMin, yMax, zMin, zMax;
  xMin = bounds[0]; xMax = bounds[1];
  yMin = bounds[2]; yMax = bounds[3];
  zMin = bounds[4]; zMax = bounds[5];

  box->SetPoint(0, xMax, yMin, zMax);
  box->SetPoint(1, xMax, yMin, zMin);
  box->SetPoint(2, xMax, yMax, zMin);
  box->SetPoint(3, xMax, yMax, zMax);
  box->SetPoint(4, xMin, yMin, zMax);
  box->SetPoint(5, xMin, yMin, zMin);
  box->SetPoint(6, xMin, yMax, zMin);
  box->SetPoint(7, xMin, yMax, zMax);

  vtkSmartPointer<vtkPlanesIntersection> planesIntersection =
      vtkSmartPointer<vtkPlanesIntersection>::New();
  planesIntersection->SetBounds(bounds);
  
  int intersects = planesIntersection->IntersectsRegion(box);

  std::cout << "Intersects? " << intersects << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PlanesIntersection)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PlanesIntersection MACOSX_BUNDLE PlanesIntersection.cxx)
 
target_link_libraries(PlanesIntersection ${VTK_LIBRARIES})
```

**Download and Build PlanesIntersection**

Click [here to download PlanesIntersection](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PlanesIntersection.tar) and its *CMakeLists.txt* file.
Once the *tarball PlanesIntersection.tar* has been downloaded and extracted,
```
cd PlanesIntersection/build 
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
./PlanesIntersection
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

