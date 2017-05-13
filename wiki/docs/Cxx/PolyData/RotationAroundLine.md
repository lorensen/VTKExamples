[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/RotationAroundLine

### Description
This example demonstrates how to rotate an object around an axis. For the demo, we rotate a cone 10 degrees around the y axis.

**RotationAroundLine.cxx**
```c++
#include <vtkConeSource.h>
#include <vtkPolyData.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataWriter.h>
 
int main(int, char *[])
{
  //Create a cone
  vtkSmartPointer<vtkConeSource> coneSource = 
    vtkSmartPointer<vtkConeSource>::New();
  
  {
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(coneSource->GetOutputPort());
  writer->SetFileName("original.vtp");
  writer->Write();
  }
  
  vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
  //transform->RotateWXYZ(double angle, double x, double y, double z);
  transform->RotateWXYZ(10, 0, 1, 0);
  
  vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter = 
      vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  
  transformFilter->SetTransform(transform);
  transformFilter->SetInputConnection(coneSource->GetOutputPort());
  transformFilter->Update();
  
  {
    vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
        vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetInputConnection(transformFilter->GetOutputPort());
    writer->SetFileName("transformed.vtp");
    writer->Write();
  }
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RotationAroundLine)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RotationAroundLine MACOSX_BUNDLE RotationAroundLine.cxx)
 
target_link_libraries(RotationAroundLine ${VTK_LIBRARIES})
```

**Download and Build RotationAroundLine**

Click [here to download RotationAroundLine](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RotationAroundLine.tar) and its *CMakeLists.txt* file.
Once the *tarball RotationAroundLine.tar* has been downloaded and extracted,
```
cd RotationAroundLine/build 
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
./RotationAroundLine
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

