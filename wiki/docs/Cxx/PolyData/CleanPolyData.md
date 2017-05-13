[VTKExamples](Home)/[Cxx](Cxx)/PolyData/CleanPolyData

### Description
When a cube is created, it has 24 vertices (4 for each face). This is done because 
the normal at each face is very different. Often we would want a cube to only have 8 vertices. The vtkCleanPolyData filter removes coincident points, resulting in the cube we would expect.

**CleanPolyData.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkPolyData.h>
#include <vtkCleanPolyData.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkCubeSource> cubeSource = 
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();
  
  std::cout << "Input cube has " << cubeSource->GetOutput()->GetNumberOfPoints() 
    << " vertices." << std::endl;
    
  vtkSmartPointer<vtkCleanPolyData> cleanPolyData = 
      vtkSmartPointer<vtkCleanPolyData>::New();
  cleanPolyData->SetInputConnection(cubeSource->GetOutputPort());
  cleanPolyData->Update();
  
  std::cout << "Cleaned cube has " << cleanPolyData->GetOutput()->GetNumberOfPoints() 
    << " vertices." << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CleanPolyData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CleanPolyData MACOSX_BUNDLE CleanPolyData.cxx)
 
target_link_libraries(CleanPolyData ${VTK_LIBRARIES})
```

**Download and Build CleanPolyData**

Click [here to download CleanPolyData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CleanPolyData.tar) and its *CMakeLists.txt* file.
Once the *tarball CleanPolyData.tar* has been downloaded and extracted,
```
cd CleanPolyData/build 
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
./CleanPolyData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

