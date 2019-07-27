/*
This code is based on the VTK file: Examples/Modelling/Tcl/DelMesh.py.

This example demonstrates how to use 2D Delaunay triangulation.
We create a fancy image of a 2D Delaunay triangulation. Points are
 randomly generated.
*/

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDelaunay2D.h>
#include <vtkExtractEdges.h>
#include <vtkGlyph3D.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkTubeFilter.h>

int main(int, char*[])
{
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  // Generate some "random" points.
  auto points = vtkSmartPointer<vtkPoints>::New();
  auto randomSequence =
      vtkSmartPointer<vtkMinimalStandardRandomSequence>::New();
  randomSequence->SetSeed(1);
  for (auto i = 0; i < 50; ++i)
  {
    double p1;
    double p2;
    p1 = randomSequence->GetValue();
    randomSequence->Next();
    p2 = randomSequence->GetValue();
    randomSequence->Next();
    points->InsertPoint(i, p1, p2, 0.0);
  }
  // Create a polydata with the points we just created.
  auto profile = vtkSmartPointer<vtkPolyData>::New();
  profile->SetPoints(points);

  // Perform a 2D Delaunay triangulation on them.
  auto delny = vtkSmartPointer<vtkDelaunay2D>::New();
  delny->SetInputData(profile);
  delny->SetTolerance(0.001);
  auto mapMesh = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapMesh->SetInputConnection(delny->GetOutputPort());
  auto meshActor = vtkSmartPointer<vtkActor>::New();
  meshActor->SetMapper(mapMesh);
  meshActor->GetProperty()->SetColor(
      colors->GetColor3d("MidnightBlue").GetData());

  // We will now create a nice looking mesh by wrapping the edges in tubes,
  // and putting fat spheres at the points.
  auto extract = vtkSmartPointer<vtkExtractEdges>::New();
  extract->SetInputConnection(delny->GetOutputPort());
  auto tubes = vtkSmartPointer<vtkTubeFilter>::New();
  tubes->SetInputConnection(extract->GetOutputPort());
  tubes->SetRadius(0.01);
  tubes->SetNumberOfSides(6);
  auto mapEdges = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapEdges->SetInputConnection(tubes->GetOutputPort());
  auto edgeActor = vtkSmartPointer<vtkActor>::New();
  edgeActor->SetMapper(mapEdges);
  edgeActor->GetProperty()->SetColor(colors->GetColor3d("peacock").GetData());
  edgeActor->GetProperty()->SetSpecularColor(1, 1, 1);
  edgeActor->GetProperty()->SetSpecular(0.3);
  edgeActor->GetProperty()->SetSpecularPower(20);
  edgeActor->GetProperty()->SetAmbient(0.2);
  edgeActor->GetProperty()->SetDiffuse(0.8);

  auto ball = vtkSmartPointer<vtkSphereSource>::New();
  ball->SetRadius(0.025);
  ball->SetThetaResolution(12);
  ball->SetPhiResolution(12);
  auto balls = vtkSmartPointer<vtkGlyph3D>::New();
  balls->SetInputConnection(delny->GetOutputPort());
  balls->SetSourceConnection(ball->GetOutputPort());
  auto mapBalls = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBalls->SetInputConnection(balls->GetOutputPort());
  auto ballActor = vtkSmartPointer<vtkActor>::New();
  ballActor->SetMapper(mapBalls);
  ballActor->GetProperty()->SetColor(colors->GetColor3d("hot_pink").GetData());
  ballActor->GetProperty()->SetSpecularColor(1, 1, 1);
  ballActor->GetProperty()->SetSpecular(0.3);
  ballActor->GetProperty()->SetSpecularPower(20);
  ballActor->GetProperty()->SetAmbient(0.2);
  ballActor->GetProperty()->SetDiffuse(0.8);

  // Create the rendering window, renderer, and interactive renderer.
  auto ren = vtkSmartPointer<vtkRenderer>::New();
  auto renWin = vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  auto iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer, set the background and size.
  ren->AddActor(ballActor);
  ren->AddActor(edgeActor);
  ren->SetBackground(colors->GetColor3d("AliceBlue").GetData());
  renWin->SetSize(512, 512);

  ren->ResetCamera();
  ren->GetActiveCamera()->Zoom(1.3);

  // Interact with the data.
  iren->Initialize();
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
