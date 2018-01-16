#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRotationalExtrusionFilter.h>
#include <vtkStripper.h>
#include <vtkTubeFilter.h>

int main (int, char *[])
{
// Create the RenderWindow, Renderer and both Actors
//
  vtkSmartPointer<vtkNamedColors> colors = 
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

// create bottle profile
//
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertPoint(0, 0.01, 0.0, 0.0);
  points->InsertPoint(1, 1.5, 0.0, 0.0);
  points->InsertPoint(2, 1.5, 0.0, 3.5);
  points->InsertPoint(3, 1.25, 0.0, 3.75);
  points->InsertPoint(4, 0.75, 0.0, 4.00);
  points->InsertPoint(5, 0.6, 0.0, 4.35);
  points->InsertPoint(6, 0.7, 0.0, 4.65);
  points->InsertPoint(7, 1.0, 0.0, 4.75);
  points->InsertPoint(8, 1.0, 0.0, 5.0);
  points->InsertPoint(9, 0.2, 0.0, 5.0);
  
  vtkSmartPointer<vtkCellArray> lines =
    vtkSmartPointer<vtkCellArray>::New();
  lines->InsertNextCell(10);//number of points
  lines->InsertCellPoint(0);
  lines->InsertCellPoint(1);
  lines->InsertCellPoint(2);
  lines->InsertCellPoint(3);
  lines->InsertCellPoint(4);
  lines->InsertCellPoint(5);
  lines->InsertCellPoint(6);
  lines->InsertCellPoint(7);
  lines->InsertCellPoint(8);
  lines->InsertCellPoint(9);

  vtkSmartPointer<vtkPolyData> profile =
    vtkSmartPointer<vtkPolyData>::New();
  profile->SetPoints(points);
  profile->SetLines(lines);

// extrude profile to make bottle
//
  vtkSmartPointer<vtkRotationalExtrusionFilter> extrude =
    vtkSmartPointer<vtkRotationalExtrusionFilter>::New();
  extrude->SetInputData(profile);
  extrude->SetResolution(60);
    
  vtkSmartPointer<vtkPolyDataMapper> map =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  map->SetInputConnection(extrude->GetOutputPort());

  vtkSmartPointer<vtkActor> bottle =
    vtkSmartPointer<vtkActor>::New();
  bottle->SetMapper(map);
  bottle->GetProperty()->SetColor(colors->GetColor3d("Mint").GetData());

// display the profile
  vtkSmartPointer<vtkStripper> stripper =
    vtkSmartPointer<vtkStripper>::New();
  stripper->SetInputData(profile);

  vtkSmartPointer<vtkTubeFilter> tubes =
    vtkSmartPointer<vtkTubeFilter>::New();
  tubes->SetInputConnection(stripper->GetOutputPort());
  tubes->SetNumberOfSides(11);
  tubes->SetRadius(.05);

  vtkSmartPointer<vtkPolyDataMapper> profileMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  profileMapper->SetInputConnection(tubes->GetOutputPort());

  vtkSmartPointer<vtkActor> profileActor =
    vtkSmartPointer<vtkActor>::New();
  profileActor->SetMapper(profileMapper);
  profileActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

// Add the actors to the renderer, set the background and size
//
  renderer->AddActor(bottle);
  renderer->AddActor(profileActor);
  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());

  renWin->SetSize(640,480);
  renWin->Render();

  renderer->GetActiveCamera()->SetPosition(1, 0, 0);
  renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  renderer->GetActiveCamera()->SetViewUp(0, 0, 1);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);

//$cam1 SetClippingRange 3.95297 50
//$cam1 SetFocalPoint 9.71821 0.458166 29.3999
//$cam1 SetPosition 2.7439 -37.3196 38.7167
//$cam1 SetViewUp -0.16123 0.264271 0.950876

// render the image
//
  iren->Start();

  return EXIT_SUCCESS;
}
