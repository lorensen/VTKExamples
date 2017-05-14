[VTKExamples](/index/)/[Cxx](/Cxx)/StructuredData/GetLinearPointId

**GetLinearPointId.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkStructuredData.h>
#include <vtkStructuredGrid.h>

int main(int, char *[])
{
  // Create a grid
  vtkSmartPointer<vtkStructuredGrid> structuredGrid =
    vtkSmartPointer<vtkStructuredGrid>::New();

  // Set the dimensions of the grid
  {
    int dims[3] = {5,10,1};
    structuredGrid->SetDimensions(dims);
  }

  // Retrieve the dimensions of the grid
  int dimensions[3];
  structuredGrid->GetDimensions(dimensions);

  {
  int queryPoint[3] = {4, 0, 0};
  vtkIdType pointId = vtkStructuredData::ComputePointId(dimensions, queryPoint);

  std::cout << "PointId: " << pointId << std::endl; // Outputs '4'
  }
  
  {
  int queryPoint[3] = {0, 1, 0};
  vtkIdType pointId = vtkStructuredData::ComputePointId(dimensions, queryPoint);

  std::cout << "PointId: " << pointId << std::endl; // Outputs '5'
  }
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GetLinearPointId)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GetLinearPointId MACOSX_BUNDLE GetLinearPointId.cxx)
 
target_link_libraries(GetLinearPointId ${VTK_LIBRARIES})
```

**Download and Build GetLinearPointId**

Click [here to download GetLinearPointId](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GetLinearPointId.tar) and its *CMakeLists.txt* file.
Once the *tarball GetLinearPointId.tar* has been downloaded and extracted,
```
cd GetLinearPointId/build 
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
./GetLinearPointId
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

