[VTKExamples](/index/)/[Cxx](/Cxx)/IO/XMLStructuredGridWriter

**XMLStructuredGridWriter.cxx**
```c++
#include <vtkVersion.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkStructuredGrid.h>
#include <vtkSmartPointer.h>

int main ( int, char *[] )
{
   // Create a grid
  vtkSmartPointer<vtkStructuredGrid> structuredGrid =
    vtkSmartPointer<vtkStructuredGrid>::New();

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(1, 0, 0);
  points->InsertNextPoint(0, 1, 0);
  points->InsertNextPoint(1, 1, 0);
  points->InsertNextPoint(0, 2, 0);
  points->InsertNextPoint(1, 2, 1);
  
  // Specify the dimensions of the grid
  structuredGrid->SetDimensions(2,3,1);
  structuredGrid->SetPoints(points);
  
  // Write file
  vtkSmartPointer<vtkXMLStructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLStructuredGridWriter>::New();
  writer->SetFileName("output.vts");
#if VTK_MAJOR_VERSION <= 5
  writer->SetInput(structuredGrid);
#else
  writer->SetInputData(structuredGrid);
#endif
  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(XMLStructuredGridWriter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(XMLStructuredGridWriter MACOSX_BUNDLE XMLStructuredGridWriter.cxx)
 
target_link_libraries(XMLStructuredGridWriter ${VTK_LIBRARIES})
```

**Download and Build XMLStructuredGridWriter**

Click [here to download XMLStructuredGridWriter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/XMLStructuredGridWriter.tar) and its *CMakeLists.txt* file.
Once the *tarball XMLStructuredGridWriter.tar* has been downloaded and extracted,
```
cd XMLStructuredGridWriter/build 
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
./XMLStructuredGridWriter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

