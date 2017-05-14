[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/DeleteCells

### Description
This example demonstrates how to delete a cell from a vtkPolyData. This is a three-step process: first, build upward-links from points to cells; second, mark cells for deletion; third, delete the marked cells. The first step is necessary to create a data structure suitable for efficient delete operations. Creating this data structure is computationally expensive, so it is only carried out before operations that need it, e.g. those that require changes to the topology.

**DeleteCells.cxx**
```c++
#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
 
int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);
  points->InsertNextPoint(1,1,0);
  points->InsertNextPoint(0,1,0);
 
  vtkSmartPointer<vtkLine> line0 = 
    vtkSmartPointer<vtkLine>::New();
  line0->GetPointIds()->SetId(0, 0);
  line0->GetPointIds()->SetId(1, 1);
 
  vtkSmartPointer<vtkLine> line1 = 
    vtkSmartPointer<vtkLine>::New();
  line1->GetPointIds()->SetId(0, 1);
  line1->GetPointIds()->SetId(1, 2);
 
  vtkSmartPointer<vtkLine> line2 = 
    vtkSmartPointer<vtkLine>::New();
  line2->GetPointIds()->SetId(0, 2);
  line2->GetPointIds()->SetId(1, 3);
 
  vtkSmartPointer<vtkCellArray> lines =
    vtkSmartPointer<vtkCellArray>::New();
  lines->InsertNextCell(line0);
  lines->InsertNextCell(line1);
  lines->InsertNextCell(line2);
 
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetLines(lines);

  // Tell the polydata to build 'upward' links from points to cells.
  polydata->BuildLinks();
  // Mark a cell as deleted.
  polydata->DeleteCell(1);
  // Remove the marked cell.
  polydata->RemoveDeletedCells();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputDataObject(polydata);
 
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(actor);
 
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DeleteCells)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DeleteCells MACOSX_BUNDLE DeleteCells.cxx)
 
target_link_libraries(DeleteCells ${VTK_LIBRARIES})
```

**Download and Build DeleteCells**

Click [here to download DeleteCells](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DeleteCells.tar) and its *CMakeLists.txt* file.
Once the *tarball DeleteCells.tar* has been downloaded and extracted,
```
cd DeleteCells/build 
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
./DeleteCells
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

