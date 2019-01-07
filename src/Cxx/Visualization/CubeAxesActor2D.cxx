#include <vtkNew.h>
#include <vtkPlatonicSolidSource.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataMapper.h>
#include <vtkLODActor.h>
#include <vtkOutlineFilter.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkTextProperty.h>
#include <vtkCubeAxesActor2D.h>

// The vtkCubeAxesActor2D draws axes on the bounding box of the data set and
// labels the axes with x-y-z coordinates.

//----------------------------------------------------------------------------//
int main(int, char *[])
{
  vtkNew<vtkPlatonicSolidSource> icosahedron;
  icosahedron->SetSolidTypeToIcosahedron();

  // Create a vtkPolyDataNormals filter to calculate the normals of the data set.
  vtkNew<vtkPolyDataNormals> normals;
  normals->SetInputConnection(icosahedron->GetOutputPort());

  // Set up the associated mapper and actor.
  vtkNew<vtkPolyDataMapper> icosahedron_mapper;
  icosahedron_mapper->SetInputConnection(normals->GetOutputPort());
  icosahedron_mapper->ScalarVisibilityOff();

  vtkNew<vtkLODActor> icosahedron_actor;
  icosahedron_actor->SetMapper(icosahedron_mapper.GetPointer());
  icosahedron_actor->GetProperty()->SetColor(0.8, .1, .9);

  // Create a vtkOutlineFilter to draw the bounding box of the data set.
  // Also create the associated mapper and actor.
  vtkNew<vtkOutlineFilter> outline;
  outline->SetInputConnection(normals->GetOutputPort());

  vtkNew<vtkPolyDataMapper> map_outline;
  map_outline->SetInputConnection(outline->GetOutputPort());

  vtkNew<vtkActor> outline_actor;
  outline_actor->SetMapper(map_outline.GetPointer());
  outline_actor->GetProperty()->SetColor(0., 0., 0.);

  // Create the Renderers.  Assign them the appropriate viewport
  // coordinates, active camera, and light.
  vtkNew<vtkRenderer> ren;
  ren->SetViewport(0, 0, 0.5, 1.0);
  // It is also possible to enhance the display with cameras.
  // ren->SetActiveCamera(camera);
  // ren->AddLight(light);

  vtkNew<vtkRenderer> ren2;
  ren2->SetViewport(0.5, 0, 1.0, 1.0);
  ren2->SetActiveCamera(ren->GetActiveCamera());
  // ren2->AddLight(light);

  // Create the RenderWindow and RenderWindowInteractor.
  vtkNew<vtkRenderWindow> renWin;
  renWin->AddRenderer(ren.GetPointer());
  renWin->AddRenderer(ren2.GetPointer());
  renWin->SetWindowName("VTK - Cube Axes");
  renWin->SetSize(600, 300);

  vtkNew<vtkRenderWindowInteractor> iren;
  iren->SetRenderWindow(renWin.GetPointer());

  // Add the actors to the renderer, and set the background.
  ren->AddViewProp(icosahedron_actor.GetPointer());
  ren->AddViewProp(outline_actor.GetPointer());
  ren2->AddViewProp(icosahedron_actor.GetPointer());
  ren2->AddViewProp(outline_actor.GetPointer());

  ren->SetBackground(0.1, 0.2, 0.4);
  ren2->SetBackground(0.1, 0.2, 0.4);

  // Create a text property for both cube axes
  vtkNew<vtkTextProperty> tprop;
  tprop->SetColor(1, 1, 1);
  tprop->ShadowOn();
  tprop->SetFontSize(20);

  // Create a vtkCubeAxesActor2D.  Use the outer edges of the bounding box to
  // draw the axes.  Add the actor to the renderer.
  vtkNew<vtkCubeAxesActor2D> axes;
  axes->SetInputConnection(normals->GetOutputPort());
  axes->SetCamera(ren->GetActiveCamera());
  axes->SetLabelFormat("%6.4g");
  axes->SetFlyModeToOuterEdges();
  axes->SetAxisTitleTextProperty(tprop.GetPointer());
  axes->SetAxisLabelTextProperty(tprop.GetPointer());
  ren->AddViewProp(axes.GetPointer());

  // Create a vtkCubeAxesActor2D.  Use the closest vertex to the camera to
  // determine where to draw the axes.  Add the actor to the renderer.
  vtkNew<vtkCubeAxesActor2D> axes2;
  axes2->SetViewProp(icosahedron_actor.GetPointer());
  axes2->SetCamera(ren2->GetActiveCamera());
  axes2->SetLabelFormat("%6.4g");
  axes2->SetFlyModeToClosestTriad();
  axes2->ScalingOff();
  axes2->SetAxisTitleTextProperty(tprop.GetPointer());
  axes2->SetAxisLabelTextProperty(tprop.GetPointer());
  ren2->AddViewProp(axes2.GetPointer());

  ren->ResetCamera();
  iren->Initialize();
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
