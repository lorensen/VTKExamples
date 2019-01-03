#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTriangle.h>

int main(int , char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create a triangle
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint ( 1.0, 0.0, 0.0 );
  points->InsertNextPoint ( 0.0, 0.0, 0.0 );
  points->InsertNextPoint ( 0.0, 1.0, 0.0 );
  
  vtkSmartPointer<vtkTriangle> triangle =
    vtkSmartPointer<vtkTriangle>::New();
  triangle->GetPointIds()->SetId ( 0, 0 );
  triangle->GetPointIds()->SetId ( 1, 1 );
  triangle->GetPointIds()->SetId ( 2, 2 );
  
  vtkSmartPointer<vtkCellArray> triangles =
    vtkSmartPointer<vtkCellArray>::New();
  triangles->InsertNextCell ( triangle );
  
  // Create a polydata object
  vtkSmartPointer<vtkPolyData> trianglePolyData =
    vtkSmartPointer<vtkPolyData>::New();

  // Add the geometry and topology to the polydata
  trianglePolyData->SetPoints ( points );
  trianglePolyData->SetPolys ( triangles );
  
  // Create mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(trianglePolyData);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->GetProperty()->SetColor(colors->GetColor3d("Cyan").GetData());
  actor->SetMapper(mapper);

  // Create a renderer, render window, and an interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Triangle");
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("DarkGreen").GetData());

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
