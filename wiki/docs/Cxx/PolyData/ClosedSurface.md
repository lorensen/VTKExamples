[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/ClosedSurface

**ClosedSurface.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkFeatureEdges.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkFeatureEdges> featureEdges =
    vtkSmartPointer<vtkFeatureEdges>::New();
  featureEdges->FeatureEdgesOff();
  featureEdges->BoundaryEdgesOn();
  featureEdges->NonManifoldEdgesOn();
  featureEdges->SetInputConnection(sphereSource->GetOutputPort());
  featureEdges->Update();

  int numberOfOpenEdges = featureEdges->GetOutput()->GetNumberOfCells();

  if(numberOfOpenEdges > 0)
  {
    std::cout << "Surface is not closed" << std::endl;
  }
  else
  {
    std::cout << "Surface is closed" << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ClosedSurface)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ClosedSurface MACOSX_BUNDLE ClosedSurface.cxx)
 
target_link_libraries(ClosedSurface ${VTK_LIBRARIES})
```

**Download and Build ClosedSurface**

Click [here to download ClosedSurface](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ClosedSurface.tar) and its *CMakeLists.txt* file.
Once the *tarball ClosedSurface.tar* has been downloaded and extracted,
```
cd ClosedSurface/build 
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
./ClosedSurface
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

