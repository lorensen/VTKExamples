[VTKExamples](/home/)/[Cxx](/Cxx)/ImageData/CellIdFromGridCoordinates

**CellIdFromGridCoordinates.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkStructuredData.h>

int main(int, char *[])
{

  vtkSmartPointer<vtkImageData> grid = vtkSmartPointer<vtkImageData>::New();
  grid->SetOrigin(0, 0, 0);

  unsigned int numVoxelsPerDimension = 2; //the number of voxels in each dimension
  grid->SetSpacing(1, 1, 1);

  int extent[6];
  extent[0] = 0;
  extent[1] = numVoxelsPerDimension;
  extent[2] = 0;
  extent[3] = numVoxelsPerDimension;
  extent[4] = 0;
  extent[5] = numVoxelsPerDimension;
  grid->SetExtent(extent);
#if VTK_MAJOR_VERSION <= 5
  grid->SetScalarTypeToInt();
  grid->SetNumberOfScalarComponents(1);
#else
  grid->AllocateScalars(VTK_INT,1);
#endif

  for(unsigned int i = 0; i < numVoxelsPerDimension; ++i)
  {
    for(unsigned int j = 0; j < numVoxelsPerDimension; ++j)
    {
      for(unsigned int k = 0; k < numVoxelsPerDimension; ++k)
      {
        int pos[3];
        pos[0] = i;
        pos[1] = j;
        pos[2] = k;

        vtkIdType id = vtkStructuredData::ComputeCellIdForExtent(extent, pos);
        std::cout << "Cell " << i << " " << j << " " << k << " has id : " << id << std::endl;
      }
    }
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CellIdFromGridCoordinates)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CellIdFromGridCoordinates MACOSX_BUNDLE CellIdFromGridCoordinates.cxx)
 
target_link_libraries(CellIdFromGridCoordinates ${VTK_LIBRARIES})
```

**Download and Build CellIdFromGridCoordinates**

Click [here to download CellIdFromGridCoordinates](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CellIdFromGridCoordinates.tar) and its *CMakeLists.txt* file.
Once the *tarball CellIdFromGridCoordinates.tar* has been downloaded and extracted,
```
cd CellIdFromGridCoordinates/build 
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
./CellIdFromGridCoordinates
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

