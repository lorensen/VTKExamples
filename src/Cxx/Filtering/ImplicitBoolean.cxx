#include <vtkSmartPointer.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkImplicitBoolean.h>
#include <vtkSphere.h>

#include <vtkNamedColors.h>
#include <vtkColor.h>
 
int main (int, char *[])
{
  // Define colors
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkColor3d background = colors->GetColor3d("SlateGray");
  vtkColor3d actorColor = colors->GetColor3d("hot_pink");

  vtkSmartPointer<vtkSphere> sphere1 = 
    vtkSmartPointer<vtkSphere>::New();
  sphere1->SetCenter(.9,0,0);
  vtkSmartPointer<vtkSphere> sphere2 = 
    vtkSmartPointer<vtkSphere>::New();
  sphere2->SetCenter(-.9,0,0);
 
  vtkSmartPointer<vtkImplicitBoolean> implicitBoolean =
    vtkSmartPointer<vtkImplicitBoolean>::New();
  implicitBoolean->AddFunction(sphere1);
  implicitBoolean->AddFunction(sphere2);
  implicitBoolean->SetOperationTypeToUnion();

//  implicitBoolean->SetOperationTypeToIntersection();
//  implicitBoolean->SetOperationTypeToDifference();
  
  // Sample the function
  vtkSmartPointer<vtkSampleFunction> sample = 
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(50,50,50);
  sample->SetImplicitFunction(implicitBoolean);
  double value = 3.0;
  double xmin = -value, xmax = value,
    ymin = -value, ymax = value,
    zmin = -value, zmax = value;
  sample->SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax);
 
  // Create the 0 isosurface
  vtkSmartPointer<vtkContourFilter> contours = 
    vtkSmartPointer<vtkContourFilter>::New();
  contours->SetInputConnection(sample->GetOutputPort());
  contours->GenerateValues(1, 1, 1);
 
  // Map the contours to graphical primitives
  vtkSmartPointer<vtkPolyDataMapper> contourMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contours->GetOutputPort());
  contourMapper->ScalarVisibilityOff();
 
  // Create an actor for the contours
  vtkSmartPointer<vtkActor> contourActor = 
    vtkSmartPointer<vtkActor>::New();
  contourActor->SetMapper(contourMapper);
  contourActor->GetProperty()->SetDiffuseColor(actorColor.GetData()); 
  contourActor->GetProperty()->SetDiffuse(.8);
  contourActor->GetProperty()->SetSpecular(.2);
  contourActor->GetProperty()->SetSpecularPower(60.0);

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(contourActor);
  renderer->SetBackground(background.GetData());
 
  renderWindow->Render();
  interactor->Start();
 
  return EXIT_SUCCESS;
}
