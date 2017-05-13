[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/ShrinkPolyData

**ShrinkPolyData.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkShrinkPolyData.h>
#include <vtkXMLPolyDataWriter.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(10);
  sphereSource->SetPhiResolution(50);
  sphereSource->SetThetaResolution(50);
  sphereSource->Update();

  {
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("sphere.vtp");
  writer->SetInputConnection(sphereSource->GetOutputPort());
  writer->Write();
  }

  vtkSmartPointer<vtkShrinkPolyData> shrinkFilter =
      vtkSmartPointer<vtkShrinkPolyData>::New();
  shrinkFilter->SetInputConnection(sphereSource->GetOutputPort());
  shrinkFilter->Update();
  
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("output.vtp");
  writer->SetInputConnection(shrinkFilter->GetOutputPort());
  writer->Write();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ShrinkPolyData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ShrinkPolyData MACOSX_BUNDLE ShrinkPolyData.cxx)
 
target_link_libraries(ShrinkPolyData ${VTK_LIBRARIES})
```

**Download and Build ShrinkPolyData**

Click [here to download ShrinkPolyData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ShrinkPolyData.tar) and its *CMakeLists.txt* file.
Once the *tarball ShrinkPolyData.tar* has been downloaded and extracted,
```
cd ShrinkPolyData/build 
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
./ShrinkPolyData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

