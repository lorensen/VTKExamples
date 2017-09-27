#include <vtkSmartPointer.h>
#include <vtkDelaunay2D.h>

#include <vtkCellArray.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolygon.h>
#include <vtkMath.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>
#include <vtkVersionMacros.h> // For version macros

int main(int, char *[])
{
  // Generate a 10 x 10 grid of points
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  for(unsigned int x = 0; x < 10; x++)
  {
    for(unsigned int y = 0; y < 10; y++)
    {
      points->InsertNextPoint(x + vtkMath::Random(-.25, .25),
                              y + vtkMath::Random(-.25,.25),
                              0);
    }
  }

  vtkSmartPointer<vtkPolyData> aPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  aPolyData->SetPoints(points);

  // Create a cell array to store the polygon in
  vtkSmartPointer<vtkCellArray> aCellArray =
    vtkSmartPointer<vtkCellArray>::New();

  // Define a polygonal hole with a clockwise polygon
  vtkSmartPointer<vtkPolygon> aPolygon =
   vtkSmartPointer<vtkPolygon>::New();

  aPolygon->GetPointIds()->InsertNextId(22);
  aPolygon->GetPointIds()->InsertNextId(23);
  aPolygon->GetPointIds()->InsertNextId(24);
  aPolygon->GetPointIds()->InsertNextId(25);
  aPolygon->GetPointIds()->InsertNextId(35);
  aPolygon->GetPointIds()->InsertNextId(45);
  aPolygon->GetPointIds()->InsertNextId(44);
  aPolygon->GetPointIds()->InsertNextId(43);
  aPolygon->GetPointIds()->InsertNextId(42);
  aPolygon->GetPointIds()->InsertNextId(32);

  aCellArray->InsertNextCell(aPolygon);

  // Create a polydata to store the boundary. The points must be the
  // same as the points we will triangulate.
  vtkSmartPointer<vtkPolyData> boundary =
   vtkSmartPointer<vtkPolyData>::New();
  boundary->SetPoints(aPolyData->GetPoints());
  boundary->SetPolys(aCellArray);

  // Triangulate the grid points
  vtkSmartPointer<vtkDelaunay2D> delaunay =
   vtkSmartPointer<vtkDelaunay2D>::New();
  delaunay->SetInputData(aPolyData);
  delaunay->SetSourceData(boundary);

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> meshMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  meshMapper->SetInputConnection(delaunay->GetOutputPort());

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkActor> meshActor =
    vtkSmartPointer<vtkActor>::New();
  meshActor->SetMapper(meshMapper);
  meshActor->GetProperty()->EdgeVisibilityOn();
  meshActor->GetProperty()->SetEdgeColor(colors->GetColor3d("Peacock").GetData());
  meshActor->GetProperty()->SetInterpolationToFlat();

  vtkSmartPointer<vtkPolyDataMapper> boundaryMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  boundaryMapper->SetInputData(boundary);

  vtkSmartPointer<vtkActor> boundaryActor =
    vtkSmartPointer<vtkActor>::New();
  boundaryActor->SetMapper(boundaryMapper);
  boundaryActor->GetProperty()->SetColor(colors->GetColor3d("Raspberry").GetData());
  boundaryActor->GetProperty()->SetLineWidth(3);
  boundaryActor->GetProperty()->EdgeVisibilityOn();
  boundaryActor->GetProperty()->SetEdgeColor(1,0,0);
  boundaryActor->GetProperty()->SetRepresentationToWireframe();

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(meshActor);
  renderer->AddActor(boundaryActor);
  renderer->SetBackground(colors->GetColor3d("Mint").GetData());

  // Render and interact
  renderWindow->SetSize(640, 480);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
