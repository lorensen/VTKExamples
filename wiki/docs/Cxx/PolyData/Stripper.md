[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/Stripper

**Stripper.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkStripper.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  std::cout << "Number of cells before stripping: " << sphereSource->GetOutput()->GetNumberOfCells() << std::endl;
  
  vtkSmartPointer<vtkStripper> stripper = 
      vtkSmartPointer<vtkStripper>::New();
  stripper->SetInputConnection(sphereSource->GetOutputPort());
  stripper->Update();
  
  std::cout << "Number of cells after stripping: " << stripper->GetOutput()->GetNumberOfCells() << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Stripper)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Stripper MACOSX_BUNDLE Stripper.cxx)
 
target_link_libraries(Stripper ${VTK_LIBRARIES})
```

**Download and Build Stripper**

Click [here to download Stripper](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Stripper.tar) and its *CMakeLists.txt* file.
Once the *tarball Stripper.tar* has been downloaded and extracted,
```
cd Stripper/build 
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
./Stripper
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

