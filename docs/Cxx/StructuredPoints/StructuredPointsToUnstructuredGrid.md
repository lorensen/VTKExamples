[VTKExamples](/index/)/[Cxx](/Cxx)/StructuredPoints/StructuredPointsToUnstructuredGrid

**StructuredPointsToUnstructuredGrid.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkStructuredPoints.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkUnstructuredGrid.h>

int main(int argc, char *argv[])
{
  // Create a structuredpoints
  vtkSmartPointer<vtkStructuredPoints> structuredPoints =
    vtkSmartPointer<vtkStructuredPoints>::New();

  // Specify the size of the image data
  structuredPoints->SetDimensions(2,3,1);
  structuredPoints->SetNumberOfScalarComponents(1);
  structuredPoints->SetScalarTypeToDouble();

  int* dims = structuredPoints->GetDimensions();

  std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << std::endl;

  std::cout << "Number of points: " << structuredPoints->GetNumberOfPoints() << std::endl;
  std::cout << "Number of cells: " << structuredPoints->GetNumberOfCells() << std::endl;

  //fill every entry of the image data with "2.0"
  for (int z = 0; z < dims[2]; z++)
  {
    for (int y = 0; y < dims[1]; y++)
    {
      for (int x = 0; x < dims[0]; x++)
      {
        double* pixel = static_cast<double*>(structuredPoints->GetScalarPointer(x,y,z));
        pixel[0] = 2.0;
      }
    }
  }


  // Copy the points from the StructuredPoints to the UnstructuredGrid
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  //retrieve the entries from the grid and print them to the screen
  unsigned int counter = 0;
  for(vtkIdType i = 0; i < structuredPoints->GetNumberOfPoints(); i++)
  {
    double p[3];
    structuredPoints->GetPoint(i, p);

    points->InsertNextPoint(p);
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);

  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName("output.vtu");
  writer->SetInput(ug);
  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(StructuredPointsToUnstructuredGrid)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(StructuredPointsToUnstructuredGrid MACOSX_BUNDLE StructuredPointsToUnstructuredGrid.cxx)
 
target_link_libraries(StructuredPointsToUnstructuredGrid ${VTK_LIBRARIES})
```

**Download and Build StructuredPointsToUnstructuredGrid**

Click [here to download StructuredPointsToUnstructuredGrid](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/StructuredPointsToUnstructuredGrid.tar) and its *CMakeLists.txt* file.
Once the *tarball StructuredPointsToUnstructuredGrid.tar* has been downloaded and extracted,
```
cd StructuredPointsToUnstructuredGrid/build 
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
./StructuredPointsToUnstructuredGrid
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

