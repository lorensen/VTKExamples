#include <vtkSmartPointer.h>
// For the rendering pipeline setup:
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
// For vtkBoxWidget2:
#include <vtkBoxWidget2.h>
#include <vtkBoxRepresentation.h>
#include <vtkCommand.h>
#include <vtkTransform.h>

class vtkBoxCallback : public vtkCommand
{
public:
  static vtkBoxCallback *New()
  {
    return new vtkBoxCallback;
  }

  vtkSmartPointer<vtkActor> m_actor;

  void SetActor( vtkSmartPointer<vtkActor> actor )
  {
    m_actor = actor;
  }

  virtual void Execute( vtkObject *caller, unsigned long, void* )
  {
    vtkSmartPointer<vtkBoxWidget2> boxWidget =
      dynamic_cast<vtkBoxWidget2*>(caller);

    vtkSmartPointer<vtkTransform> t =
      vtkSmartPointer<vtkTransform>::New();

    dynamic_cast<vtkBoxRepresentation*>( boxWidget->GetRepresentation() )->GetTransform( t );
    this->m_actor->SetUserTransform( t );
  }

  vtkBoxCallback(){}
};

int main( int vtkNotUsed( argc ), char* vtkNotUsed( argv )[] )
{
  vtkSmartPointer<vtkConeSource> coneSource =
    vtkSmartPointer<vtkConeSource>::New();
  coneSource->SetHeight( 1.5 );

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection( coneSource->GetOutputPort() );

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper( mapper );

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera(); // Reposition camera so the whole scene is visible

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow( renderWindow );

  // Use the "trackball camera" interactor style, rather than the default "joystick camera"
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  renderWindowInteractor->SetInteractorStyle( style );

  vtkSmartPointer<vtkBoxWidget2> boxWidget =
    vtkSmartPointer<vtkBoxWidget2>::New();
  boxWidget->SetInteractor( renderWindowInteractor );
  boxWidget->GetRepresentation()->SetPlaceFactor( 1 ); // Default is 0.5
  boxWidget->GetRepresentation()->PlaceWidget(actor->GetBounds());
  
  // Set up a callback for the interactor to call so we can manipulate the actor
  vtkSmartPointer<vtkBoxCallback> boxCallback =
    vtkSmartPointer<vtkBoxCallback>::New();
  boxCallback->SetActor(actor);
  boxWidget->AddObserver( vtkCommand::InteractionEvent, boxCallback );

  boxWidget->On();

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
