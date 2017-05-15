#include <vtkSmartPointer.h>

#include <vtkCellLocator.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkDataObject.h>
#include <vtkUnstructuredGrid.h>
#include <vtkIdList.h>
#include <vtkCellArray.h>

#include <vtkUnsignedCharArray.h>
#include <vtkCellData.h>
#include <vtkLineSource.h>

#include <vtkShrinkFilter.h>

#include <vtkDataSetSurfaceFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " filename.vtu" << std::endl;
    return EXIT_FAILURE;
  }

  // Get the filename from the command line
  std::string inputFilename = argv[1];

  // Read a xml unstructured grid dataset
  vtkSmartPointer<vtkXMLUnstructuredGridReader> reader =
    vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  // The line goes through the center of the data and runs along the x axis
  double center[3];
  reader->GetOutput()->GetCenter(center);
  double bounds[6];
  reader->GetOutput()->GetBounds(bounds);

  double startRay[3];
  startRay[0] = bounds[0] - center[0];
  startRay[1] = center[1];
  startRay[2] = center[2];

  double endRay[3];
  endRay[0] = bounds[1] + center[0];
  endRay[1] = center[1];
  endRay[2] = center[2];
  std::cout << "center: "
            << center[0] << ", "
            << center[1] << ", "
            << center[2] << std::endl;
  std::cout << "startRay: "
            << startRay[0] << ", "
            << startRay[1] << ", "
            << startRay[2] << std::endl;
  std::cout << "endRay: "
            << endRay[0] << ", "
            << endRay[1] << ", "
            << endRay[2] << std::endl;

  // Initialize all of the cell data colors
  vtkSmartPointer<vtkUnsignedCharArray> cellData =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  cellData->SetNumberOfComponents(3);
  cellData->SetNumberOfTuples(reader->GetOutput()->GetNumberOfCells());
  reader->GetOutput()->GetCellData()->SetScalars(cellData);

  for (int i = 0; i < cellData->GetNumberOfTuples(); ++i)
  {
    float rgb[3];
    rgb[0] = 227.0; rgb[1] = 207.0; rgb[2] =  87.0; // banana
    cellData->InsertTuple(i, rgb);
  }

  // Find the cells that intersect the line and color those cells
  vtkSmartPointer<vtkIdList> cellIds =
    vtkSmartPointer<vtkIdList>::New();
  vtkSmartPointer<vtkCellLocator> locator =
    vtkSmartPointer<vtkCellLocator>::New();
  locator->SetDataSet(reader->GetOutput());
  locator->BuildLocator();
  locator->FindCellsAlongLine(startRay, endRay, .001, cellIds);

  for (vtkIdType i = 0; i < cellIds->GetNumberOfIds(); ++i)
  {
    float rgb[3];
    rgb[0] = 255; rgb[1] = 99; rgb[2] = 71; // tomato
    cellData->InsertTuple(cellIds->GetId(i), rgb);
  }

  // Shrink each cell to make them visible
  vtkSmartPointer<vtkShrinkFilter> shrink =
    vtkSmartPointer<vtkShrinkFilter>::New();
  shrink->SetInputConnection(reader->GetOutputPort());
  shrink->SetShrinkFactor(.95);

  // Convert the cells to polydata
  vtkSmartPointer<vtkDataSetSurfaceFilter> surface =
    vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
  surface->SetInputConnection(shrink->GetOutputPort());
  surface->SetNonlinearSubdivisionLevel(2);
  surface->Update();

  // Create a line
  vtkSmartPointer<vtkLineSource> lineSource =
    vtkSmartPointer<vtkLineSource>::New();
  lineSource->SetPoint1(startRay);
  lineSource->SetPoint2(endRay);
  vtkSmartPointer<vtkPolyDataMapper> lineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  lineMapper->SetInputConnection(lineSource->GetOutputPort());
  vtkSmartPointer<vtkActor> lineActor =
    vtkSmartPointer<vtkActor>::New();
  lineActor->SetMapper(lineMapper);

  // Render the results
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(surface->GetOutputPort());
  mapper->ScalarVisibilityOn();
  mapper->SetScalarModeToUseCellData();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->AddActor(lineActor);
  renderer->SetBackground(.2, .3, .4);

  // Make an oblique view
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor>
    iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  iren->SetRenderWindow(renWin);
  renWin->AddRenderer(renderer);
  renWin->SetSize(640, 480);
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
