[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/PolyDataToUnstructuredGrid

### Description
There is not a filter whose sole purpose is converting a vtkPolyData to a vtkUnstructuredGrid. However, the append filter can accept any type of input, and produces a vtkUnstructuredGrid, so we can use it for this purpose.

**PolyDataToUnstructuredGrid.cxx**
```c++
#include <vtkAppendFilter.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVersion.h>
#include <vtkXMLUnstructuredGridWriter.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();

  // Combine the two data sets
  vtkSmartPointer<vtkAppendFilter> appendFilter =
    vtkSmartPointer<vtkAppendFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  appendFilter->AddInput(sphereSource->GetOutput());
#else
  appendFilter->AddInputData(sphereSource->GetOutput());
#endif
  appendFilter->Update();

  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid =
     vtkSmartPointer<vtkUnstructuredGrid>::New();
  unstructuredGrid->ShallowCopy(appendFilter->GetOutput());

  // Write the unstructured grid
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName("UnstructuredGrid.vtu");
  #if VTK_MAJOR_VERSION <= 5
    writer->SetInput(unstructuredGrid);
  #else
    writer->SetInputData(unstructuredGrid);
  #endif
  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PolyDataToUnstructuredGrid)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PolyDataToUnstructuredGrid MACOSX_BUNDLE PolyDataToUnstructuredGrid.cxx)
 
target_link_libraries(PolyDataToUnstructuredGrid ${VTK_LIBRARIES})
```

**Download and Build PolyDataToUnstructuredGrid**

Click [here to download PolyDataToUnstructuredGrid](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PolyDataToUnstructuredGrid.tar) and its *CMakeLists.txt* file.
Once the *tarball PolyDataToUnstructuredGrid.tar* has been downloaded and extracted,
```
cd PolyDataToUnstructuredGrid/build 
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
./PolyDataToUnstructuredGrid
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

