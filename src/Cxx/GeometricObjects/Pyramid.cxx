#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkDataSetMapper.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <vtkPyramid.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>

int main(int , char *[])
{
  vtkSmartPointer<vtkPoints> points = 
      vtkSmartPointer<vtkPoints>::New();
  
  float p0[3] = {1.0, 1.0, 1.0};
  float p1[3] = {-1.0, 1.0, 1.0};
  float p2[3] = {-1.0, -1.0, 1.0};
  float p3[3] = {1.0, -1.0, 1.0};
  float p4[3] = {0.0, 0.0, 0.0};
    
  points->InsertNextPoint(p0);
  points->InsertNextPoint(p1);
  points->InsertNextPoint(p2);
  points->InsertNextPoint(p3);
  points->InsertNextPoint(p4);
  
  vtkSmartPointer<vtkPyramid> pyramid = 
      vtkSmartPointer<vtkPyramid>::New();
  pyramid->GetPointIds()->SetId(0,0);
  pyramid->GetPointIds()->SetId(1,1);
  pyramid->GetPointIds()->SetId(2,2);
  pyramid->GetPointIds()->SetId(3,3);
  pyramid->GetPointIds()->SetId(4,4);
  
  vtkSmartPointer<vtkCellArray> cells = 
      vtkSmartPointer<vtkCellArray>::New();
  cells->InsertNextCell (pyramid);
  
  vtkSmartPointer<vtkUnstructuredGrid> ug = 
      vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(pyramid->GetCellType(),pyramid->GetPointIds());
  
  //Create an actor and mapper
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkSmartPointer<vtkDataSetMapper> mapper = 
      vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputData(ug);

  vtkSmartPointer<vtkActor> actor = 
      vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Pyramid");
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);

  // Create a nice view
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(180);
  renderer->GetActiveCamera()->Elevation(-20);
  renderer->ResetCameraClippingRange();

renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
