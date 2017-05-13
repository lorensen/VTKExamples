[VTKExamples](/index/)/[Cxx](/Cxx)/IO/WriteVTP

### Description
In this example, we add 10 points to a polygonal data (polydata) object and write the result to a VTP file.

**WriteVTP.cxx**
```c++
#include <vtkVersion.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

int main ( int, char *[] )
{
  // Create 10 points.
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  for ( unsigned int i = 0; i < 10; ++i )
  {
    points->InsertNextPoint ( i, i, i );
  }

  // Create a polydata object and add the points to it.
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Write the file
  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("test.vtp");
#if VTK_MAJOR_VERSION <= 5
  writer->SetInput(polydata);
#else
  writer->SetInputData(polydata);
#endif

  // Optional - set the mode. The default is binary.
  //writer->SetDataModeToBinary();
  //writer->SetDataModeToAscii();

  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(WriteVTP)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(WriteVTP MACOSX_BUNDLE WriteVTP.cxx)
 
target_link_libraries(WriteVTP ${VTK_LIBRARIES})
```

**Download and Build WriteVTP**

Click [here to download WriteVTP](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/WriteVTP.tar) and its *CMakeLists.txt* file.
Once the *tarball WriteVTP.tar* has been downloaded and extracted,
```
cd WriteVTP/build 
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
./WriteVTP
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

