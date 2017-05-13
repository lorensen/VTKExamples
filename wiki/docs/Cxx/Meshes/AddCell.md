[VTKExamples](/home/)/[Cxx](/Cxx)/Meshes/AddCell

**AddCell.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>

int main(int , char *[])
{
  // Create a triangle
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint ( 1.0, 0.0, 0.0 );
  points->InsertNextPoint ( 0.0, 0.0, 0.0 );
  points->InsertNextPoint ( 0.0, 1.0, 0.0 );

  vtkSmartPointer<vtkTriangle> triangle =
    vtkSmartPointer<vtkTriangle>::New();
  triangle->GetPointIds()->SetId ( 0, 0 );
  triangle->GetPointIds()->SetId ( 1, 1 );
  triangle->GetPointIds()->SetId ( 2, 2 );

  vtkSmartPointer<vtkCellArray> triangles =
    vtkSmartPointer<vtkCellArray>::New();
  triangles->InsertNextCell ( triangle );

  // Create a polydata object
  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();

  // Add the geometry and topology to the polydata
  polyData->SetPoints ( points );
  polyData->SetPolys ( triangles );

  std::cout << "There are " << polyData->GetNumberOfCells() << " cells." << std::endl;

  polyData->GetPolys()->InsertNextCell(triangle);

  std::cout << "There are " << polyData->GetNumberOfCells() << " cells." << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(AddCell)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(AddCell MACOSX_BUNDLE AddCell.cxx)
 
target_link_libraries(AddCell ${VTK_LIBRARIES})
```

**Download and Build AddCell**

Click [here to download AddCell](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/AddCell.tar) and its *CMakeLists.txt* file.
Once the *tarball AddCell.tar* has been downloaded and extracted,
```
cd AddCell/build 
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
./AddCell
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

