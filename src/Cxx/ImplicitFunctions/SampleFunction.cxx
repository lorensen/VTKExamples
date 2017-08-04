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

#include <vtkSuperquadric.h>
#include <vtkNamedColors.h>

int main (int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkSuperquadric> implicitFunction = 
    vtkSmartPointer<vtkSuperquadric>::New();
  implicitFunction->SetPhiRoundness(2.5);
  implicitFunction->SetThetaRoundness(.5);
  
  // Sample the function
  vtkSmartPointer<vtkSampleFunction> sample = 
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(50,50,50);
  sample->SetImplicitFunction(implicitFunction);
  double value = 2.0;
  double xmin = -value, xmax = value, ymin = -value, ymax = value, zmin = -value, zmax = value;
  sample->SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax);
    
  // Create the 0 isosurface
  vtkSmartPointer<vtkContourFilter> contours = 
    vtkSmartPointer<vtkContourFilter>::New();
  contours->SetInputConnection(sample->GetOutputPort());
  contours->GenerateValues(1, 2.0, 2.0);
  
  // Map the contours to graphical primitives
  vtkSmartPointer<vtkPolyDataMapper> contourMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contours->GetOutputPort());
  contourMapper->SetScalarRange(0.0, 1.2);
  
  // Create an actor for the contours
  vtkSmartPointer<vtkActor> contourActor = 
    vtkSmartPointer<vtkActor>::New();
  contourActor->SetMapper(contourMapper);
  
  // -- create a box around the function to indicate the sampling volume --
  
  // Create outline
  vtkSmartPointer<vtkOutlineFilter> outline = 
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(sample->GetOutputPort());
  
  // Map it to graphics primitives
  vtkSmartPointer<vtkPolyDataMapper> outlineMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());
  
  // Create an actor for it
  vtkSmartPointer<vtkActor> outlineActor = 
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(0,0,0);
  
  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  
  renderer->AddActor(contourActor);
  renderer->AddActor(outlineActor);
  renderer->SetBackground(colors->GetColor3d("Tan").GetData());
  
  renderWindow->Render();
  interactor->Start();
    
  return EXIT_SUCCESS;
}
