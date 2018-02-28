#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkCutter.h>
#include <vtkDataSetMapper.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkHexahedron.h>
#include <vtkNamedColors.h>
#include <vtkPlane.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>

#include <array>
#include <cstdlib>

int main(int, char* [])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Setup the coordinates of eight points
  // (the two faces must be in counter clockwise order as viewed from the
  // outside)
  std::array<std::array<double, 3>, 8> pointCoords{{
    {{0.0, 0.0, 0.0}},
    {{1.0, 0.0, 0.0}},
    {{1.0, 1.0, 0.0}},
    {{0.0, 1.0, 0.0}},
    {{0.0, 0.0, 1.0}},
    {{1.0, 0.0, 1.0}},
    {{1.0, 1.0, 1.0}},
    {{0.0, 1.0, 1.0}}}};

  // Create the points and a hexahedron from the points.
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkHexahedron> hexa =
    vtkSmartPointer<vtkHexahedron>::New();
  for (auto i = 0; i < pointCoords.size(); ++i)
  {
    points->InsertNextPoint(pointCoords[i].data());
    hexa->GetPointIds()->SetId(i, i);
  }

  // Add the hexahedron to a cell array.
  vtkSmartPointer<vtkCellArray> hexs =
    vtkSmartPointer<vtkCellArray>::New();
  hexs->InsertNextCell(hexa);

  // Add the points and hexahedron to an unstructured grid.
  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  uGrid->SetPoints(points);
  uGrid->InsertNextCell(hexa->GetCellType(), hexa->GetPointIds());

  // Extract the outer (polygonal) surface.
  vtkSmartPointer<vtkDataSetSurfaceFilter> surface =
    vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
  surface->SetInputData(uGrid);
  surface->Update();

  vtkSmartPointer<vtkDataSetMapper> aBeamMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  aBeamMapper->SetInputConnection(surface->GetOutputPort());
  vtkSmartPointer<vtkActor> aBeamActor =
    vtkSmartPointer<vtkActor>::New();
  aBeamActor->SetMapper(aBeamMapper);
  aBeamActor->AddPosition(0, 0, 0);
  aBeamActor->GetProperty()->SetColor(
    colors->GetColor3d("Yellow").GetData());
  aBeamActor->GetProperty()->SetOpacity(0.60);
  aBeamActor->GetProperty()->EdgeVisibilityOn();
  aBeamActor->GetProperty()->SetEdgeColor( 
    colors->GetColor3d("Black").GetData());
  aBeamActor->GetProperty()->SetLineWidth(1.5);

  // Create a plane to cut, here it cuts in the XZ direction
  // (xz normal=(1,0,0); XY =(0,0,1), YZ =(0,1,0)
  vtkSmartPointer<vtkPlane> plane =
    vtkSmartPointer<vtkPlane>::New();
  plane->SetOrigin(0.5, 0, 0);
  plane->SetNormal(1, 0, 0);

  // Create cutter
  vtkSmartPointer<vtkCutter> cutter =
    vtkSmartPointer<vtkCutter>::New();
  cutter->SetCutFunction(plane);
  cutter->SetInputData(aBeamActor->GetMapper()->GetInput());
  cutter->Update();
  vtkSmartPointer<vtkPolyDataMapper> cutterMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cutterMapper->SetInputConnection(cutter->GetOutputPort());

  // Create plane actor
  vtkSmartPointer<vtkActor> planeActor =
    vtkSmartPointer<vtkActor>::New();
  planeActor->GetProperty()->SetColor(
    colors->GetColor3d("Red").GetData());
  planeActor->GetProperty()->SetLineWidth(2);
  planeActor->SetMapper(cutterMapper);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Dataset Surface");
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(aBeamActor);
  renderer->AddActor(planeActor);
  renderer->SetBackground(
    colors->GetColor3d("Seashell").GetData());

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(-25);
  renderer->GetActiveCamera()->Elevation(30);

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
