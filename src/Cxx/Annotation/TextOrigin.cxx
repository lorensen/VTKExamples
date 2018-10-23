// This example demonstrates the use of vtkVectorText and vtkFollower.
// vtkVectorText is used to create 3D annotation.  vtkFollower is used to
// position the 3D text and to ensure that the text always faces the
// renderer's active camera (i.e., the text is always readable).

#include <vtkSmartPointer.h>
#include <vtkAxes.h>
#include <vtkFollower.h>
#include <vtkVectorText.h>

#include <vtkNamedColors.h>
#include <vtkCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main (int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

// Create the axes and the associated mapper and actor.
  vtkSmartPointer<vtkAxes> axes =
    vtkSmartPointer<vtkAxes>::New();
  axes->SetOrigin(0, 0, 0);
  vtkSmartPointer<vtkPolyDataMapper> axesMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  axesMapper->SetInputConnection(axes->GetOutputPort());
  vtkSmartPointer<vtkActor> axesActor =
    vtkSmartPointer<vtkActor>::New();
  axesActor->SetMapper(axesMapper);

// Create the 3D text and the associated mapper and follower (a type of
// actor).  Position the text so it is displayed over the origin of the
// axes.
  vtkSmartPointer<vtkVectorText> atext =
    vtkSmartPointer<vtkVectorText>::New();
  atext->SetText("Origin");
  vtkSmartPointer<vtkPolyDataMapper> textMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  textMapper->SetInputConnection(atext->GetOutputPort());
  vtkSmartPointer<vtkFollower> textActor =
    vtkSmartPointer<vtkFollower>::New();
  textActor->SetMapper(textMapper);
  textActor->SetScale(0.2, 0.2, 0.2);
  textActor->AddPosition(0, -0.1, 0);

// Create the Renderer, RenderWindow, and RenderWindowInteractor.
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  interactor->SetInteractorStyle( style );

// Add the actors to the renderer.
  renderer->AddActor(axesActor);
  renderer->AddActor(textActor);

  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

// Zoom in closer.
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(1.6);

  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

// Reset the clipping range of the camera; set the camera of the
// follower; render.
  renderer->ResetCameraClippingRange();
  textActor->SetCamera(renderer->GetActiveCamera());

  interactor->Initialize();
  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}

