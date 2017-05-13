#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>
#include <vtkCellLocator.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkTriangleFilter.h>

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
    // Small sphere with most polgons
    vtkSmartPointer<vtkSphereSource> sphereSource1 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource1->SetThetaResolution(10);
    sphereSource1->SetPhiResolution(10);
    sphereSource1->SetCenter(5, 5, 5);

    // Large sphere with least polygons
    vtkSmartPointer<vtkSphereSource> sphereSource2 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource2->SetRadius(10);
    sphereSource2->SetCenter(10,1,10);

    vtkSmartPointer<vtkAppendPolyData> appendFilter =
      vtkSmartPointer<vtkAppendPolyData>::New();
    appendFilter->AddInputConnection(sphereSource1->GetOutputPort());
    appendFilter->AddInputConnection(sphereSource2->GetOutputPort());
    appendFilter->Update();
    polyData = appendFilter->GetOutput();
  }

  double center[3], bounds[6];
  polyData->GetCenter(center);
  std::cout << "Center of data is: "
            << center[0] << ", "
            << center[1] << ", "
            << center[2] << std::endl;
  polyData->GetPoints()->GetBounds(bounds);
  std::cout << "Bounds of data is: "
            << bounds[0] << ", "
            << bounds[1] << ", "
            << bounds[2] << ", "
            << bounds[3] << ", "
            << bounds[4] << ", "
            << bounds[5] << std::endl;

  // Build a cell locator.
  vtkSmartPointer<vtkCellLocator> cellLocator =
    vtkSmartPointer<vtkCellLocator>::New();
  cellLocator->SetDataSet(polyData);
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
  std::cout << "Id of cell on outside surface: " << cellId << std::endl;

  vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter =
      vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  connectivityFilter->SetInput(polyData);
#else
  connectivityFilter->SetInputData(polyData);
#endif
  connectivityFilter->SetExtractionModeToCellSeededRegions();
  connectivityFilter->InitializeSeedList();
  connectivityFilter->AddSeed(cellId);

  // Create a mapper and actor for original data
    vtkSmartPointer<vtkPolyDataMapper> originalMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  originalMapper->SetInput(polyData);
#else
  originalMapper->SetInputData(polyData);
#endif

  vtkSmartPointer<vtkActor> originalActor =
      vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);

  // Create a mapper and actor for extracted data
  vtkSmartPointer<vtkPolyDataMapper> extractedMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  extractedMapper->SetInputConnection(connectivityFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> extractedActor =
      vtkSmartPointer<vtkActor>::New();
  extractedActor->GetProperty()->SetColor(1,0,0);
  extractedActor->SetMapper(extractedMapper);

  // Create a renderer
  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(originalActor);
  renderer->AddActor(extractedActor);

  // Create a render window
  vtkSmartPointer<vtkRenderWindow> renwin =
      vtkSmartPointer<vtkRenderWindow>::New();
  renwin->AddRenderer(renderer);

  // Create an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renwin);
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
