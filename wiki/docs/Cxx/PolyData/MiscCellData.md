[VTKExamples](Home)/[Cxx](Cxx)/PolyData/MiscCellData

### Description
This demo attaches a double to a cell (triangle) in a polydata.

**MiscCellData.cxx**
```c++
#include <vtkVersion.h>
#include <vtkCellData.h>
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkTriangle.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataWriter.h>

int main(int, char *[])
{
  // We will write the resulting file to Test.vtp so it can be inspected in Paraview
  std::string outputFilename = "output.vtp";

  // Setup 3 points
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);

  // Create a triangle
  vtkSmartPointer<vtkTriangle> triangle = 
    vtkSmartPointer<vtkTriangle>::New();
  triangle->GetPointIds()->SetId(0,0);
  triangle->GetPointIds()->SetId(1,1);
  triangle->GetPointIds()->SetId(2,2);
  
  // Add the triangle to a cell array
  vtkSmartPointer<vtkCellArray> triangles = 
    vtkSmartPointer<vtkCellArray>::New();
  triangles->InsertNextCell(triangle);

  // Setup data for the triangle. Attach a value of 1.45.
  // This can be anything you wish to store with it)
  vtkSmartPointer<vtkDoubleArray> triangleData = 
    vtkSmartPointer<vtkDoubleArray>::New();
  triangleData->SetNumberOfComponents(1); //we will have only 1 value associated with the triangle
  triangleData->SetName("TriangleData"); //set the name of the value
  triangleData->InsertNextValue(1.45); //set the actual value

  // Create a polydata that contains the points, 
  // the triangle on those points, and the data 
  // array (value) we created for the triangle
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetPolys(triangles);
  polydata->GetCellData()->AddArray(triangleData);

  // Write the file
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
#if VTK_MAJOR_VERSION <= 5
  writer->SetInput(polydata);
#else
  writer->SetInputData(polydata);
#endif
  writer->SetFileName(outputFilename.c_str());
  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MiscCellData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MiscCellData MACOSX_BUNDLE MiscCellData.cxx)
 
target_link_libraries(MiscCellData ${VTK_LIBRARIES})
```

**Download and Build MiscCellData**

Click [here to download MiscCellData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MiscCellData.tar) and its *CMakeLists.txt* file.
Once the *tarball MiscCellData.tar* has been downloaded and extracted,
```
cd MiscCellData/build 
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
./MiscCellData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

