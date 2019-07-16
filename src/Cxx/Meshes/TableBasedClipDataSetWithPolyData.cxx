#include <vtkSmartPointer.h>

#include <vtkConeSource.h>
#include <vtkImplicitPolyDataDistance.h>
#include <vtkPointData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkFloatArray.h>
#include <vtkCellTypes.h>
#include <vtkRectilinearGrid.h>
#include <vtkTableBasedClipDataSet.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRectilinearGridGeometryFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <map>

int main (int, char *[])
{
  // Create polydata to slice the grid with. In this case, use a cone. This could
  // be any polydata including a stl file.
  auto cone =
    vtkSmartPointer<vtkConeSource>::New();
  cone->SetResolution(50);
  cone->SetDirection(0,0,-1);
  cone->SetHeight(3.0);
  cone->CappingOn();
  cone->Update();

  // Implicit function that will be used to slice the mesh
  auto implicitPolyDataDistance =
    vtkSmartPointer<vtkImplicitPolyDataDistance>::New();
  implicitPolyDataDistance->SetInput(cone->GetOutput());

  // create a grid
  unsigned int dimension = 51;
  auto xCoords =
    vtkSmartPointer<vtkFloatArray>::New();
  for (unsigned int i = 0; i < dimension; ++i)
  {
    xCoords->InsertNextValue(-1.0 + i * 2.0 / static_cast<float>(dimension-1));
  }
  auto yCoords =
    vtkSmartPointer<vtkFloatArray>::New();
  for (unsigned int i = 0; i < dimension; ++i)
  {
    yCoords->InsertNextValue(-1.0 + i * 2.0 / static_cast<float>(dimension-1));
  }
  auto zCoords =
    vtkSmartPointer<vtkFloatArray>::New();
  for (unsigned int i = 0; i < dimension; ++i)
  {
    zCoords->InsertNextValue(-1.0 + i * 2.0 / static_cast<float>(dimension-1));
  }
  // The coordinates are assigned to the rectilinear grid. Make sure that
  // the number of values in each of the XCoordinates, YCoordinates,
  // and ZCoordinates is equal to what is defined in SetDimensions().
  auto rgrid =
    vtkSmartPointer<vtkRectilinearGrid>::New();
  rgrid->SetDimensions(xCoords->GetNumberOfTuples(),
                       yCoords->GetNumberOfTuples(),
                       zCoords->GetNumberOfTuples());
  rgrid->SetXCoordinates(xCoords);
  rgrid->SetYCoordinates(yCoords);
  rgrid->SetZCoordinates(zCoords);

  // Create an array to hold distance information
  auto signedDistances =
    vtkSmartPointer<vtkFloatArray>::New();
  signedDistances->SetNumberOfComponents(1);
  signedDistances->SetName("SignedDistances");

  // Evaluate the signed distance function at all of the grid points
  for (vtkIdType pointId = 0; pointId < rgrid->GetNumberOfPoints(); ++pointId)
  {
    double p[3];
    rgrid->GetPoint(pointId, p);
    double signedDistance = implicitPolyDataDistance->EvaluateFunction(p);
    signedDistances->InsertNextValue(signedDistance);
  }

  // Add the SignedDistances to the grid
  rgrid->GetPointData()->SetScalars(signedDistances);

  // Use vtkTableBasedClipDataSet to slice the grid with the polydata
  auto clipper =
    vtkSmartPointer<vtkTableBasedClipDataSet>::New();
  clipper->SetInputData(rgrid);
  clipper->InsideOutOn();
  clipper->SetValue(0.0);
  clipper->GenerateClippedOutputOn();
  clipper->Update();

  // --- mappers, actors, render, etc. ---
  // mapper and actor to view the cone
  auto coneMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection(cone->GetOutputPort());
  auto coneActor =
    vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMapper);

  // geometry filter to view the background grid
  auto geometryFilter =
    vtkSmartPointer<vtkRectilinearGridGeometryFilter>::New();
  geometryFilter->SetInputData(rgrid);
  geometryFilter->SetExtent(0, dimension, 0, dimension, dimension/2, dimension/2);
  geometryFilter->Update();

  auto rgridMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  rgridMapper->SetInputConnection(geometryFilter->GetOutputPort());
  rgridMapper->SetScalarRange(rgrid->GetPointData()->GetArray("SignedDistances")->GetRange());

  auto wireActor =
    vtkSmartPointer<vtkActor>::New();
  wireActor->SetMapper(rgridMapper);
  wireActor->GetProperty()->SetRepresentationToWireframe();

  // mapper and actor to view the clipped mesh
  auto clipperMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  clipperMapper->SetInputConnection(clipper->GetOutputPort());
  clipperMapper->ScalarVisibilityOff();

  auto clipperOutsideMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  clipperOutsideMapper->SetInputConnection(clipper->GetOutputPort(1));
  clipperOutsideMapper->ScalarVisibilityOff();

  auto clipperActor =
    vtkSmartPointer<vtkActor>::New();
  clipperActor->SetMapper(clipperMapper);
  clipperActor->GetProperty()->SetColor(0.89,0.81,0.34); // banana

  auto clipperOutsideActor =
    vtkSmartPointer<vtkActor>::New();
  clipperOutsideActor->SetMapper(clipperOutsideMapper);
  clipperOutsideActor->GetProperty()->SetColor(0.89,0.81,0.34); // banana

  // A renderer and render window
  // Create a renderer, render window, and interactor
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  auto leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.4, .5, .6);
  leftRenderer->UseHiddenLineRemovalOn();

  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};
  auto rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.5, .6, .6);
  rightRenderer->UseHiddenLineRemovalOn();

  // add the actors
  leftRenderer->AddActor(wireActor);
  leftRenderer->AddActor(clipperActor);
  rightRenderer->AddActor(clipperOutsideActor);

  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(leftRenderer);
  renderWindow->AddRenderer(rightRenderer);

  // An interactor
  auto interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Share the camera

  leftRenderer->GetActiveCamera()->SetPosition(0, -1, 0);
  leftRenderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  leftRenderer->GetActiveCamera()->SetViewUp(0, 0, 1);
  leftRenderer->GetActiveCamera()->Azimuth(30);
  leftRenderer->GetActiveCamera()->Elevation(30);
  leftRenderer->ResetCamera();
  rightRenderer->SetActiveCamera(leftRenderer->GetActiveCamera());

  renderWindow->Render();
  interactor->Start();

  // Generate a report
  vtkIdType numberOfCells = clipper->GetOutput()->GetNumberOfCells();
  std::cout << "------------------------" << std::endl;
  std::cout << "The clipped dataset(inside) contains a " << std::endl
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
  std::cout << "The clipped dataset(outside) contains a " << std::endl
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
