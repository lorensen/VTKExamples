#include <vtkSmartPointer.h>
#include <vtkConnectivityFilter.h>

#include <vtkSphereSource.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>
#include <vtkCellLocator.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkUnstructuredGrid.h>
#include <vtkIdTypeArray.h>
#include <vtkCellIterator.h>
#include <vtkGenericCell.h>
#include <vtkCellData.h>

#include <vtkNamedColors.h>
#include <vtkMath.h>

int main(int argc, char *argv[])
{
  // PolyData to process
  vtkSmartPointer<vtkPolyData> polyData;

  if (argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    vtkMath::RandomSeed(5070); // for testing
    vtkSmartPointer<vtkAppendPolyData> appendFilter =
      vtkSmartPointer<vtkAppendPolyData>::New();

    for (int i = 0; i < 20; ++i)
    {
      // Small spheres with most polgons
      vtkSmartPointer<vtkSphereSource> sphereSource1 =
        vtkSmartPointer<vtkSphereSource>::New();
      sphereSource1->SetThetaResolution(10);
      sphereSource1->SetPhiResolution(10);
      sphereSource1->SetCenter(vtkMath::Random(4.0, 14.0), vtkMath::Random(-3.0, 5.0), vtkMath::Random(4.0, 14.0));
      sphereSource1->SetRadius(1.0);
      appendFilter->AddInputConnection(sphereSource1->GetOutputPort());
    }

    // Large sphere with least polygons
    vtkSmartPointer<vtkSphereSource> sphereSource2 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource2->SetRadius(10);
    sphereSource2->SetCenter(10,1,10);

    appendFilter->AddInputConnection(sphereSource2->GetOutputPort());
    appendFilter->Update();
    polyData = appendFilter->GetOutput();
  }

  double center[3], bounds[6];
  polyData->GetCenter(center);
  std::cout << "Center of data: "
            << center[0] << ", "
            << center[1] << ", "
            << center[2] << std::endl;
  polyData->GetPoints()->GetBounds(bounds);
  std::cout << "Bounds of data: "
            << bounds[0] << ", "
            << bounds[1] << ", "
            << bounds[2] << ", "
            << bounds[3] << ", "
            << bounds[4] << ", "
            << bounds[5] << std::endl;

  // Extract all regions and label cells with region number
  vtkSmartPointer<vtkConnectivityFilter> connectivityFilter =
      vtkSmartPointer<vtkConnectivityFilter>::New();
  connectivityFilter->SetInputData(polyData);
  connectivityFilter->SetExtractionModeToAllRegions();
  connectivityFilter->ColorRegionsOn();
  connectivityFilter->Update();

  // Build a cell locator.
  vtkSmartPointer<vtkCellLocator> cellLocator =
    vtkSmartPointer<vtkCellLocator>::New();
  cellLocator->SetDataSet(connectivityFilter->GetOutput());
  cellLocator->BuildLocator();

  // Now fire a ray from outside the bounds to the center and find a
  // cell. This cell should be on the outside surface
  double rayStart[3];
  for (unsigned int i = 0; i < 3; i++)
  {
    rayStart[i] = bounds[2 * i + 1] * 1.1;
  }

  vtkIdType cellId = -1;
  double xyz[3], t, pcoords[3];
  int subId;

  cellLocator->IntersectWithLine(
    rayStart,
    center,
    0.0001,
    t,
    xyz,
    pcoords,
    subId,
    cellId);

  vtkIdTypeArray *cd =
    dynamic_cast<vtkIdTypeArray*>(connectivityFilter->GetOutput()->GetCellData()->GetScalars());
  vtkIdType outsideRegionId = cd->GetTuple1(cellId);
  std::cout << "Id of cell on outside surface: " << cellId << std::endl;
  std::cout << "CellData at " << cellId << ": " << outsideRegionId << std::endl;

  // Build a polydata from cells that are not in the outside surface
  // Iterate over the original cells
  vtkSmartPointer<vtkPolyData> insidePolyData =
    vtkSmartPointer<vtkPolyData>::New();
  insidePolyData->Allocate();
  insidePolyData->SetPoints(connectivityFilter->GetOutput()->GetPoints());

  vtkSmartPointer<vtkGenericCell> cell =
    vtkSmartPointer<vtkGenericCell>::New();
  auto it = connectivityFilter->GetOutput()->NewCellIterator();
  vtkIdType originalCellId = 0;
  for (it->InitTraversal();
       !it->IsDoneWithTraversal();
       it->GoToNextCell(), ++originalCellId)
  {
    //  Retain cell if it is NOT an outside cell
    if (cd->GetTuple1(originalCellId) != outsideRegionId)
    {
      it->GetCell(cell);
      insidePolyData->InsertNextCell(it->GetCellType(), cell->GetPointIds());
    }
  }
  it->Delete();

  // Create a mapper and actor for original data
  vtkSmartPointer<vtkPolyDataMapper> originalMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputData(polyData);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkActor> originalActor =
      vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->BackfaceCullingOn();
  originalActor->GetProperty()->SetOpacity(.5);;
  originalActor->GetProperty()->SetColor(colors->GetColor3d("Gold").GetData());

  // Create a mapper and actor for extracted data
  vtkSmartPointer<vtkPolyDataMapper> extractedMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  extractedMapper->SetInputData(insidePolyData);

  vtkSmartPointer<vtkActor> extractedActor =
      vtkSmartPointer<vtkActor>::New();
  extractedActor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());
  extractedActor->SetMapper(extractedMapper);
  extractedActor->GetProperty()->SetOpacity(.5);;
  extractedActor->GetProperty()->BackfaceCullingOn();

  // Create a renderer
  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(originalActor);
  renderer->AddActor(extractedActor);

  renderer->GradientBackgroundOn();
  renderer->SetBackground2(colors->GetColor3d("Beige").GetData());
  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());

  extractedActor->SetPosition((bounds[1] - bounds[0]) / 1.9, 0, 0);
  originalActor->SetPosition(-(bounds[1] - bounds[0]) / 1.9, 0, 0);
  // Create a render window
  vtkSmartPointer<vtkRenderWindow> renwin =
      vtkSmartPointer<vtkRenderWindow>::New();
  renwin->AddRenderer(renderer);
  renwin->SetSize(512, 512);

  // Create an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renwin);
  renwin->Render();
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
