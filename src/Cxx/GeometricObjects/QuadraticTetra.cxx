#include <vtkSmartPointer.h>

#include <vtkUnstructuredGrid.h>
#include <vtkQuadraticTetra.h>
#include <vtkTessellatorFilter.h>
#include <vtkNamedColors.h>

#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>

#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkMath.h>

#include <vtkPoints.h>

static vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticTetra();

int main (int, char *[])
{
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    MakeQuadraticTetra();

  vtkSmartPointer<vtkTessellatorFilter> tessellate =
    vtkSmartPointer<vtkTessellatorFilter>::New();
  tessellate->SetInputData(uGrid);

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
  sphereSource->SetRadius(.02);

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

vtkSmartPointer<vtkUnstructuredGrid> MakeQuadraticTetra()
{
  vtkSmartPointer<vtkQuadraticTetra> aTetra =
    vtkSmartPointer<vtkQuadraticTetra>::New();
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  double *pcoords = aTetra->GetParametricCoords();

  vtkMath::RandomSeed(5070); // for testing
  points->SetNumberOfPoints(aTetra->GetNumberOfPoints());
  for (int i = 0; i < aTetra->GetNumberOfPoints(); ++i)
  {
    aTetra->GetPointIds()->SetId(i, i);
    points->SetPoint(i,
                     *(pcoords + 3 * i) + vtkMath::Random(-.1, .1),
                     *(pcoords + 3 * i + 1) + vtkMath::Random(-.1, .1),
                     *(pcoords + 3 * i + 2) + vtkMath::Random(-.1, .1));
  }

  // Add the points and tetra to an unstructured grid
  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  uGrid->SetPoints(points);
  uGrid->InsertNextCell(aTetra->GetCellType(), aTetra->GetPointIds());

  return uGrid;
}

