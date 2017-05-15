#include <vtkSmartPointer.h>

#include <vtkVersion.h>

#include <vtkActor.h>
#include <vtkBox.h>
#include <vtkCamera.h>
#include <vtkCellData.h>
#include <vtkClipPolyData.h>
#include <vtkCubeSource.h>
#include <vtkDataSetWriter.h>
#include <vtkIdFilter.h>
#include <vtkIdTypeArray.h>
#include <vtkImplicitDataSet.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataWriter.h>

void WritePolyData(vtkPolyData* const polyData, const std::string& filename)
{
    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
#if VTK_MAJOR_VERSION <= 5
    writer->SetInput(polyData);
#else
    writer->SetInputData(polyData);
#endif
    writer->SetFileName(filename.c_str());
    writer->Write();
}

void WriteDataSet(vtkDataSet* const dataSet, const std::string& filename)
{
    vtkSmartPointer<vtkDataSetWriter> writer = vtkSmartPointer<vtkDataSetWriter>::New();
#if VTK_MAJOR_VERSION <= 5
    writer->SetInput(dataSet);
#else
    writer->SetInputData(dataSet);
#endif
    writer->SetFileName(filename.c_str());
    writer->Write();
}

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(.75, 0, 0);

  unsigned int res = 10;
  sphereSource->SetThetaResolution(res);
  sphereSource->SetPhiResolution(res);
  sphereSource->Update();

  std::cout << "The sphere has " << sphereSource->GetOutput()->GetNumberOfPoints()
            << " points." << " and " << sphereSource->GetOutput()->GetNumberOfCells()
            << " cells. " << std::endl;

  // Add ids to the points and cells of the sphere
  vtkSmartPointer<vtkIdFilter> cellIdFilter =
      vtkSmartPointer<vtkIdFilter>::New();
  cellIdFilter->SetInputConnection(sphereSource->GetOutputPort());
  cellIdFilter->SetCellIds(true);
  cellIdFilter->SetPointIds(false);
  cellIdFilter->SetIdsArrayName("CellIds");
  cellIdFilter->Update();

  WriteDataSet(cellIdFilter->GetOutput(), "CellIdFilter.vtp");

  vtkSmartPointer<vtkIdFilter> pointIdFilter =
      vtkSmartPointer<vtkIdFilter>::New();
  pointIdFilter->SetInputConnection(cellIdFilter->GetOutputPort());
  pointIdFilter->SetCellIds(false);
  pointIdFilter->SetPointIds(true);
  pointIdFilter->SetIdsArrayName("PointIds");
  pointIdFilter->Update();

 vtkDataSet* sphereWithIds = pointIdFilter->GetOutput();

  WriteDataSet(sphereWithIds, "BothIdFilter.vtp");

  vtkSmartPointer<vtkCubeSource> cubeSource =
      vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();

  vtkSmartPointer<vtkBox> implicitCube =
      vtkSmartPointer<vtkBox>::New();
  implicitCube->SetBounds(cubeSource->GetOutput()->GetBounds());

  vtkSmartPointer<vtkClipPolyData> clipper =
      vtkSmartPointer<vtkClipPolyData>::New();
  clipper->SetClipFunction(implicitCube);
#if VTK_MAJOR_VERSION <= 5
  clipper->SetInput(sphereWithIds);
#else
  clipper->SetInputData(sphereWithIds);
#endif
  clipper->InsideOutOn();
  clipper->Update();

  WriteDataSet(clipper->GetOutput(), "clipper.vtp");

  // Get the clipped cell ids
  vtkPolyData* clipped = clipper->GetOutput();

  std::cout << "There are " << clipped->GetNumberOfPoints() << " clipped points." << std::endl;
  std::cout << "There are " << clipped->GetNumberOfCells() << " clipped cells." << std::endl;

  vtkIdTypeArray* clippedCellIds = vtkIdTypeArray::SafeDownCast(clipped->GetCellData()->GetArray("CellIds"));

  for(vtkIdType i = 0; i < clippedCellIds->GetNumberOfTuples(); i++)
  {
    std::cout << "Clipped cell id " << i << " : " << clippedCellIds->GetValue(i) << std::endl;
  }

  // Create a mapper and actor for clipped sphere
  vtkSmartPointer<vtkPolyDataMapper> clippedMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  clippedMapper->SetInputConnection(clipper->GetOutputPort());
  clippedMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> clippedActor =
      vtkSmartPointer<vtkActor>::New();
  clippedActor->SetMapper(clippedMapper);
  clippedActor->GetProperty()->SetRepresentationToWireframe();

  // Create a mapper and actor for cube
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

  vtkSmartPointer<vtkActor> cubeActor =
      vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);
  cubeActor->GetProperty()->SetRepresentationToWireframe();
  cubeActor->GetProperty()->SetOpacity(0.5);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actor to the scene
  renderer->AddActor(clippedActor);
  renderer->AddActor(cubeActor);
  renderer->SetBackground(.2, .3, .4);

  // Generate an interesting view
  //
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(-30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.1);
  renderer->ResetCameraClippingRange();

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
