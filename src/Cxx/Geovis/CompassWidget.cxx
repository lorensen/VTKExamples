#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkCompassWidget.h>
#include <vtkCompassRepresentation.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleTrackball.h>

int main (int, char *[])
{

  //sphere 1
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(4.0);
    
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  // a renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  
  // Create the widget and its representation
  vtkSmartPointer<vtkCompassRepresentation> compassRepresentation = vtkSmartPointer<vtkCompassRepresentation>::New();
  
  vtkSmartPointer<vtkCompassWidget> compassWidget = 
    vtkSmartPointer<vtkCompassWidget>::New();
  compassWidget->SetInteractor(renderWindowInteractor);
  compassWidget->SetRepresentation(compassRepresentation);
  
  // add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white
  renderWindow->Render();
  compassWidget->EnabledOn();
      
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
      vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();   
  renderWindowInteractor->SetInteractorStyle( style );
  
  // begin interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
