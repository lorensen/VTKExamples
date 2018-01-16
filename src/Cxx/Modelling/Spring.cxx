#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRotationalExtrusionFilter.h>

int main (int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

// Create the RenderWindow, Renderer and both Actors
//
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

// create spring profile (a circle)
//
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertPoint(0, 1.0, 0.0, 0.0);
  points->InsertPoint(1, 1.0732, 0.0, -0.1768);
  points->InsertPoint(2, 1.25, 0.0, -0.25);
  points->InsertPoint(3, 1.4268, 0.0, -0.1768);
  points->InsertPoint(4, 1.5, 0.0, 0.00);
  points->InsertPoint(5, 1.4268, 0.0, 0.1768);
  points->InsertPoint(6, 1.25, 0.0, 0.25);
  points->InsertPoint(7, 1.0732, 0.0, 0.1768);

  vtkSmartPointer<vtkCellArray> poly =
    vtkSmartPointer<vtkCellArray>::New();
  poly->InsertNextCell(8);//number of points
  poly->InsertCellPoint(0);
  poly->InsertCellPoint(1);
  poly->InsertCellPoint(2);
  poly->InsertCellPoint(3);
  poly->InsertCellPoint(4);
  poly->InsertCellPoint(5);
  poly->InsertCellPoint(6);
  poly->InsertCellPoint(7);

  vtkSmartPointer<vtkPolyData> profile =
    vtkSmartPointer<vtkPolyData>::New();
  profile->SetPoints(points);
  profile->SetPolys(poly);

// extrude profile to make spring
//
  vtkSmartPointer<vtkRotationalExtrusionFilter> extrude =
    vtkSmartPointer<vtkRotationalExtrusionFilter>::New();
  extrude->SetInputData(profile);
  extrude->SetResolution(360);
  extrude->SetTranslation(6);
  extrude->SetDeltaRadius(1.0);
  extrude->SetAngle(2160.0);//six revolutions
    
  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputConnection(extrude->GetOutputPort());
  normals->SetFeatureAngle(60);

  vtkSmartPointer<vtkPolyDataMapper> map =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  map->SetInputConnection(normals->GetOutputPort());

  vtkSmartPointer<vtkActor> spring =
    vtkSmartPointer<vtkActor>::New();
  spring->SetMapper(map);
  spring->GetProperty()->SetColor(colors->GetColor3d("PowderBlue").GetData());
  spring->GetProperty()->SetDiffuse(0.7);
  spring->GetProperty()->SetSpecular(0.4);
  spring->GetProperty()->SetSpecularPower(20);
  spring->GetProperty()->BackfaceCullingOn();

// Add the actors to the renderer, set the background and size
//
  renderer->AddActor(spring);
  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());
  renderWindow->SetSize(640, 512);

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(90);

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
