#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter ( 0.0, 0.0, 0.0 );
  sphereSource->SetRadius ( 5.0 );
  sphereSource->Update();

  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData ( sphereSource->GetOutput() );

  // Create an actor
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper ( mapper );

  // Create a renderer
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground ( 1, 1, 1 ); // Set background color to white
  renderer->AddActor ( actor );

  // Create a render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer ( renderer );

  // Create an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow ( renderWindow );

  // Setup the text and add it to the renderer
  vtkSmartPointer<vtkTextActor> textActor = 
    vtkSmartPointer<vtkTextActor>::New();
  textActor->SetInput ( "Hello world" );
  textActor->SetPosition2 ( 10, 40 );
  textActor->GetTextProperty()->SetFontSize ( 24 );
  textActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
  renderer->AddActor2D ( textActor );
  
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
