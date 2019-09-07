#include <vtkQuadric.h>
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

#include <cstdlib>

int main(int argc, char *argv[])
{
  // Define colors
  auto colors =
  	vtkSmartPointer<vtkNamedColors>::New();
  vtkColor3d actorColor = colors->GetColor3d("AliceBlue");
  vtkColor3d  EdgeColour = colors->GetColor3d("SteelBlue");
  vtkColor3d BackgroundColour = colors->GetColor3d("Silver");
  
  // create a Quadric
  auto quadric = vtkSmartPointer<vtkQuadric>::New();
  quadric->SetCoefficients(0.5, 1, 0.2, 0, 0.1, 0, 0, 0.2, 0, 0);
     
   /*The sample function generates a distance function from the implicit
  	 function.This is then contoured to get a polygonal surface.*/
  auto sample =
  	vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetImplicitFunction(quadric);
  sample->SetModelBounds(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5);
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
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
