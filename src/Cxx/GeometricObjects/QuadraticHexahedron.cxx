#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkGlyph3D.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <vtkQuadraticHexahedron.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTessellatorFilter.h>
#include <vtkUnstructuredGrid.h>

namespace
{
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticHexahedron();
}

int main (int, char *[])
{
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    MakeQuadraticHexahedron();

  vtkSmartPointer<vtkTessellatorFilter> tessellate =
    vtkSmartPointer<vtkTessellatorFilter>::New();
  tessellate->SetInputData(uGrid);
  tessellate->SetMaximumNumberOfSubdivisions(2);

  vtkSmartPointer<vtkDataSetMapper> mapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(tessellate->GetOutputPort());
  mapper->ScalarVisibilityOff();
 
  // Create an actor for the grid
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuseColor(
    namedColors->GetColor3d("Tomato").GetData());
  actor->GetProperty()->SetEdgeColor(
    namedColors->GetColor3d("IvoryBlack").GetData());
  actor->GetProperty()->EdgeVisibilityOn();

  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(0.02);

  vtkSmartPointer<vtkGlyph3D> glyph3D =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph3D->SetInputData(uGrid);
  glyph3D->SetSourceConnection(sphereSource->GetOutputPort());
  glyph3D->ScalingOff();
  glyph3D->Update();

  vtkSmartPointer<vtkDataSetMapper> glyph3DMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  glyph3DMapper->SetInputConnection(glyph3D->GetOutputPort());
  glyph3DMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> glyph3DActor =
    vtkSmartPointer<vtkActor>::New();
  glyph3DActor->SetMapper(glyph3DMapper);
  glyph3DActor->GetProperty()->SetColor(
    namedColors->GetColor3d("Banana").GetData());

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Quadratic Hexahedron");
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(actor);
  renderer->AddActor(glyph3DActor);
  renderer->SetBackground(namedColors->GetColor3d("SlateGray").GetData());
 
  renderWindow->Render();
  interactor->Start();
 
  return EXIT_SUCCESS;
}

namespace
{
vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticHexahedron()
{
  vtkSmartPointer<vtkQuadraticHexahedron> aHexahedron =
    vtkSmartPointer<vtkQuadraticHexahedron>::New();
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  double *pcoords = aHexahedron->GetParametricCoords();
  vtkSmartPointer<vtkMinimalStandardRandomSequence> rng =
    vtkSmartPointer<vtkMinimalStandardRandomSequence>::New();
  points->SetNumberOfPoints(aHexahedron->GetNumberOfPoints());
  rng->SetSeed(5070); // for testing
  for (auto i = 0; i < aHexahedron->GetNumberOfPoints(); ++i)
  {
    double perturbation[3];
    for (auto j = 0; j < 3; ++j)
    {
      rng->Next();
      perturbation[j] = rng->GetRangeValue(-0.1, 0.1);
    }
    aHexahedron->GetPointIds()->SetId(i, i);
    points->SetPoint(i,
                     *(pcoords + 3 * i) + perturbation[0],
                     *(pcoords + 3 * i + 1) + perturbation[1],
                     *(pcoords + 3 * i + 2) + perturbation[2]);
  }

  // Add the points and hexahedron to an unstructured grid
  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  uGrid->SetPoints(points);
  uGrid->InsertNextCell(aHexahedron->GetCellType(), aHexahedron->GetPointIds());

  return uGrid;
}
}
