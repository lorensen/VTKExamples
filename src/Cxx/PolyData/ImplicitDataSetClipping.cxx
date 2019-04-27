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
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkVersion.h>
#include <vtkXMLPolyDataWriter.h>

#if VTK_VERSION_NUMBER >= 89000000000ULL
#define VTK890 1
#endif

namespace {
void WritePolyData(vtkPolyData* const polyData, const std::string& filename);

void WriteDataSet(vtkDataSet* const dataSet, const std::string& filename);
} // namespace

int main(int, char*[])
{
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  colors->SetColor("Bkg", 0.2, 0.3, 0.4);

  auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(.75, 0, 0);

  unsigned int res = 10;
  sphereSource->SetThetaResolution(res);
  sphereSource->SetPhiResolution(res);
  sphereSource->Update();

  std::cout << "The sphere has "
            << sphereSource->GetOutput()->GetNumberOfPoints() << " points."
            << " and " << sphereSource->GetOutput()->GetNumberOfCells()
            << " cells. " << std::endl;

  // Add ids to the points and cells of the sphere
  auto cellIdFilter = vtkSmartPointer<vtkIdFilter>::New();
  cellIdFilter->SetInputConnection(sphereSource->GetOutputPort());
  cellIdFilter->SetCellIds(true);
  cellIdFilter->SetPointIds(false);
#if VTK890
  cellIdFilter->SetCellIdsArrayName("CellIds");
#else
  cellIdFilter->SetIdsArrayName("CellIds");
#endif
  cellIdFilter->Update();

  WriteDataSet(cellIdFilter->GetOutput(), "CellIdFilter.vtp");

  auto pointIdFilter = vtkSmartPointer<vtkIdFilter>::New();
  pointIdFilter->SetInputConnection(cellIdFilter->GetOutputPort());
  pointIdFilter->SetCellIds(false);
  pointIdFilter->SetPointIds(true);
#if VTK890
  pointIdFilter->SetPointIdsArrayName("PointIds");
#else
  pointIdFilter->SetIdsArrayName("PointIds");
#endif
  pointIdFilter->Update();

  vtkDataSet* sphereWithIds = pointIdFilter->GetOutput();

  WriteDataSet(sphereWithIds, "BothIdFilter.vtp");

  auto cubeSource = vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();

  auto implicitCube = vtkSmartPointer<vtkBox>::New();
  implicitCube->SetBounds(cubeSource->GetOutput()->GetBounds());

  auto clipper = vtkSmartPointer<vtkClipPolyData>::New();
  clipper->SetClipFunction(implicitCube);
  clipper->SetInputData(sphereWithIds);
  clipper->InsideOutOn();
  clipper->Update();

  WriteDataSet(clipper->GetOutput(), "clipper.vtp");

  // Get the clipped cell ids
  vtkPolyData* clipped = clipper->GetOutput();

  std::cout << "There are " << clipped->GetNumberOfPoints()
            << " clipped points." << std::endl;
  std::cout << "There are " << clipped->GetNumberOfCells() << " clipped cells."
            << std::endl;

  vtkIdTypeArray* clippedCellIds = dynamic_cast<vtkIdTypeArray*>(
      clipped->GetCellData()->GetArray("CellIds"));

  for (vtkIdType i = 0; i < clippedCellIds->GetNumberOfTuples(); i++)
  {
    std::cout << "Clipped cell id " << i << " : " << clippedCellIds->GetValue(i)
              << std::endl;
  }

  // Create a mapper and actor for clipped sphere
  auto clippedMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  clippedMapper->SetInputConnection(clipper->GetOutputPort());
  clippedMapper->ScalarVisibilityOff();

  auto clippedActor = vtkSmartPointer<vtkActor>::New();
  clippedActor->SetMapper(clippedMapper);
  clippedActor->GetProperty()->SetRepresentationToWireframe();

  // Create a mapper and actor for cube
  auto cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

  auto cubeActor = vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);
  cubeActor->GetProperty()->SetRepresentationToWireframe();
  cubeActor->GetProperty()->SetOpacity(0.5);

  // Create a renderer, render window, and interactor
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(clippedActor);
  renderer->AddActor(cubeActor);
  renderer->SetBackground(colors->GetColor3d("Bkg").GetData());

  // Generate an interesting view
  //
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(-30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.1);
  renderer->ResetCameraClippingRange();

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

namespace {
void WritePolyData(vtkPolyData* const polyData, const std::string& filename)
{
  auto writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputData(polyData);
  writer->SetFileName(filename.c_str());
  writer->Write();
}

void WriteDataSet(vtkDataSet* const dataSet, const std::string& filename)
{
  auto writer = vtkSmartPointer<vtkDataSetWriter>::New();
  writer->SetInputData(dataSet);
  writer->SetFileName(filename.c_str());
  writer->Write();
}
} // namespace
