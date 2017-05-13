[VTKExamples](Home)/[Cxx](Cxx)/PolyData/IterateOverLines

### Description
(If anyone can explain why the commented section doesn't work the same as the uncommented section, or fix it, that would be great.)

**IterateOverLines.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkLine.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>

int main(int, char *[])
{
  double origin[3] = {0.0, 0.0, 0.0};
  double p0[3] = {1.0, 0.0, 0.0};
  double p1[3] = {0.0, 1.0, 0.0};
  double p2[3] = {0.0, 1.0, 2.0};
  double p3[3] = {1.0, 2.0, 3.0};

  // Create a vtkPoints object and store the points in it
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(origin);
  points->InsertNextPoint(p0);
  points->InsertNextPoint(p1);
  points->InsertNextPoint(p2);
  points->InsertNextPoint(p3);

  // Create a cell array to store the lines in and add the lines to it
  vtkSmartPointer<vtkCellArray> lines =
    vtkSmartPointer<vtkCellArray>::New();

  //Create four lines
  for(unsigned int i = 0; i < 4; i++)
  {
    vtkSmartPointer<vtkLine> line =
      vtkSmartPointer<vtkLine>::New();
    line->GetPointIds()->SetId(0,i);
    line->GetPointIds()->SetId(1,i+1);
    lines->InsertNextCell(line);
  }

  // Create a polydata to store everything in
  vtkSmartPointer<vtkPolyData> linesPolyData =
    vtkSmartPointer<vtkPolyData>::New();

  // Add the points to the dataset
  linesPolyData->SetPoints(points);

  // Add the lines to the dataset
  linesPolyData->SetLines(lines);

  std::cout << "There are " << linesPolyData->GetNumberOfLines() << " lines." << std::endl;

  linesPolyData->GetLines()->InitTraversal();
  vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();
  while(linesPolyData->GetLines()->GetNextCell(idList))
  {
    std::cout << "Line has " << idList->GetNumberOfIds() << " points." << std::endl;

    for(vtkIdType pointId = 0; pointId < idList->GetNumberOfIds(); pointId++)
    {
      std::cout << idList->GetId(pointId) << " ";
    }
    std::cout << std::endl;
  }
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(IterateOverLines)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(IterateOverLines MACOSX_BUNDLE IterateOverLines.cxx)
 
target_link_libraries(IterateOverLines ${VTK_LIBRARIES})
```

**Download and Build IterateOverLines**

Click [here to download IterateOverLines](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/IterateOverLines.tar) and its *CMakeLists.txt* file.
Once the *tarball IterateOverLines.tar* has been downloaded and extracted,
```
cd IterateOverLines/build 
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
./IterateOverLines
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

