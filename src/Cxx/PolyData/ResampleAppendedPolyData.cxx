#include <vtkSmartPointer.h>

#include <vtkPlaneSource.h>
#include <vtkPlatonicSolidSource.h>
#include <vtkAppendPolyData.h>
#include <vtkCellLocator.h>
#include <vtkCellArray.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

#include <vtkNamedColors.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <random>

int main(int, char* [])
{
 // Define adjustable paramaters
  constexpr double xMin = -10.0;
  constexpr double xMax =  10.0;
  constexpr double yMin = -10.0;
  constexpr double yMax =  10.0;
  constexpr int xResolution = 100;
  constexpr int yResolution = 100;
  constexpr double scaleMin = .2;
  constexpr double scaleMax = 1.5;
  constexpr int numberOfObjects = 200;
  constexpr int probeResolution = 200.0;

 // Generate terrain
  auto terrain =
    vtkSmartPointer<vtkPlaneSource>::New();
  terrain->SetOrigin(xMin, yMin, 0.0);
  terrain->SetPoint2(xMin, yMax, 0.0);
  terrain->SetPoint1(xMax, yMin, 0.0);
  terrain->SetXResolution(xResolution);
  terrain->SetYResolution(yResolution);
  terrain->Update();

  // Generate objects and append them to terrain
  auto append =
    vtkSmartPointer<vtkAppendPolyData>::New();
  append->AddInputConnection(terrain->GetOutputPort());

  std::mt19937_64 mt(4355412); //Standard mersenne twister engine
  std::uniform_int_distribution<> solid(0, 4);
  std::uniform_real_distribution<> scale(scaleMin, scaleMax);
  std::uniform_real_distribution<> position(xMin + 1.0, xMax - 1.0);

  for (auto i = 0; i < numberOfObjects; ++i)
  {
    // Generate an object
    auto platonic =
      vtkSmartPointer<vtkPlatonicSolidSource>::New();
    platonic->SetSolidType(solid(mt));

    // Translate and scale
    auto transform =
      vtkSmartPointer<vtkTransform>::New();
    double s = scale(mt);
    transform->Translate(position(mt), position(mt), 0.0);
    transform->Scale(s, s, s);
    auto transformPD =
      vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    transformPD->SetTransform(transform);
    transformPD->SetInputConnection(platonic->GetOutputPort());
    transformPD->Update();

    auto pd =
      vtkSmartPointer<vtkPolyData>::New();
    pd->DeepCopy(transformPD->GetOutput());    
    append->AddInputData(pd);
  }
  append->Update();

  // Resample terrian
  auto cellLocator =
    vtkSmartPointer<vtkCellLocator>::New();
  cellLocator->SetDataSet(append->GetOutput());
  cellLocator->BuildLocator();

  // Generate a probe plane
  auto probeTerrain =
    vtkSmartPointer<vtkPlaneSource>::New();
  probeTerrain->SetOrigin(terrain->GetOrigin());
  probeTerrain->SetPoint2(terrain->GetPoint2());
  probeTerrain->SetPoint1(terrain->GetPoint1());
  probeTerrain->SetXResolution(probeResolution);
  probeTerrain->SetYResolution(probeResolution);
  probeTerrain->Update();

  vtkPoints *probePoints = probeTerrain->GetOutput()->GetPoints();
  for(auto i = 0; i < probeTerrain->GetOutput()->GetNumberOfPoints(); ++i)
  {
    int subId;
    double t, xyz[3], pcoords[3];
    double rayStart[3], rayEnd[3];
    probePoints->GetPoint(i, rayStart);
    rayStart[2] += 100000.0;
    probePoints->GetPoint(i, rayEnd);
    rayEnd[2] -= 100000.0;

    if (cellLocator->IntersectWithLine(
          rayStart,
          rayEnd,
          0.0001,
          t,
          xyz,
          pcoords,
          subId))
    {
      // The new elevation is in xyz[2]
      double pt[3];
      probePoints->GetPoint(i, pt);
      probePoints->SetPoint(i, pt[0], pt[1], xyz[2]);
    }
  }
  probeTerrain->GetOutput()->GetPointData()->SetNormals(nullptr);

  // Visualize
  auto colors =
  vtkSmartPointer<vtkNamedColors>::New();

  // Two viewports, left for original and right for resampled
  auto originalMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(append->GetOutputPort());
  originalMapper->SetInputData(append->GetOutput());
  originalMapper->ScalarVisibilityOff();

  auto originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetRepresentationToWireframe();

  auto resampledMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  resampledMapper->SetInputConnection(append->GetOutputPort());
  resampledMapper->SetInputData(probeTerrain->GetOutput());
  resampledMapper->ScalarVisibilityOff();

  auto resampledActor =
    vtkSmartPointer<vtkActor>::New();
  resampledActor->SetMapper(resampledMapper);
  resampledActor->GetProperty()->SetRepresentationToWireframe();

  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};
  auto rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->UseHiddenLineRemovalOn();
  rightRenderer->AddActor(resampledActor);
  rightRenderer->SetBackground(colors->GetColor3d("dimgray").GetData());

  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  auto leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->UseHiddenLineRemovalOn();
  leftRenderer->AddActor(originalActor);
  leftRenderer->SetBackground(colors->GetColor3d("dimgray").GetData());
  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(rightRenderer);
  renderWindow->AddRenderer(leftRenderer);
  renderWindow->SetSize(1024, 512);

  auto renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  auto style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  renderWindowInteractor->SetInteractorStyle(style);

  renderWindow->Render();
  vtkCamera *camera;
  camera = leftRenderer->GetActiveCamera();
  camera->SetFocalPoint(0.0, 0.0, 0.0);
  camera->SetPosition(1.0, 0.0, 0.0);
  camera->SetViewUp(0.0, 0.0, 1.0);
  camera->Azimuth(30.0);
  camera->Elevation(30.0);

  leftRenderer->ResetCamera();
  rightRenderer->SetActiveCamera(camera);
  renderWindow->Render();

  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
