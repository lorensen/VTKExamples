#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkExtractSelection.h>
#include <vtkIdTypeArray.h>
#include <vtkInformation.h>
#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSelection.h>
#include <vtkSelectionNode.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(50);
  pointSource->Update();

  std::cout << "There are " << pointSource->GetOutput()->GetNumberOfPoints()
            << " input points." << std::endl;

  vtkSmartPointer<vtkIdTypeArray> ids1 =
    vtkSmartPointer<vtkIdTypeArray>::New();
  ids1->SetNumberOfComponents(1);

  // Set values
  for(unsigned int i = 10; i < 20; i++)
  {
    ids1->InsertNextValue(i);
  }

  vtkSmartPointer<vtkIdTypeArray> ids2 =
    vtkSmartPointer<vtkIdTypeArray>::New();
  ids2->SetNumberOfComponents(1);

  for(unsigned int i = 15; i < 30; i++)
  {
    ids2->InsertNextValue(i);
  }

  vtkSmartPointer<vtkSelectionNode> selectionNode1 =
    vtkSmartPointer<vtkSelectionNode>::New();
  selectionNode1->SetFieldType(vtkSelectionNode::POINT);
  selectionNode1->SetContentType(vtkSelectionNode::INDICES);
  selectionNode1->SetSelectionList(ids1);

  vtkSmartPointer<vtkSelectionNode> selectionNode2 =
    vtkSmartPointer<vtkSelectionNode>::New();
  selectionNode2->SetFieldType(vtkSelectionNode::POINT);
  selectionNode2->SetContentType(vtkSelectionNode::INDICES);
  selectionNode2->SetSelectionList(ids2);

  vtkSmartPointer<vtkSelection> selection1 =
    vtkSmartPointer<vtkSelection>::New();
  selection1->AddNode(selectionNode1);

  vtkSmartPointer<vtkSelection> selection2 =
    vtkSmartPointer<vtkSelection>::New();
  selection2->AddNode(selectionNode2);

  vtkSmartPointer<vtkSelection> selectionCombined =
    vtkSmartPointer<vtkSelection>::New();
  selectionCombined->AddNode(selectionNode1);
  selectionCombined->Union(selectionNode2);

  std::cout << "There are " << selectionCombined->GetNumberOfNodes() << " nodes." << std::endl;

  vtkSmartPointer<vtkExtractSelection> extractSelection1 =
    vtkSmartPointer<vtkExtractSelection>::New();
  extractSelection1->SetInputConnection(0, pointSource->GetOutputPort());
  extractSelection1->SetInputData(1, selection1);
  extractSelection1->Update();

  vtkSmartPointer<vtkExtractSelection> extractSelection2 =
    vtkSmartPointer<vtkExtractSelection>::New();
  extractSelection2->SetInputConnection(0, pointSource->GetOutputPort());
  extractSelection2->SetInputData(1, selection2);
  extractSelection2->Update();

  vtkSmartPointer<vtkExtractSelection> extractSelectionCombined =
    vtkSmartPointer<vtkExtractSelection>::New();
  extractSelectionCombined->SetInputConnection(0, pointSource->GetOutputPort());
  extractSelectionCombined->SetInputData(1, selectionCombined);
  extractSelectionCombined->Update();

  // In selection
  vtkDataSet* ds = dynamic_cast<vtkDataSet*>(extractSelectionCombined->GetOutput());
  std::cout << "There are " << ds->GetNumberOfPoints() << " points in the selection." << std::endl;
  std::cout << "There are " << ds->GetNumberOfCells() << " cells in the selection." << std::endl;

  /*
  // Not in selection
  selectionNode1->GetProperties()->Set(vtkSelectionNode::INVERSE(), 1); //invert the selection
  selectionNode2->GetProperties()->Set(vtkSelectionNode::INVERSE(), 1); //invert the selection
  extractSelection->Update();
  std::cout << "There are " << dynamic_cast<vtkDataSet*> (extractSelection->GetOutput())->GetNumberOfPoints()
            << " points not in the selection." << std::endl;
  */

  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapperOriginal =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapperOriginal->SetInputConnection(pointSource->GetOutputPort());
  mapperOriginal->ScalarVisibilityOff();

  vtkSmartPointer<vtkDataSetMapper> mapper1 =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper1->SetInputConnection(extractSelection1->GetOutputPort());
  mapper1->ScalarVisibilityOff();

  vtkSmartPointer<vtkDataSetMapper> mapper2 =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper2->SetInputConnection(extractSelection2->GetOutputPort());
  mapper2->ScalarVisibilityOff();

  vtkSmartPointer<vtkDataSetMapper> mapperCombined =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapperCombined->SetInputConnection(extractSelectionCombined->GetOutputPort());
  mapperCombined->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(mapperOriginal);

  vtkSmartPointer<vtkActor> actor1 =
    vtkSmartPointer<vtkActor>::New();
  actor1->SetMapper(mapper1);

  vtkSmartPointer<vtkActor> actor2 =
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(mapper2);

  vtkSmartPointer<vtkActor> actorCombined =
    vtkSmartPointer<vtkActor>::New();
  actorCombined->SetMapper(mapperCombined);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(1000,250);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  double originalViewport[4] = {0.0, 0.0, 0.25, 1.0};
  double selection1Viewport[4] = {0.25, 0.0, 0.5, 1.0};
  double selection2Viewport[4] = {0.5, 0.0, 0.75, 1.0};
  double selectionCombinedViewport[4] = {0.75, 0.0, 1.0, 1.0};

  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);

  vtkSmartPointer<vtkRenderer> selection1Renderer =
    vtkSmartPointer<vtkRenderer>::New();
  selection1Renderer->SetViewport(selection1Viewport);

  vtkSmartPointer<vtkRenderer> selection2Renderer =
    vtkSmartPointer<vtkRenderer>::New();
  selection2Renderer->SetViewport(selection2Viewport);

  vtkSmartPointer<vtkRenderer> selectionCombinedRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  selectionCombinedRenderer->SetViewport(selectionCombinedViewport);

  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(selection1Renderer);
  renderWindow->AddRenderer(selection2Renderer);
  renderWindow->AddRenderer(selectionCombinedRenderer);

  originalRenderer->AddActor(originalActor);
  selection1Renderer->AddActor(actor1);
  selection2Renderer->AddActor(actor2);
  selectionCombinedRenderer->AddActor(actorCombined);
  //renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();

  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
