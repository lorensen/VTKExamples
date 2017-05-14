#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkReflectionFilter.h>
#include <vtkPolyData.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkConeSource> coneSource = 
    vtkSmartPointer<vtkConeSource>::New();
  coneSource->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> coneMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection(coneSource->GetOutputPort());
  vtkSmartPointer<vtkActor> coneActor = 
      vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMapper);
  coneActor->GetProperty()->SetColor(0.0, 1.0, 0.0); //(R,G,B)
  
  // Reflection
  vtkSmartPointer<vtkReflectionFilter> reflectionFilter = 
    vtkSmartPointer<vtkReflectionFilter>::New();
  reflectionFilter->SetInputConnection(coneSource->GetOutputPort());
  reflectionFilter->CopyInputOff();
  reflectionFilter->Update();
  
  vtkSmartPointer<vtkDataSetMapper> reflectionMapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
  reflectionMapper->SetInputConnection(reflectionFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> reflectionActor = 
    vtkSmartPointer<vtkActor>::New();
  reflectionActor->SetMapper(reflectionMapper);
  reflectionActor->GetProperty()->SetColor(1.0, 0.0, 0.0); //(R,G,B)
  
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  // Add the actor to the scene
  renderer->AddActor(coneActor);
  renderer->AddActor(reflectionActor);
  renderer->SetBackground(1,1,1); // Background color white
 
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
