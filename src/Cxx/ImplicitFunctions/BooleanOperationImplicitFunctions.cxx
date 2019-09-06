#include <vtkSphere.h>
#include <vtkBox.h>
#include <vtkImplicitBoolean.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkColor.h>

int main(int argc, char *argv[])
{
  // Define colors
  auto colors =
  	vtkSmartPointer<vtkNamedColors>::New();
  vtkColor3d actorColor = colors->GetColor3d("AliceBlue");
  vtkColor3d  EdgeColour = colors->GetColor3d("SteelBlue");
  vtkColor3d BackgroundColour = colors->GetColor3d("Silver");
  
  // create a sphere
  auto sphere =
  	vtkSmartPointer<vtkSphere>::New();
  sphere->SetCenter(1.0, 0.0, 0.0);
  sphere->SetRadius(1);
  
  //create a box
  auto box =
  	vtkSmartPointer<vtkBox>::New();
  box->SetBounds(-1, 1, -1, 1, -1, 1);
  
  // combine the two implicit functions
  auto boolean =
  	vtkSmartPointer<vtkImplicitBoolean>::New();
  boolean->SetOperationTypeToDifference();
  // boolean->SetOperationTypeToUnion()
  // boolean->SetOperationTypeToIntersection()
  boolean->AddFunction(box);
  boolean->AddFunction(sphere);
  //The sample function generates a distance function from the implicit
  //function.This is then contoured to get a polygonal surface.
  auto sample =
  	vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetImplicitFunction(boolean);
  sample->SetModelBounds(-1, 2, -1, 1, -1, 1);
  sample->SetSampleDimensions(40, 40, 40);
  sample->ComputeNormalsOff();
  
  // contour
  auto surface =
  	vtkSmartPointer<vtkContourFilter>::New();
  surface->SetInputConnection(sample->GetOutputPort());
  surface->SetValue(0, 0.0);
  
  //Create a mapper and an actor
  auto mapper =
  	vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(surface->GetOutputPort());
  mapper->ScalarVisibilityOff();
  auto actor =
  	vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->EdgeVisibilityOn();
  actor->GetProperty()->SetColor(actorColor.GetData());
  actor->GetProperty()->SetEdgeColor(EdgeColour.GetData());
    
  // A renderer and render window
  auto renderer =
  	vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(BackgroundColour.GetData());
  auto renderWindow =
  	vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  auto renderWindowInteractor =
  	vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  //add the actor
  renderer->AddActor(actor);
  // Start
  renderer->GetActiveCamera()->SetPosition(5.0, -4.0, 1.6);
  renderer->GetActiveCamera()->SetViewUp(0.1, 0.5, 0.9);
  renderer->GetActiveCamera()->SetDistance(6.7);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
