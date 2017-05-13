[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/CenterOfMass

**CenterOfMass.cxx**
```c++
#include <vtkVersion.h>
#include <vtkCenterOfMass.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

#include <limits>
#include <cmath>

int main(int, char*[])
{
  // Create a point set of a square
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);
  points->InsertNextPoint(0,1,0);
  points->InsertNextPoint(1,1,0);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Compute the center of mass
  vtkSmartPointer<vtkCenterOfMass> centerOfMassFilter =
    vtkSmartPointer<vtkCenterOfMass>::New();
#if VTK_MAJOR_VERSION <= 5
  centerOfMassFilter->SetInput(polydata);
#else
  centerOfMassFilter->SetInputData(polydata);
#endif
  centerOfMassFilter->SetUseScalarsAsWeights(false);
  centerOfMassFilter->Update();

  double center[3];
  centerOfMassFilter->GetCenter(center);

  std::cout << "Center of mass is " << center[0] << " " << center[1] << " " << center[2] << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CenterOfMass)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CenterOfMass MACOSX_BUNDLE CenterOfMass.cxx)
 
target_link_libraries(CenterOfMass ${VTK_LIBRARIES})
```

**Download and Build CenterOfMass**

Click [here to download CenterOfMass](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CenterOfMass.tar) and its *CMakeLists.txt* file.
Once the *tarball CenterOfMass.tar* has been downloaded and extracted,
```
cd CenterOfMass/build 
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
./CenterOfMass
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

