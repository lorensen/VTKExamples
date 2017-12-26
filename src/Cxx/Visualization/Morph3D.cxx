#include <vtkCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkContourFilter.h>
#include <vtkInterpolateDataSetAttributes.h>
#include <vtkImplicitModeller.h>
#include <vtkVectorText.h>
#include <vtkProperty.h>

#include <vtkNamedColors.h>
#include <vtksys/SystemTools.hxx>

int main (int argc, char *argv[])
{
  double t = 2.0;
  if (argc > 1)
  {
    t = atof(argv[1]);
  }

// make the letter v
  vtkSmartPointer<vtkVectorText> letterV =
    vtkSmartPointer<vtkVectorText>::New();
  letterV->SetText("v");

// read the geometry file containing the letter t
  vtkSmartPointer<vtkVectorText> letterT =
    vtkSmartPointer<vtkVectorText>::New();
  letterT->SetText("t");

// read the geometry file containing the letter k
  vtkSmartPointer<vtkVectorText> letterK =
    vtkSmartPointer<vtkVectorText>::New();
  letterK->SetText("k");
    
// create implicit models of each letter
  vtkSmartPointer<vtkImplicitModeller> blobbyV =
    vtkSmartPointer<vtkImplicitModeller>::New();
  blobbyV->SetInputConnection(letterV->GetOutputPort());
  blobbyV->SetMaximumDistance(.2);
  blobbyV->SetSampleDimensions(50, 50, 12);
  blobbyV->SetModelBounds(-0.5, 1.5, -0.5, 1.5, -0.5, 0.5);

  vtkSmartPointer<vtkImplicitModeller> blobbyT =
    vtkSmartPointer<vtkImplicitModeller>::New();
  blobbyT->SetInputConnection(letterT->GetOutputPort());
  blobbyT->SetMaximumDistance(.2);
  blobbyT->SetSampleDimensions(50, 50, 12);
  blobbyT->SetModelBounds(-0.5, 1.5, -0.5, 1.5, -0.5, 0.5);

  vtkSmartPointer<vtkImplicitModeller> blobbyK =
    vtkSmartPointer<vtkImplicitModeller>::New();
  blobbyK->SetInputConnection(letterK->GetOutputPort());
  blobbyK->SetMaximumDistance(.2);
  blobbyK->SetSampleDimensions(50, 50, 12);
  blobbyK->SetModelBounds(-0.5, 1.5, -0.5, 1.5, -0.5, 0.5);

// Interpolate the data
  vtkSmartPointer<vtkInterpolateDataSetAttributes> interpolate =
    vtkSmartPointer<vtkInterpolateDataSetAttributes>::New();
  interpolate->AddInputConnection(blobbyV->GetOutputPort());
  interpolate->AddInputConnection(blobbyT->GetOutputPort());
  interpolate->AddInputConnection(blobbyK->GetOutputPort());
  interpolate->SetT(0.0);

// extract an iso surface
  vtkSmartPointer<vtkContourFilter> blobbyIso =
    vtkSmartPointer<vtkContourFilter>::New();
  blobbyIso->SetInputConnection(interpolate->GetOutputPort());
  blobbyIso->SetValue(0, 0.1);

// map to rendering primitives
  vtkSmartPointer<vtkPolyDataMapper> blobbyMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  blobbyMapper->SetInputConnection(blobbyIso->GetOutputPort());
  blobbyMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

// now an actor
  vtkSmartPointer<vtkActor> blobby =
    vtkSmartPointer<vtkActor>::New();
  blobby->SetMapper(blobbyMapper);
  blobby->GetProperty()->SetDiffuseColor(colors->GetColor3d("Banana").GetData());
  blobby->GetProperty()->EdgeVisibilityOn();

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

  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  camera->SetClippingRange(0.265,13.2);
  camera->SetFocalPoint(0.539, 0.47464, 0);
  camera->SetPosition(0.539, 0.474674, 2.644);
  camera->SetViewUp(0, 1, 0);
  camera->Azimuth(30.);
  camera->Elevation(30.);
  renderer->SetActiveCamera(camera);

//  now  make a renderer and tell it about lights and actors
  renderWindow->SetSize(640,480);

  renderer->AddActor(blobby);
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renderWindow->Render();
  for (unsigned i = 0; i < 100; ++i)
  {
    interpolate->SetT(i / 99.0 * 2.0);
    interpolate->Modified();
    renderWindow->Render();
    vtksys::SystemTools::Delay(100);
  }
  interpolate->SetT(t);
  renderWindow->Render();

// interact
  interactor->Start();
  return EXIT_SUCCESS;
  }
