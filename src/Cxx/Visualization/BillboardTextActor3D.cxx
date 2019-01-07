#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkBillboardTextActor3D.h>
#include <vtkTextProperty.h>
#include <vtkCallbackCommand.h>
#include <vtkMath.h>
#include <sstream>

void ActorCallback( vtkObject* caller,
                      long unsigned int vtkNotUsed(eventId),
                      void* clientData,
                      void* vtkNotUsed(callData) )
{
  vtkSmartPointer<vtkBillboardTextActor3D> textActor = 
    static_cast<vtkBillboardTextActor3D *>(clientData);
  vtkSmartPointer<vtkActor> actor = 
    static_cast<vtkActor *>(caller);
  std::ostringstream label;
  label << std::setprecision(3)
        << actor->GetPosition()[0] << ", "
       << actor->GetPosition()[1] << ", "
       << actor->GetPosition()[2] << std::endl;
  textActor->SetPosition(actor->GetPosition());
  textActor->SetInput(label.str().c_str());
}

int main(int, char *[])
{
  // For testing
  vtkMath::RandomSeed(8775070);

  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter ( 0.0, 0.0, 0.0 );
  sphereSource->SetRadius ( 1.0 );

  // Create an actor
  vtkSmartPointer<vtkPolyDataMapper> mapper2 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper2->SetInputConnection ( sphereSource->GetOutputPort() );
  vtkSmartPointer<vtkActor> actor2 = 
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper ( mapper2 );
  actor2->SetPosition(0, 0, 0);
  actor2->GetProperty()->SetColor(1.0, .4, .4);

  // Create a renderer
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground ( .6, .4, .2);
  renderer->AddActor ( actor2 );

  // Create a render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer ( renderer );

  // Create an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow ( renderWindow );

  for (int i = 0; i < 10; ++i)
  {
    // Create a mapper
    vtkSmartPointer<vtkPolyDataMapper> mapper = 
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection ( sphereSource->GetOutputPort() );

    // Create an actor
    vtkSmartPointer<vtkActor> actor = 
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper ( mapper );
    actor->SetPosition(0, 0, 0);

    // Setup the text and add it to the renderer
    vtkSmartPointer<vtkBillboardTextActor3D> textActor = 
      vtkSmartPointer<vtkBillboardTextActor3D>::New();
    textActor->SetInput ("");
    textActor->SetPosition (actor->GetPosition());
    textActor->GetTextProperty()->SetFontSize ( 12 );
    textActor->GetTextProperty()->SetColor ( 1.0, 1.0, .4 );
    textActor->GetTextProperty()->SetJustificationToCentered();

    renderer->AddActor ( actor );
    renderer->AddActor ( textActor );
  
    vtkSmartPointer<vtkCallbackCommand> actorCallback =
      vtkSmartPointer<vtkCallbackCommand>::New();
    actorCallback->SetCallback (ActorCallback);
    actorCallback->SetClientData(textActor);
    actor->AddObserver(vtkCommand::ModifiedEvent,actorCallback);
    actor->SetPosition(vtkMath::Random(-10.0, 10.0),
                       vtkMath::Random(-10.0, 10.0),
                       vtkMath::Random(-10.0, 10.0));
  }
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
