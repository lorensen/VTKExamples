[VTKExamples](/index/)/[Cxx](/Cxx)/InfoVis/PassThrough

**PassThrough.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkPassThrough.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  std::cout << "Points before: " << sphereSource->GetOutput()->GetNumberOfPoints() << std::endl;
  
  vtkSmartPointer<vtkPassThrough> passThrough = 
    vtkSmartPointer<vtkPassThrough>::New();
  passThrough->SetInputConnection(sphereSource->GetOutputPort());
  passThrough->Update();
  
  vtkSmartPointer<vtkPolyData> output = vtkPolyData::SafeDownCast(passThrough->GetOutput());
  
  std::cout << "Points after: " << output->GetNumberOfPoints() << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PassThrough)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PassThrough MACOSX_BUNDLE PassThrough.cxx)
 
target_link_libraries(PassThrough ${VTK_LIBRARIES})
```

**Download and Build PassThrough**

Click [here to download PassThrough](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PassThrough.tar) and its *CMakeLists.txt* file.
Once the *tarball PassThrough.tar* has been downloaded and extracted,
```
cd PassThrough/build 
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
./PassThrough
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

