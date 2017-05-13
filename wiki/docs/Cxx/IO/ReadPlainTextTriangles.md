[VTKExamples](/home/)/[Cxx](/Cxx)/IO/ReadPlainTextTriangles

### Description

Here is an example of a custom file-format reader that produces a VTK XML PolyData file from a plain-text input format.  

#### Input Format
```
number_of_points
number_of_triangles
point[point[0]Y point[0](0]X)Z
point[point[1]Y point[1](1]X)Z
...
point[point[N]Y point[N](N]X)Z
triangle[triangle[0]B triangle[0](0]A)C
triangle[triangle[1]B triangle[1](1]A)C
...
triangle[triangle[M]B triangle[M](M]A)C
```

#### Example Input

```
3
1
0.0 0.0 0.0
0.0 0.0 1.0
0.0 1.0 0.0
0 1 2
```

**ReadPlainTextTriangles.cxx**
```c++
#include "vtkVersion.h"
#include "vtkSmartPointer.h"
#include "vtkPolyData.h"
#include "vtkPoints.h"
#include "vtkCellArray.h"
#include "vtkXMLPolyDataWriter.h"
#include <iostream>

vtkPolyData * custom_reader(std::istream & infile)
{
  vtkIdType number_of_points, number_of_triangles;
  infile >> number_of_points >> number_of_triangles;

  vtkSmartPointer<vtkPoints> points
    = vtkSmartPointer<vtkPoints>::New();
  points->SetNumberOfPoints(number_of_points);
  for (vtkIdType i = 0; i < number_of_points; i++)
  {
    double x, y, z;
    infile >> x >> y >> z;
    points->SetPoint(i, x, y, z);
  }

  vtkSmartPointer<vtkCellArray> polys
    = vtkSmartPointer<vtkCellArray>::New();
  for (vtkIdType i = 0; i < number_of_triangles; i++)
  {
    vtkIdType a, b, c;
    infile >> a >> b >> c;
    polys->InsertNextCell(3);
    polys->InsertCellPoint(a);
    polys->InsertCellPoint(b);
    polys->InsertCellPoint(c);
  }
  vtkPolyData * polydata = vtkPolyData::New();
  polydata->SetPoints(points);
  polydata->SetPolys(polys);
  return polydata;
}

int main(int argc, char * argv[])
{
  // Verify command line arguments
  if(argc != 2)
  {
    std::cerr << "Required arguments: triangleFile.txt" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  std::ifstream fin(inputFilename.c_str());

  vtkSmartPointer<vtkPolyData> polydata
    = vtkSmartPointer<vtkPolyData>::Take(
      custom_reader(fin));

  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
#if VTK_MAJOR_VERSION <= 5
  writer->SetInput(polydata);
#else
  writer->SetInputData(polydata);
#endif
  writer->SetFileName("x.vtp");
  writer->Write();
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ReadPlainTextTriangles)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadPlainTextTriangles MACOSX_BUNDLE ReadPlainTextTriangles.cxx)
 
target_link_libraries(ReadPlainTextTriangles ${VTK_LIBRARIES})
```

**Download and Build ReadPlainTextTriangles**

Click [here to download ReadPlainTextTriangles](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ReadPlainTextTriangles.tar) and its *CMakeLists.txt* file.
Once the *tarball ReadPlainTextTriangles.tar* has been downloaded and extracted,
```
cd ReadPlainTextTriangles/build 
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
./ReadPlainTextTriangles
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

