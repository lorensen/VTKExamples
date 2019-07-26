#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellData.h>
#include <vtkCellIterator.h>
#include <vtkConnectivityFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkFillHolesFilter.h>
#include <vtkGenericCell.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usgae: " << argv[0] << " file.vtp e.g. Torso.vtp"
              << std::endl;
    return EXIT_FAILURE;
  }
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  // Fill the holes
  auto fillHoles = vtkSmartPointer<vtkFillHolesFilter>::New();
  fillHoles->SetInputConnection(reader->GetOutputPort());
  fillHoles->SetHoleSize(1000.0);

  // Make the triangle winding order consistent
  auto normals = vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputConnection(fillHoles->GetOutputPort());
  normals->ConsistencyOn();
  normals->SplittingOff();
  normals->Update();
  normals->GetOutput()->GetPointData()->SetNormals(
      reader->GetOutput()->GetPointData()->GetNormals());

  // How many added cells
  vtkIdType numOriginalCells = reader->GetOutput()->GetNumberOfCells();
  vtkIdType numNewCells = normals->GetOutput()->GetNumberOfCells();

  // Iterate over the original cells
  auto it = normals->GetOutput()->NewCellIterator();
  vtkIdType numCells = 0;
  for (it->InitTraversal();
       !it->IsDoneWithTraversal() && numCells < numOriginalCells;
       it->GoToNextCell(), ++numCells)
  {
  }
  std::cout << "Num original: " << numOriginalCells
            << ", Num new: " << numNewCells
            << ", Num added: " << numNewCells - numOriginalCells << std::endl;
  auto holePolyData = vtkSmartPointer<vtkPolyData>::New();
  holePolyData->Allocate(normals->GetOutput(), numNewCells - numOriginalCells);
  holePolyData->SetPoints(normals->GetOutput()->GetPoints());

  auto cell = vtkSmartPointer<vtkGenericCell>::New();

  // The remaining cells are the new ones from the hole filler
  for (; !it->IsDoneWithTraversal(); it->GoToNextCell())
  {
    it->GetCell(cell);
    holePolyData->InsertNextCell(it->GetCellType(), cell->GetPointIds());
  }
  it->Delete();

  // We have to use ConnectivtyFilter and not
  // PolyDataConnectivityFilter since the later does not create
  // RegionIds cell data.
  auto connectivity = vtkSmartPointer<vtkConnectivityFilter>::New();
  connectivity->SetInputData(holePolyData);
  connectivity->SetExtractionModeToAllRegions();
  connectivity->ColorRegionsOn();
  connectivity->Update();
  std::cout << "Found " << connectivity->GetNumberOfExtractedRegions()
            << " holes" << std::endl;

  // Visualize

  // Create a mapper and actor for the fill polydata
  auto filledMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  filledMapper->SetInputConnection(connectivity->GetOutputPort());
  filledMapper->SetScalarModeToUseCellData();
  filledMapper->SetScalarRange(connectivity->GetOutput()
                                   ->GetCellData()
                                   ->GetArray("RegionId")
                                   ->GetRange());
  auto filledActor = vtkSmartPointer<vtkActor>::New();
  filledActor->SetMapper(filledMapper);
  filledActor->GetProperty()->SetDiffuseColor(
      colors->GetColor3d("Peacock").GetData());

  // Create a mapper and actor for the original polydata
  auto originalMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(reader->GetOutputPort());

  auto backfaceProp = vtkSmartPointer<vtkProperty>::New();
  backfaceProp->SetDiffuseColor(colors->GetColor3d("Banana").GetData());

  auto originalActor = vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->SetBackfaceProperty(backfaceProp);
  originalActor->GetProperty()->SetDiffuseColor(
      colors->GetColor3d("Flesh").GetData());
  originalActor->GetProperty()->SetRepresentationToWireframe();

  // Create a renderer, render window, and interactor
  auto renderer = vtkSmartPointer<vtkRenderer>::New();

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(512, 512);

  renderWindow->AddRenderer(renderer);

  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(originalActor);
  renderer->AddActor(filledActor);
  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());

  renderer->GetActiveCamera()->SetPosition(0, -1, 0);
  renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  renderer->GetActiveCamera()->SetViewUp(0, 0, 1);
  renderer->GetActiveCamera()->Azimuth(60);
  renderer->GetActiveCamera()->Elevation(30);

  renderer->ResetCamera();
  // Render and interact
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
