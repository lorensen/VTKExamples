[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/GeometryFilter

### Description
This example demonstrates how to convert an unstructured grid to a polydata. Currently nothing is done with the resulting polydata. If someone has a good data set that demonstrates the conversion, please let us know.

**GeometryFilter.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCellArray.h>
#include <vtkGeometryFilter.h>
#include <vtkPointSource.h>

int main(int, char *[])
{ 
  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = 
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  
  vtkSmartPointer<vtkGeometryFilter> geometryFilter = 
    vtkSmartPointer<vtkGeometryFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  geometryFilter->SetInput(unstructuredGrid);
#else
  geometryFilter->SetInputData(unstructuredGrid);
#endif
  geometryFilter->Update(); 
 
  vtkPolyData* polydata = geometryFilter->GetOutput();

  std::cout << "Output has " << polydata->GetNumberOfPoints() << " points." << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GeometryFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GeometryFilter MACOSX_BUNDLE GeometryFilter.cxx)
 
target_link_libraries(GeometryFilter ${VTK_LIBRARIES})
```

**Download and Build GeometryFilter**

Click [here to download GeometryFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GeometryFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball GeometryFilter.tar* has been downloaded and extracted,
```
cd GeometryFilter/build 
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
./GeometryFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

