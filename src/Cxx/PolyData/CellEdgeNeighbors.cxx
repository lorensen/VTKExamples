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

#include <vtkNamedColors.h>

#include <list>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkTriangleFilter> triangleFilter =
    vtkSmartPointer<vtkTriangleFilter>::New();
  triangleFilter->SetInputConnection(sphereSource->GetOutputPort());
  triangleFilter->Update();

  vtkIdType cellId = 0;

  vtkSmartPointer<vtkIdList> cellPointIds =
    vtkSmartPointer<vtkIdList>::New();
  triangleFilter->GetOutput()->GetCellPoints(cellId, cellPointIds);

  std::list<vtkIdType> neighbors;

  for(vtkIdType i = 0; i < cellPointIds->GetNumberOfIds(); i++)
  {
    vtkSmartPointer<vtkIdList> idList =
      vtkSmartPointer<vtkIdList>::New();

    //add one of the edge points
    idList->InsertNextId(cellPointIds->GetId(i));

    //add the other edge point
    if(i+1 == cellPointIds->GetNumberOfIds())
    {
      idList->InsertNextId(cellPointIds->GetId(0));
    }
    else
    {
      idList->InsertNextId(cellPointIds->GetId(i+1));
    }

    //get the neighbors of the cell
    vtkSmartPointer<vtkIdList> neighborCellIds =
      vtkSmartPointer<vtkIdList>::New();

    triangleFilter->GetOutput()->GetCellNeighbors(cellId, idList, neighborCellIds);

    for(vtkIdType j = 0; j < neighborCellIds->GetNumberOfIds(); j++)
    {
      neighbors.push_back(neighborCellIds->GetId(j));
    }

  }

  std::cout << "Edge neighbor ids are: " << std::endl;

  for(std::list<vtkIdType>::iterator it1 = neighbors.begin(); it1 != neighbors.end(); it1++)
  {
    std::cout << " " << *it1;
  }
  std::cout << std::endl;

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkDataSetMapper> sphereMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  sphereMapper->SetResolveCoincidentTopologyToPolygonOffset();

  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetEdgeColor(colors->GetColor3d("Lamp_Black").GetData());
  sphereActor->GetProperty()->EdgeVisibilityOn();
  sphereActor->GetProperty()->SetLineWidth(5);

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
    extractSelection->SetInputData(1, selection);
    extractSelection->Update();

    mainCellMapper->SetInputConnection(extractSelection->GetOutputPort());

  }

  vtkSmartPointer<vtkActor> mainCellActor =
    vtkSmartPointer<vtkActor>::New();
  mainCellActor->SetMapper(mainCellMapper);
  mainCellActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

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
    extractSelection->SetInputData(1, selection);
    extractSelection->Update();

    neighborCellsMapper->SetInputConnection(extractSelection->GetOutputPort());

  }

  vtkSmartPointer<vtkActor> neighborCellsActor =
    vtkSmartPointer<vtkActor>::New();
  neighborCellsActor->SetMapper(neighborCellsMapper);
  neighborCellsActor->GetProperty()->SetColor(colors->GetColor3d("Mint").GetData());

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
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
