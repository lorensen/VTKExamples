[VTKExamples](Home)/[Cxx](Cxx)/PolyData/CellPointNeighbors

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/PolyData/TestCellPointNeighbors.png" width="256" />

### Description
Determine which cells share at least a single point with a specified cell.

**CellPointNeighbors.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkIdList.h>
#include <vtkCell.h>
#include <vtkTriangleFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkIdTypeArray.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkProperty.h>

#include <list>

int main(int, char *[])
{
  //Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkTriangleFilter> triangleFilter =
    vtkSmartPointer<vtkTriangleFilter>::New();
  triangleFilter->SetInputConnection(sphereSource->GetOutputPort());
  triangleFilter->Update();

  // Find all cells connected to point 0
  vtkIdType cellId = 0;

  vtkSmartPointer<vtkIdList> cellPointIds =
    vtkSmartPointer<vtkIdList>::New();
  triangleFilter->GetOutput()->GetCellPoints(cellId, cellPointIds);

  // neighbor cells may be listed multiple times
  // use std::set instead of std::list if you want a unique list of neighbors
  std::list<vtkIdType> neighbors;

  /*For each vertice of the cell, we calculate which cells uses that point.
   So if we make this, for each vertice, we have all the neighbors.
   In the case we use ''cellPointIds'' as a parameter of ''GeteCellNeighbors'',
   we will obtain an empty set. Because the only cell that is using that set of points
   is the current one. That is why we have to make each vertice at time.*/

  for(vtkIdType i = 0; i < cellPointIds->GetNumberOfIds(); i++)
  {
    vtkSmartPointer<vtkIdList> idList =
      vtkSmartPointer<vtkIdList>::New();
    idList->InsertNextId(cellPointIds->GetId(i));

    //get the neighbors of the cell
    vtkSmartPointer<vtkIdList> neighborCellIds =
      vtkSmartPointer<vtkIdList>::New();

    triangleFilter->GetOutput()->GetCellNeighbors(cellId, idList, neighborCellIds);

    for(vtkIdType j = 0; j < neighborCellIds->GetNumberOfIds(); j++)
    {
      neighbors.push_back(neighborCellIds->GetId(j));
    }

  }

  std::cout << "Point neighbor ids are: " << std::endl;

  for(std::list<vtkIdType>::iterator it1 = neighbors.begin(); it1 != neighbors.end(); it1++)
  {
    std::cout << " " << *it1;
  }
  std::cout << std::endl;


  vtkSmartPointer<vtkDataSetMapper> sphereMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetEdgeColor(0, 0, 0);
  sphereActor->GetProperty()->EdgeVisibilityOn();

  vtkSmartPointer<vtkDataSetMapper> mainCellMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();

  vtkSmartPointer<vtkDataSetMapper> neighborCellsMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();

  // Create a dataset with the cell of interest
  {
    vtkSmartPointer<vtkIdTypeArray> ids =
        vtkSmartPointer<vtkIdTypeArray>::New();
    ids->SetNumberOfComponents(1);
    ids->InsertNextValue(cellId);

    vtkSmartPointer<vtkSelectionNode> selectionNode =
      vtkSmartPointer<vtkSelectionNode>::New();
    selectionNode->SetFieldType(vtkSelectionNode::CELL);
    selectionNode->SetContentType(vtkSelectionNode::INDICES);
    selectionNode->SetSelectionList(ids);

    vtkSmartPointer<vtkSelection> selection =
        vtkSmartPointer<vtkSelection>::New();
    selection->AddNode(selectionNode);

    vtkSmartPointer<vtkExtractSelection> extractSelection =
        vtkSmartPointer<vtkExtractSelection>::New();
    extractSelection->SetInputConnection(0, sphereSource->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
    extractSelection->SetInput(1, selection);
#else
    extractSelection->SetInputData(1, selection);
#endif
    extractSelection->Update();

    mainCellMapper->SetInputConnection(extractSelection->GetOutputPort());

  }

  vtkSmartPointer<vtkActor> mainCellActor =
    vtkSmartPointer<vtkActor>::New();
  mainCellActor->SetMapper(mainCellMapper);
  mainCellActor->GetProperty()->SetColor(1,0,0);

  // Create a dataset with the neighbor cells
  {
    vtkSmartPointer<vtkIdTypeArray> ids =
        vtkSmartPointer<vtkIdTypeArray>::New();
    ids->SetNumberOfComponents(1);
    for(std::list<vtkIdType>::iterator it1 = neighbors.begin(); it1 != neighbors.end(); it1++)
    {
      ids->InsertNextValue(*it1);
    }

    vtkSmartPointer<vtkSelectionNode> selectionNode =
      vtkSmartPointer<vtkSelectionNode>::New();
    selectionNode->SetFieldType(vtkSelectionNode::CELL);
    selectionNode->SetContentType(vtkSelectionNode::INDICES);
    selectionNode->SetSelectionList(ids);

    vtkSmartPointer<vtkSelection> selection =
        vtkSmartPointer<vtkSelection>::New();
    selection->AddNode(selectionNode);

    vtkSmartPointer<vtkExtractSelection> extractSelection =
        vtkSmartPointer<vtkExtractSelection>::New();
    extractSelection->SetInputConnection(0, sphereSource->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
    extractSelection->SetInput(1, selection);
#else
    extractSelection->SetInputData(1, selection);
#endif
    extractSelection->Update();

    neighborCellsMapper->SetInputConnection(extractSelection->GetOutputPort());

  }

  vtkSmartPointer<vtkActor> neighborCellsActor =
    vtkSmartPointer<vtkActor>::New();
  neighborCellsActor->SetMapper(neighborCellsMapper);
  neighborCellsActor->GetProperty()->SetColor(0,1,0);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actors to the scene
  renderer->AddActor(sphereActor);
  renderer->AddActor(mainCellActor);
  renderer->AddActor(neighborCellsActor);
  renderer->SetBackground(.3, .2, .1); // Background color dark red

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CellPointNeighbors)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CellPointNeighbors MACOSX_BUNDLE CellPointNeighbors.cxx)
 
target_link_libraries(CellPointNeighbors ${VTK_LIBRARIES})
```

**Download and Build CellPointNeighbors**

Click [here to download CellPointNeighbors](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CellPointNeighbors.tar) and its *CMakeLists.txt* file.
Once the *tarball CellPointNeighbors.tar* has been downloaded and extracted,
```
cd CellPointNeighbors/build 
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
./CellPointNeighbors
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

