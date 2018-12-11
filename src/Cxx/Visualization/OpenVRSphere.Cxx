#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderer.h>
#include <vtkOpenVRRenderWindowInteractor.h>
//Author: Chethana B
//Organisation: Virtual Environments Lab, Chung Ang University, Seoul, South Korea. 
int main(int, char *[])
{
  // Create a Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  
  //Create a Mapper

  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  
  //Create an Actor
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  //Create a Renderer, RenderWindow, RenderWindowInteractor
  vtkSmartPointer<vtkOpenVRRenderer> renderer = vtkSmartPointer<vtkOpenVRRenderer>::New();
  
  vtkSmartPointer<vtkOpenVRRenderWindow> renderWindow = vtkSmartPointer<vtkOpenVRRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  
  vtkSmartPointer<vtkOpenVRRenderWindowInteractor> renderWindowInteractor =  vtkSmartPointer<vtkOpenVRRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
