/**
  1. Create a cube and cone source.
  2. Render it with the cube in layer 0 and the cone in layer 1 of the render
  window.
  3. Interact with it.
  4. Notice that the cube and the cone are both visible and the layer 1
  background is transparent.
  5. Pressing '0' on the keyboard will let you manipulate the objects in
  layer 0.
  6. Pressing '1' on the keyboard will let you manipulate the objects in layer 1.
*/

#include <vtkActor.h>
#include <vtkCallbackCommand.h>
#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkInteractorObserver.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>

#include <array>
#include <cstdlib>
#include <iomanip>
#include <iostream>

namespace {
void KeypressCallbackFunction(vtkObject* caller, long unsigned int eventId,
                              void* clientData, void* callData);
} // namespace

int main(int argc, char* argv[])
{
  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkCubeSource> cubeSource;
  cubeSource->SetXLength(4.0);
  cubeSource->SetYLength(9.0);
  cubeSource->SetZLength(1.0);
  cubeSource->SetCenter(0.0, 0.0, 0.0);

  // Render the cube
  vtkNew<vtkPolyDataMapper> cubeMapper;
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

  vtkNew<vtkActor> cubeActor;
  cubeActor->GetProperty()->SetDiffuseColor(
      colors->GetColor3d("DarkGreen").GetData());
  cubeActor->SetMapper(cubeMapper);

  vtkNew<vtkConeSource> coneSource;
  coneSource->SetCenter(0.0, 0.0, 0.0);
  coneSource->SetHeight(1.0);
  coneSource->SetRadius(0.25);
  coneSource->SetDirection(0.0, 1.0, 0.0);
  coneSource->SetResolution(60);
  coneSource->CappingOn();

  // Render the cone
  vtkNew<vtkPolyDataMapper> coneMapper;
  coneMapper->SetInputConnection(coneSource->GetOutputPort());

  vtkNew<vtkActor> coneActor;
  coneActor->GetProperty()->SetDiffuseColor(
      colors->GetColor3d("DarkTurquoise").GetData());
  // Make the cone slightly transparent for fun
  coneActor->GetProperty()->SetOpacity(0.75);
  coneActor->SetMapper(coneMapper);

  // The renderers, render window and interactor
  std::array<vtkNew<vtkRenderer>, 2> renderers;
  vtkNew<vtkRenderWindow> renWin;
  for (auto&& ren : renderers)
  {
    renWin->AddRenderer(ren);
  }
  renWin->SetSize(800, 800);
  vtkNew<vtkRenderWindowInteractor> iren;
  iren->SetRenderWindow(renWin);

  // Layer 0 - background not transparent
  renderers[0]->SetBackground(colors->GetColor3d("Silver").GetData());
  renderers[0]->AddActor(cubeActor);
  renderers[0]->SetLayer(0);

  // Layer 1 - the background is transparent
  //           so we only see the layer 0 background color
  renderers[1]->AddActor(coneActor);
  renderers[1]->SetBackground(colors->GetColor3d("MidnightBlue").GetData());
  renderers[1]->SetLayer(1);

  // We have two layers
  renWin->SetNumberOfLayers(static_cast<int>(renderers.size()));
  renWin->Render();
  renWin->SetWindowName("TransparentBackground");
  renWin->StereoRenderOff();

  vtkNew<vtkCallbackCommand> keypressCallback;
  keypressCallback->SetCallback(KeypressCallbackFunction);
  iren->AddObserver(vtkCommand::KeyPressEvent, keypressCallback);

  // Interact with the data
  iren->Start();

  return EXIT_SUCCESS;
}

namespace {
void KeypressCallbackFunction(vtkObject* caller,
                              long unsigned int vtkNotUsed(eventId),
                              void* vtkNotUsed(clientData),
                              void* vtkNotUsed(callData))
{
  vtkRenderWindowInteractor* iren =
      static_cast<vtkRenderWindowInteractor*>(caller);
  vtkRendererCollection* renderers = iren->GetRenderWindow()->GetRenderers();
  if (renderers->GetNumberOfItems() < 2)
  {
    std::cerr << "We need at least two renderers, we have only "
              << renderers->GetNumberOfItems() << std::endl;
    return;
  }
  renderers->InitTraversal();
  // Top item
  vtkRenderer* ren0 = renderers->GetNextItem();
  // Bottom item
  vtkRenderer* ren1 = renderers->GetNextItem();

  std::string key = iren->GetKeySym();

  if (key == "0")
  {
    iren->GetRenderWindow()
        ->GetInteractor()
        ->GetInteractorStyle()
        ->SetDefaultRenderer(ren0);
    ren0->InteractiveOn();
    ren1->InteractiveOff();
  }
  if (key == "1")
  {
    iren->GetRenderWindow()
        ->GetInteractor()
        ->GetInteractorStyle()
        ->SetDefaultRenderer(ren1);
    ren0->InteractiveOff();
    ren1->InteractiveOn();
  }
}
} // namespace
