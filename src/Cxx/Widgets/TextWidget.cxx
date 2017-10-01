#include <vtkSmartPointer.h>
#include <vtkTextWidget.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkTextRepresentation.h>
#include <vtkCoordinate.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>

int main(int, char *[])
{
  // Create the RenderWindow, Renderer and both Actors
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Create a test pipeline
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create the widget
  vtkSmartPointer<vtkTextActor> textActor =
    vtkSmartPointer<vtkTextActor>::New();
  textActor->SetInput("This is a test");
  textActor->GetTextProperty()->SetColor( 0.0, 1.0, 0.0 );

  vtkSmartPointer<vtkTextWidget> textWidget =
    vtkSmartPointer<vtkTextWidget>::New();

  vtkSmartPointer<vtkTextRepresentation> textRepresentation =
    vtkSmartPointer<vtkTextRepresentation>::New();
  textRepresentation->GetPositionCoordinate()->SetValue( .15, .15 );
  textRepresentation->GetPosition2Coordinate()->SetValue( .7, .2 );
  textWidget ->SetRepresentation( textRepresentation );

  textWidget->SetInteractor(interactor);
  textWidget->SetTextActor(textActor);
  textWidget->SelectableOff();

  // Add the actors to the renderer, set the background and size
  renderer->AddActor(actor);
  renderer->SetBackground(0.1, 0.2, 0.4);
  renderWindow->SetSize(300, 300);

  interactor->Initialize();
  renderWindow->Render();
  textWidget->On();
  renderWindow->Render();

  interactor->Start();
  
  return EXIT_SUCCESS;

}
