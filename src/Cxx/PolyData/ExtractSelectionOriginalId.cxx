#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkIdTypeArray.h>
#include <vtkInformation.h>
#include <vtkPointSource.h>
#include <vtkExtractSelection.h>
#include <vtkSelection.h>
#include <vtkSelectionNode.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkIdTypeArray.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkVertexGlyphFilter.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(50);
  pointSource->Update();

  std::cout << "There are " << pointSource->GetOutput()->GetNumberOfPoints()
            << " input points." << std::endl;

  vtkSmartPointer<vtkIdTypeArray> ids =
    vtkSmartPointer<vtkIdTypeArray>::New();
  ids->SetNumberOfComponents(1);

  //set values
  for(unsigned int i = 10; i < 20; i++)
  {
    ids->InsertNextValue(i);
  }

  vtkSmartPointer<vtkSelectionNode> selectionNode =
      vtkSmartPointer<vtkSelectionNode>::New();
  selectionNode->SetFieldType(vtkSelectionNode::POINT);
  selectionNode->SetContentType(vtkSelectionNode::INDICES);
  selectionNode->SetSelectionList(ids);

  vtkSmartPointer<vtkSelection> selection =
      vtkSmartPointer<vtkSelection>::New();
  selection->AddNode(selectionNode);

  vtkSmartPointer<vtkExtractSelection> extractSelection =
      vtkSmartPointer<vtkExtractSelection>::New();

  extractSelection->SetInputConnection(0, pointSource->GetOutputPort());
  extractSelection->SetInputData(1, selection);
  extractSelection->Update();

  //in selection
  vtkSmartPointer<vtkUnstructuredGrid> selected =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  selected->ShallowCopy(extractSelection->GetOutput());

  std::cout << "There are " << selected->GetNumberOfPoints()
            << " points in the selection." << std::endl;

  selected->Print(std::cout);

  vtkIdTypeArray* originalIds = dynamic_cast<vtkIdTypeArray*>(selected->GetPointData()->GetArray("vtkOriginalPointIds"));

  for(vtkIdType i = 0; i < originalIds->GetNumberOfTuples(); i++)
  {
    std::cout << "Point " << i << " was originally point " << originalIds->GetValue(i) << std::endl;
  }

  for(vtkIdType i = 0; i < originalIds->GetNumberOfTuples(); i++)
  {
    vtkIdType query = originalIds->GetValue(i);
    for(vtkIdType j = 0; j < originalIds->GetNumberOfTuples(); j++)
    {
      if(originalIds->GetValue(j) == query)
      {
        std::cout << "Original point " << query << " is now " << j << std::endl;
      }
    }
  }

  vtkSmartPointer<vtkDataSetMapper> inputMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  inputMapper->SetInputConnection(pointSource->GetOutputPort());
  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->SetMapper(inputMapper);

  vtkSmartPointer<vtkDataSetMapper> selectedMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  selectedMapper->SetInputData(selected);

  vtkSmartPointer<vtkActor> selectedActor =
    vtkSmartPointer<vtkActor>::New();
  selectedActor->SetMapper(selectedMapper);

  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(900, 300);

  // And one interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup the renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  leftRenderer->AddActor(inputActor);
  rightRenderer->AddActor(selectedActor);

  leftRenderer->ResetCamera();
  rightRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
