[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/ConvexHullShrinkWrap

### Description
This example creates a point cloud, and a sphere larger than the point cloud which fully contains the cloud. It then "shrink wraps" the sphere onto the points. This produces approximately a convex hull.

**ConvexHullShrinkWrap.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkPointSource.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkXMLPolyDataWriter.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(10);
  sphereSource->SetPhiResolution(50);
  sphereSource->SetThetaResolution(50);
  sphereSource->Update();
  
  vtkSmartPointer<vtkPointSource> pointSource = 
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(40);
  pointSource->SetRadius(2);
  pointSource->Update();
  
  {
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("input.vtp");
  writer->SetInputConnection(sphereSource->GetOutputPort());
  writer->Write();
  }
  
  {
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("points.vtp");
  writer->SetInputConnection(pointSource->GetOutputPort());
  writer->Write();
  }
    
  vtkSmartPointer<vtkSmoothPolyDataFilter> smoothFilter = 
    vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
  smoothFilter->SetInputConnection(0, sphereSource->GetOutputPort());
  smoothFilter->SetInputConnection(1, pointSource->GetOutputPort());
  smoothFilter->Update();
  
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("output.vtp");
  writer->SetInputConnection(smoothFilter->GetOutputPort());
  writer->Write();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ConvexHullShrinkWrap)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ConvexHullShrinkWrap MACOSX_BUNDLE ConvexHullShrinkWrap.cxx)
 
target_link_libraries(ConvexHullShrinkWrap ${VTK_LIBRARIES})
```

**Download and Build ConvexHullShrinkWrap**

Click [here to download ConvexHullShrinkWrap](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ConvexHullShrinkWrap.tar) and its *CMakeLists.txt* file.
Once the *tarball ConvexHullShrinkWrap.tar* has been downloaded and extracted,
```
cd ConvexHullShrinkWrap/build 
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
./ConvexHullShrinkWrap
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

