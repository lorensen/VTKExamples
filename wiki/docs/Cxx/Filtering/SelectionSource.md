[VTKExamples](/index/)/[Cxx](/Cxx)/Filtering/SelectionSource

**SelectionSource.cxx**
```c++
#include <vtkPointSource.h>
#include <vtkExtractSelection.h>
#include <vtkPolyData.h>
#include <vtkSelectionNode.h> // for POINT and INDICES enum values
#include <vtkSelectionSource.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  // Note - this generates 50 points and a single poly-vertex cell.
  vtkSmartPointer<vtkPointSource> pointSource =
      vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(50);
  pointSource->Update();

  std::cout << "There are " << pointSource->GetOutput()->GetNumberOfPoints() << " input points." << std::endl;

  vtkSmartPointer<vtkSelectionSource> selectionSource =
      vtkSmartPointer<vtkSelectionSource>::New();
  selectionSource->SetFieldType(vtkSelectionNode::POINT);
  selectionSource->SetContentType(vtkSelectionNode::INDICES);

  // Without this line, all points are passed through because the 11 points
  // we will select below are some of the points of the poly-vertex created
  // by the PointSource, so the cell (by default) gets passed through since
  // it contains some selected points, so therefore all of the points
  // (the 50 belonging to the poly-vertex) also get passed through, which
  // is not what we are trying to demonstrate.
  selectionSource->SetContainingCells(false);

  for (vtkIdType i = 10; i <= 20; i++)
  {
    selectionSource->AddID(0, i);
  }

  selectionSource->Update();

  vtkSmartPointer<vtkExtractSelection> extractSelection =
      vtkSmartPointer<vtkExtractSelection>::New();
  extractSelection->SetInputConnection(0, pointSource->GetOutputPort());
  extractSelection->SetInputConnection(1, selectionSource->GetOutputPort());
  extractSelection->Update();

  vtkDataSet* ds = vtkDataSet::SafeDownCast (extractSelection->GetOutput());

  std::cout << "There are " << ds->GetNumberOfPoints() << " output points." << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SelectionSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SelectionSource MACOSX_BUNDLE SelectionSource.cxx)
 
target_link_libraries(SelectionSource ${VTK_LIBRARIES})
```

**Download and Build SelectionSource**

Click [here to download SelectionSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SelectionSource.tar) and its *CMakeLists.txt* file.
Once the *tarball SelectionSource.tar* has been downloaded and extracted,
```
cd SelectionSource/build 
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
./SelectionSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

