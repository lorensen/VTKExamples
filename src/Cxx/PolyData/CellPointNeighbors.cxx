#include <vtkActor.h>
#include <vtkCell.h>
#include <vtkDataSetMapper.h>
#include <vtkExtractSelection.h>
#include <vtkIdList.h>
#include <vtkIdTypeArray.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSelection.h>
#include <vtkSelectionNode.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTriangleFilter.h>

#include <list>

int main(int, char*[])
{
  // Create a sphere
  auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  auto triangleFilter = vtkSmartPointer<vtkTriangleFilter>::New();
  triangleFilter->SetInputConnection(sphereSource->GetOutputPort());
  triangleFilter->Update();

  // Find all cells connected to point 0
  vtkIdType cellId = 0;

  auto cellPointIds = vtkSmartPointer<vtkIdList>::New();
  triangleFilter->GetOutput()->GetCellPoints(cellId, cellPointIds);

  // neighbor cells may be listed multiple times
  // use std::set instead of std::list if you want a unique list of neighbors
  std::list<vtkIdType> neighbors;

  /* For each vertex of the cell, we calculate which cells use that point.
   So if we do this for each vertex, we have all the neighbors.
   In the case of using "cellPointIds" as a parameter of "GetCellNeighbors",
   we will obtain an empty set. This is because the only cell that is using that
   set of points is the current one. That is why we have to make each vertice at
   time.*/

  for (vtkIdType i = 0; i < cellPointIds->GetNumberOfIds(); i++)
  {
    auto idList = vtkSmartPointer<vtkIdList>::New();
    idList->InsertNextId(cellPointIds->GetId(i));

    // get the neighbors of the cell
    auto neighborCellIds = vtkSmartPointer<vtkIdList>::New();

    triangleFilter->GetOutput()->GetCellNeighbors(cellId, idList,
                                                  neighborCellIds);

    for (vtkIdType j = 0; j < neighborCellIds->GetNumberOfIds(); j++)
    {
      neighbors.push_back(neighborCellIds->GetId(j));
    }
  }

  std::cout << "Point neighbor ids are: " << std::endl;

  for (auto it1 = neighbors.begin(); it1 != neighbors.end(); ++it1)
  {
    std::cout << " " << *it1;
  }
  std::cout << std::endl;

  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto sphereMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  sphereMapper->SetResolveCoincidentTopologyToPolygonOffset();

  auto sphereActor = vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetEdgeColor(
      colors->GetColor3d("Lamp_Black").GetData());
  sphereActor->GetProperty()->EdgeVisibilityOn();
  sphereActor->GetProperty()->SetLineWidth(3);

  auto mainCellMapper = vtkSmartPointer<vtkDataSetMapper>::New();

  auto neighborCellsMapper = vtkSmartPointer<vtkDataSetMapper>::New();

  // Create a dataset with the cell of interest
  {
    auto ids = vtkSmartPointer<vtkIdTypeArray>::New();
    ids->SetNumberOfComponents(1);
    ids->InsertNextValue(cellId);

    auto selectionNode = vtkSmartPointer<vtkSelectionNode>::New();
    selectionNode->SetFieldType(vtkSelectionNode::CELL);
    selectionNode->SetContentType(vtkSelectionNode::INDICES);
    selectionNode->SetSelectionList(ids);

    auto selection = vtkSmartPointer<vtkSelection>::New();
    selection->AddNode(selectionNode);

    auto extractSelection = vtkSmartPointer<vtkExtractSelection>::New();
    extractSelection->SetInputConnection(0, sphereSource->GetOutputPort());
    extractSelection->SetInputData(1, selection);
    extractSelection->Update();

    mainCellMapper->SetInputConnection(extractSelection->GetOutputPort());
  }

  auto mainCellActor = vtkSmartPointer<vtkActor>::New();
  mainCellActor->SetMapper(mainCellMapper);
  mainCellActor->GetProperty()->SetColor(
      colors->GetColor3d("Tomato").GetData());

  // Create a dataset with the neighbor cells
  {
    auto ids = vtkSmartPointer<vtkIdTypeArray>::New();
    ids->SetNumberOfComponents(1);
    for (auto it1 = neighbors.begin(); it1 != neighbors.end(); ++it1)
    {
      ids->InsertNextValue(*it1);
    }

    auto selectionNode = vtkSmartPointer<vtkSelectionNode>::New();
    selectionNode->SetFieldType(vtkSelectionNode::CELL);
    selectionNode->SetContentType(vtkSelectionNode::INDICES);
    selectionNode->SetSelectionList(ids);

    auto selection = vtkSmartPointer<vtkSelection>::New();
    selection->AddNode(selectionNode);

    auto extractSelection = vtkSmartPointer<vtkExtractSelection>::New();
    extractSelection->SetInputConnection(0, sphereSource->GetOutputPort());
    extractSelection->SetInputData(1, selection);
    extractSelection->Update();

    neighborCellsMapper->SetInputConnection(extractSelection->GetOutputPort());
  }

  auto neighborCellsActor = vtkSmartPointer<vtkActor>::New();
  neighborCellsActor->SetMapper(neighborCellsMapper);
  neighborCellsActor->GetProperty()->SetColor(
      colors->GetColor3d("Mint").GetData());

  // Create a renderer, render window, and interactor
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(sphereActor);
  renderer->AddActor(mainCellActor);
  renderer->AddActor(neighborCellsActor);
  renderer->SetBackground(colors->GetColor3d("Slate_grey").GetData());

  // Render and interact
  renderWindow->SetSize(640, 480);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
