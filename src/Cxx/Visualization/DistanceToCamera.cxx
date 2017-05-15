#include <vtkActor.h>
#include <vtkArrowSource.h>
#include <vtkDistanceToCamera.h>
#include <vtkGlyph3D.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPointSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

int main(int, char*[])
{
  //---------------------------------------------------------------------------
  // Draw some arrows that maintain a fixed size during zooming.

  // Create a set of points.
  vtkSmartPointer<vtkPointSource> fixedPointSource = vtkSmartPointer<
    vtkPointSource>::New();
  fixedPointSource->SetNumberOfPoints(2);

  // Calculate the distance to the camera of each point.
  vtkSmartPointer<vtkDistanceToCamera> distanceToCamera = vtkSmartPointer<
    vtkDistanceToCamera>::New();
  distanceToCamera->SetInputConnection(fixedPointSource->GetOutputPort());
  distanceToCamera->SetScreenSize(100.0);

  // Glyph each point with an arrow.
  vtkSmartPointer<vtkArrowSource> arrow =
    vtkSmartPointer<vtkArrowSource>::New();
  vtkSmartPointer<vtkGlyph3D> fixedGlyph = vtkSmartPointer<vtkGlyph3D>::New();
  fixedGlyph->SetInputConnection(distanceToCamera->GetOutputPort());
  fixedGlyph->SetSourceConnection(arrow->GetOutputPort());

  // Scale each point.
  fixedGlyph->SetScaleModeToScaleByScalar();
  fixedGlyph->SetInputArrayToProcess(0, 0, 0,
    vtkDataObject::FIELD_ASSOCIATION_POINTS, "DistanceToCamera");

  // Create a mapper.
  vtkSmartPointer<vtkPolyDataMapper> fixedMapper = vtkSmartPointer<
    vtkPolyDataMapper>::New();
  fixedMapper->SetInputConnection(fixedGlyph->GetOutputPort());
  fixedMapper->SetScalarVisibility(false);

  // Create an actor.
  vtkSmartPointer<vtkActor> fixedActor = vtkSmartPointer<vtkActor>::New();
  fixedActor->SetMapper(fixedMapper);
  fixedActor->GetProperty()->SetColor(0, 1, 1);

  //---------------------------------------------------------------------------
  // Draw some spheres that get bigger when zooming in.
  // Create a set of points.
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(4);

  // Glyph each point with a sphere.
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  vtkSmartPointer<vtkGlyph3D> glyph = vtkSmartPointer<vtkGlyph3D>::New();
  glyph->SetInputConnection(pointSource->GetOutputPort());
  glyph->SetSourceConnection(sphere->GetOutputPort());
  glyph->SetScaleFactor(0.1);

  // Create a mapper.
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyph->GetOutputPort());
  mapper->SetScalarVisibility(false);

  // Create an actor.
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(1, 1, 0);

  //---------------------------------------------------------------------------

  // A renderer and render window.
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(1, 1, 1); // Background color white
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<
    vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Give DistanceToCamera a pointer to the renderer.
  distanceToCamera->SetRenderer(renderer);

  // Add the actors to the scene.
  renderer->AddActor(fixedActor);
  renderer->AddActor(actor);

  // An interactor.
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<
    vtkInteractorStyleTrackballCamera>::New();
  renderWindowInteractor->SetInteractorStyle(style);
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Render an image (lights and cameras are created automatically).
  renderWindow->Render();

  // Begin mouse interaction.
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
