#include <vtkSmartPointer.h>
#include <vtkTableBasedClipDataSet.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPlane.h>
#include <vtkTransform.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellTypes.h>
#include <vtkDataSetMapper.h>
#include <vtkLookupTable.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <vtkNamedColors.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " filename.vtk" << std::endl;
    return EXIT_FAILURE;
  }
  // Create the reader for the data.
  std::string filename = argv[1];
  std::cout << "Loading " << filename.c_str() << std::endl;
  auto reader =
    vtkSmartPointer<vtkUnstructuredGridReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  double bounds[6];
  reader->GetOutput()->GetBounds(bounds);  
  double center[3];
  reader->GetOutput()->GetCenter(center);  

  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(colors->GetColor3d("Wheat").GetData());
  renderer->UseHiddenLineRemovalOn();

  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  auto interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  double xnorm[3] = {-1.0, -1.0, 1.0};

  auto clipPlane = vtkSmartPointer<vtkPlane>::New();
  clipPlane->SetOrigin(reader->GetOutput()->GetCenter());
  clipPlane->SetNormal(xnorm);

  auto clipper =
    vtkSmartPointer<vtkTableBasedClipDataSet>::New();
  clipper->SetClipFunction(clipPlane);
  clipper->SetInputData(reader->GetOutput());
  clipper->SetValue(0.0);
  clipper->GenerateClippedOutputOn();
  clipper->Update();

  auto insideMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  insideMapper->SetInputData(clipper->GetOutput());
  insideMapper->ScalarVisibilityOff();

  auto insideActor =
    vtkSmartPointer<vtkActor>::New();
  insideActor->SetMapper(insideMapper);
  insideActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("banana").GetData());
  insideActor->GetProperty()->SetAmbient(.3);
  insideActor->GetProperty()->EdgeVisibilityOn();

  auto clippedMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  clippedMapper->SetInputData(clipper->GetClippedOutput());
  clippedMapper->ScalarVisibilityOff();

  auto clippedActor =
    vtkSmartPointer<vtkActor>::New();
  clippedActor->SetMapper(clippedMapper);
  clippedActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("tomato").GetData());
  insideActor->GetProperty()->SetAmbient(.3);
  clippedActor->GetProperty()->EdgeVisibilityOn();

  // Create transforms to make a better visualization
  auto insideTransform = vtkSmartPointer<vtkTransform>::New();
  insideTransform->Translate(-(bounds[1] - bounds[0]) * .75, 0, 0);
  insideTransform->Translate(center[0], center[1], center[2]);
  insideTransform->RotateY(-120.0);
  insideTransform->Translate(-center[0], -center[1], -center[2]);
  insideActor->SetUserTransform(insideTransform);

  auto clippedTransform = vtkSmartPointer<vtkTransform>::New();
  clippedTransform->Translate((bounds[1] - bounds[0]) * .75, 0, 0);
  clippedTransform->Translate(center[0], center[1], center[2]);
  clippedTransform->RotateY(60.0);
  clippedTransform->Translate(-center[0], -center[1], -center[2]);
  clippedActor->SetUserTransform(clippedTransform);

  renderer->AddViewProp(clippedActor);
  renderer->AddViewProp(insideActor);

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Dolly(1.4);
  renderer->ResetCameraClippingRange();
  renderWindow->Render();
  
  interactor->Start();

  // Generate a report
  vtkIdType numberOfCells = clipper->GetOutput()->GetNumberOfCells();
  std::cout << "------------------------" << std::endl;
  std::cout << "The inside dataset contains a " << std::endl
            << clipper->GetOutput()->GetClassName()
            <<  " that has " << numberOfCells << " cells" << std::endl;
  typedef std::map<int,int> CellContainer;
  CellContainer cellMap;
  for (vtkIdType i = 0; i < numberOfCells; i++)
  {
    cellMap[clipper->GetOutput()->GetCellType(i)]++;
  }

  for (auto c : cellMap)
  {
    std::cout << "\tCell type "
              << vtkCellTypes::GetClassNameFromTypeId(c.first)
              << " occurs " << c.second << " times." << std::endl;
  }

  numberOfCells = clipper->GetClippedOutput()->GetNumberOfCells();
  std::cout << "------------------------" << std::endl;
  std::cout << "The clipped dataset contains a " << std::endl
            << clipper->GetClippedOutput()->GetClassName()
            <<  " that has " << numberOfCells << " cells" << std::endl;
  typedef std::map<int,int> OutsideCellContainer;
  CellContainer outsideCellMap;
  for (vtkIdType i = 0; i < numberOfCells; i++)
  {
    outsideCellMap[clipper->GetClippedOutput()->GetCellType(i)]++;
  }

  for (auto c : outsideCellMap)
  {
    std::cout << "\tCell type "
              << vtkCellTypes::GetClassNameFromTypeId(c.first)
              << " occurs " << c.second << " times." << std::endl;
  }
  return EXIT_SUCCESS;
}
