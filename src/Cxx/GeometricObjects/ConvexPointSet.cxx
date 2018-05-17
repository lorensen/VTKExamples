#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConvexPointSet.h>
#include <vtkDataSetMapper.h>
#include <vtkGlyph3DMapper.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkShrinkFilter.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkUnstructuredGrid.h>

int main (int, char *[])
{
  vtkSmartPointer<vtkConvexPointSet> cps =
    vtkSmartPointer<vtkConvexPointSet>::New();
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint( 0, 0, 0);
  points->InsertNextPoint( 1, 0, 0);
  points->InsertNextPoint( 1, 1, 0);
  points->InsertNextPoint( 0, 1, 0);
  points->InsertNextPoint( 0, 0, 1);
  points->InsertNextPoint( 1, 0, 1);
  points->InsertNextPoint( 1, 1, 1);
  points->InsertNextPoint( 0, 1, 1);
  points->InsertNextPoint( 0.5, 0, 0);
  points->InsertNextPoint( 1, 0.5, 0);
  points->InsertNextPoint( 0.5, 1, 0);
  points->InsertNextPoint( 0, 0.5, 0);
  points->InsertNextPoint( 0.5, 0.5, 0);

  for (int i = 0; i < 13; ++i)
  {
    cps->GetPointIds()->InsertId(i,i);
  }

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->Allocate(1,1);
  ug->InsertNextCell(cps->GetCellType(), cps->GetPointIds());
  ug->SetPoints(points);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputData(ug);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  actor->GetProperty()->SetLineWidth(3);
  actor->GetProperty()->EdgeVisibilityOn();

  // Glyph the points
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetPhiResolution(21);
  sphere->SetThetaResolution(21);
  sphere->SetRadius(.03);

  // Create a polydata to store everything in
  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();
  polyData->SetPoints(points);

  vtkSmartPointer<vtkGlyph3DMapper> pointMapper =
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  pointMapper->SetInputData(polyData);
  pointMapper->SetSourceConnection(sphere->GetOutputPort());

  vtkSmartPointer<vtkActor> pointActor =
    vtkSmartPointer<vtkActor>::New();
  pointActor->SetMapper(pointMapper);
  pointActor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Convex Point Set");
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actors to the scene
  renderer->AddActor(actor);
  renderer->AddActor(pointActor);
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(210);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCameraClippingRange();

  //Render and interact
  renderWindow->SetSize(640, 480);  
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
