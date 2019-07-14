#include <vtkSmartPointer.h>
#include <vtkVRMLImporter.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkContourFilter.h>
#include <vtkStreamTracer.h>
#include <vtkGenericOutlineFilter.h>
#include <vtkPointSource.h>
#include <vtkTubeFilter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSphereSource.h>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>

#include <vtkPolyDataMapper.h>

#include <vtkNamedColors.h>

int main (int argc, char *argv[])
{
  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkColor3d isoSurfaceColor = colors->GetColor3d("WhiteSmoke");
  vtkColor3d sphereColor = colors->GetColor3d("hotpink");
  vtkColor3d backgroundColor = colors->GetColor3d("SlateGray");

  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->UseHiddenLineRemovalOn();

  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  auto renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Import the VRML Files that define the geometry
  auto vrmlImport =
    vtkSmartPointer<vtkVRMLImporter>::New();
  vrmlImport->SetRenderWindow(renderWindow);
  vrmlImport->SetFileName(argv[1]);
  vrmlImport->Update();

  // Read the UnstructuredGrid define the solution
  auto solution =
    vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
  solution->SetFileName(argv[2]);
  solution->Update();

  // Create an outline
  auto outline =
    vtkSmartPointer<vtkGenericOutlineFilter>::New();
  outline->SetInputConnection(solution->GetOutputPort());

  // Create Seeds
  auto seeds =
    vtkSmartPointer<vtkPointSource>::New();
  seeds->SetRadius(0.2);
  seeds->SetCenter(3.5, 0.625, 1.25);
  seeds->SetNumberOfPoints(50);

  // Create streamlines  
  auto streamTracer =
    vtkSmartPointer<vtkStreamTracer>::New();
  streamTracer->SetIntegrationDirectionToBoth();
  streamTracer->SetInputConnection(solution->GetOutputPort());
  streamTracer->SetSourceConnection(seeds->GetOutputPort());
  streamTracer->SetMaximumPropagation(50);
  streamTracer->SetInitialIntegrationStep(.2);
  streamTracer->SetMinimumIntegrationStep(.01);
  streamTracer->SetIntegratorType(1);
  streamTracer->SetComputeVorticity(1);
  
  auto tubes =
    vtkSmartPointer<vtkTubeFilter>::New();
  tubes->SetInputConnection(streamTracer->GetOutputPort());
  tubes->SetNumberOfSides(8);
  tubes->SetRadius(.02);
  tubes->SetVaryRadius(0);

  auto mapTubes =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapTubes->SetInputConnection(tubes->GetOutputPort());
  mapTubes->SetScalarRange(solution->GetOutput()->GetScalarRange());

  auto tubesActor =
    vtkSmartPointer<vtkActor>::New();
  tubesActor->SetMapper(mapTubes);

  // Create an Isosurface
  auto isoSurface =
    vtkSmartPointer<vtkContourFilter>::New();
  isoSurface->SetValue(0, 550.0);
  isoSurface->SetInputConnection(solution->GetOutputPort());

  auto isoSurfaceMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  isoSurfaceMapper->SetInputConnection(isoSurface->GetOutputPort());
  isoSurfaceMapper->ScalarVisibilityOff();

  auto isoSurfaceActor =
    vtkSmartPointer<vtkActor>::New();
  isoSurfaceActor->SetMapper(isoSurfaceMapper);
  isoSurfaceActor->GetProperty()->SetOpacity(.5);
  isoSurfaceActor->GetProperty()->SetDiffuseColor(isoSurfaceColor.GetData());

  auto sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetCenter(seeds->GetCenter());
  sphere->SetRadius(seeds->GetRadius());
  sphere->SetThetaResolution(20);
  sphere->SetPhiResolution(11);;
  auto sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphere->GetOutputPort());

  auto sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetOpacity(1.0);
  sphereActor->GetProperty()->SetSpecular(.4);
  sphereActor->GetProperty()->SetSpecularPower(80);
  sphereActor->GetProperty()->SetDiffuseColor(sphereColor.GetData());

  renderer->AddActor(tubesActor);
  renderer->AddActor(sphereActor);
  renderer->AddActor(isoSurfaceActor);

  renderer->SetBackground(backgroundColor.GetData());
  renderWindow->SetSize(640, 512);
  renderWindow->Render();
  renderer->GetActiveCamera()->Azimuth(15.0);
  renderer->GetActiveCamera()->Elevation(15.0);
  renderer->GetActiveCamera()->Dolly(1.25);
  renderer->ResetCameraClippingRange();

  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
