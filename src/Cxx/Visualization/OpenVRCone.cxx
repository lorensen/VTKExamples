#include <vtkConeSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderer.h>
#include <vtkOpenVRRenderWindowInteractor.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
// Chethana B 
// Organisation: Virtual Environments Lab, Chung-Ang Univeristy, Seoul. 
int main(int, char *[])
{
  //Create a cone
  vtkSmartPointer<vtkConeSource> coneSource =    vtkSmartPointer<vtkConeSource>::New();
  coneSource->Update();

  //Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(coneSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkOpenVRRenderer> renderer =    vtkSmartPointer<vtkOpenVRRenderer>::New();
  vtkSmartPointer<vtkOpenVRRenderWindow> renderWindow =    vtkSmartPointer<vtkOpenVRRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkOpenVRRenderWindowInteractor> renderWindowInteractor =    vtkSmartPointer<vtkOpenVRRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
