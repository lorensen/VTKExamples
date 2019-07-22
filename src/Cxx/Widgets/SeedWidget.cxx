#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSeedWidget.h>
#include <vtkSeedRepresentation.h>
#include <vtkPointHandleRepresentation2D.h>
#include <vtkProperty2D.h> // For setting the color in the handles

int main( int vtkNotUsed( argc ), char* vtkNotUsed( argv )[] )
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> window =
    vtkSmartPointer<vtkRenderWindow>::New();
  window->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow( window );

  // Create the representation for the seed widget and for its handles
  vtkSmartPointer<vtkPointHandleRepresentation2D> handleRep =
    vtkSmartPointer<vtkPointHandleRepresentation2D>::New();
  handleRep->GetProperty()->SetColor( 1, 1, 0 ); // Make the handles yellow
  vtkSmartPointer<vtkSeedRepresentation> widgetRep =
    vtkSmartPointer<vtkSeedRepresentation>::New();
  widgetRep->SetHandleRepresentation( handleRep );

  // Create the seed widget
  vtkSmartPointer<vtkSeedWidget> seedWidget =
    vtkSmartPointer<vtkSeedWidget>::New();
  seedWidget->SetInteractor( interactor );
  seedWidget->SetRepresentation( widgetRep );

  seedWidget->On();
  window->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
