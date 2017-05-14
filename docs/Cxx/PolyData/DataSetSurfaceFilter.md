[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/DataSetSurfaceFilter

### Description
This example demonstrates how to convert an unstructured grid to a polydata. Currently nothing is done with the resulting polydata. If someone has a good data set that demonstrates the conversion, please let us know.

**DataSetSurfaceFilter.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCellArray.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkPointSource.h>

int main(int, char *[])
{ 

  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = 
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  
  vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceFilter = 
    vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  surfaceFilter->SetInput(unstructuredGrid);
#else
  surfaceFilter->SetInputData(unstructuredGrid);
#endif
  surfaceFilter->Update(); 
 
  vtkPolyData* polydata = surfaceFilter->GetOutput();

  std::cout << "Output has " << polydata->GetNumberOfPoints() << " points." << std::endl;  

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DataSetSurfaceFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DataSetSurfaceFilter MACOSX_BUNDLE DataSetSurfaceFilter.cxx)
 
target_link_libraries(DataSetSurfaceFilter ${VTK_LIBRARIES})
```

**Download and Build DataSetSurfaceFilter**

Click [here to download DataSetSurfaceFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DataSetSurfaceFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball DataSetSurfaceFilter.tar* has been downloaded and extracted,
```
cd DataSetSurfaceFilter/build 
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
./DataSetSurfaceFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

