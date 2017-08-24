#include <vtkSmartPointer.h>
#include <vtkDelaunay2D.h>

#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkTriangle.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkLine.h>
#include <vtkCellLocator.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkNamedColors.h>

int main(int, char *[])
{
  // Create a set of heighs on a grid.
  // This is often called a "terrain map".
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  unsigned int GridSize = 10;
  for(unsigned int x = 0; x < GridSize; x++)
  {
    for(unsigned int y = 0; y < GridSize; y++)
    {
        points->InsertNextPoint(x, y, (x+y)/(y+1));
    }
  }

  // Add the grid points to a polydata object
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Triangulate the grid points
  vtkSmartPointer<vtkDelaunay2D> delaunay =
  vtkSmartPointer<vtkDelaunay2D>::New();
  delaunay->SetInputData(polydata);

  // Visualize
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataMapper> meshMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  meshMapper->SetInputConnection(delaunay->GetOutputPort());

  vtkSmartPointer<vtkActor> meshActor =
    vtkSmartPointer<vtkActor>::New();
  meshActor->SetMapper(meshMapper);
  meshActor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
  meshActor->GetProperty()->EdgeVisibilityOn();

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
  glyphFilter->SetInputData(polydata);

  vtkSmartPointer<vtkPolyDataMapper> pointMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pointMapper->SetInputConnection(glyphFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> pointActor =
    vtkSmartPointer<vtkActor>::New();
  pointActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  pointActor->GetProperty()->SetPointSize(5);
  pointActor->SetMapper(pointMapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(meshActor);
  renderer->AddActor(pointActor);
  renderer->SetBackground(colors->GetColor3d("Mint").GetData());

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
