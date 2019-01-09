#include <vtkActor.h>
#include <vtkAssembly.h>
#include <vtkAssemblyPath.h>
#include <vtkAxesActor.h>
#include <vtkCommand.h>
#include <vtkConeSource.h>
#include <vtkFollower.h>
#include <vtkPolyDataMapper.h>
#include <vtkProp3DCollection.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkSmartPointer.h>
#include <vtkTextActor.h>
#include <vtkVectorText.h>

//----------------------------------------------------------------------------
class vtkPositionCallback : public vtkCommand
{
public:
  static vtkPositionCallback *New()
  { return new vtkPositionCallback; }

  void Execute( vtkObject* vtkNotUsed(caller), unsigned long vtkNotUsed(event),
                void *vtkNotUsed( callData ) )
  {
    this->Axes->InitPathTraversal();
    vtkAssemblyPath *path = 0;
    int count = 0;
    vtkFollower* followers[3] = { this->XLabel, this->YLabel, this->ZLabel };
    int followerId = 0;
    while( (path = this->Axes->GetNextPath()) != NULL )
    {
      if( count++ > 2 )
      {
        vtkProp3D *prop3D = static_cast<vtkProp3D *>(path->GetLastNode()->GetViewProp());
        if ( prop3D )
        {
          prop3D->PokeMatrix(path->GetLastNode()->GetMatrix());
          followers[followerId]->SetPosition(prop3D->GetCenter());
          followerId++;
          prop3D->PokeMatrix(NULL);
        }
      }
    }
  }

  vtkPositionCallback(): XLabel( 0 ), YLabel( 0 ),ZLabel( 0 ),Axes(0){}

  vtkFollower *XLabel;
  vtkFollower *YLabel;
  vtkFollower *ZLabel;
  vtkAssembly* Axes;
};

int main (int, char *[])
{
  vtkSmartPointer<vtkConeSource> coneSource =
    vtkSmartPointer<vtkConeSource>::New();
  coneSource->Update();

//  vtkPolyData* cone = coneSource->GetOutput();

  //create a mapper
  vtkSmartPointer<vtkPolyDataMapper> coneMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection(coneSource->GetOutputPort());

  // create an actor
  vtkSmartPointer<vtkActor> coneActor =
    vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMapper);
  coneActor->GetProperty()->SetColor(1,1,0);

  // a renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // add the actors to the scene
  renderer->AddActor(coneActor);
  renderer->SetBackground(0.5,0.5,0.5);

  // vtkAxesActor is currently not designed to work with vtkInteractorStyleTrackballActor
  // since it is a hybrid object containing both vtkProp3D's and vtkActor2D's, the latter
  // of which does not have a 3D position that can be manipulated
  vtkSmartPointer<vtkAxesActor> axes =
    vtkSmartPointer<vtkAxesActor>::New();

  // get a copy of the axes' constituent 3D actors and put them into a vtkAssembly
  // so they can be manipulated as one prop
  vtkSmartPointer<vtkPropCollection> collection =
    vtkSmartPointer<vtkPropCollection>::New();
  axes->GetActors(collection);

  collection->InitTraversal();

  vtkSmartPointer<vtkAssembly> movableAxes =
    vtkSmartPointer<vtkAssembly>::New();

  for( int i = 0; i < collection->GetNumberOfItems(); ++i )
  {
    movableAxes->AddPart((vtkProp3D*)collection->GetNextProp());
  }

  renderer->AddActor(movableAxes);

  // create our own labels that will follow and face the camera
  vtkSmartPointer<vtkFollower> xLabel =
    vtkSmartPointer<vtkFollower>::New();
  vtkSmartPointer<vtkVectorText> xText =
    vtkSmartPointer<vtkVectorText>::New();
  vtkSmartPointer<vtkPolyDataMapper> xTextMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  xText->SetText( "X" );
  xTextMapper->SetInputConnection( xText->GetOutputPort() );
  xLabel->SetMapper( xTextMapper );
  xLabel->SetScale( 0.3 );
  xLabel->SetCamera(renderer->GetActiveCamera());
  xLabel->SetPosition(((vtkProp3D*)collection->GetItemAsObject( 3 ))->GetCenter()); // XAxisTip
  xLabel->PickableOff();
  renderer->AddActor( xLabel );

  vtkSmartPointer<vtkFollower> yLabel =
    vtkSmartPointer<vtkFollower>::New();
  vtkSmartPointer<vtkVectorText> yText =
    vtkSmartPointer<vtkVectorText>::New();
  vtkSmartPointer<vtkPolyDataMapper> yTextMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  yText->SetText( "Y" );
  yTextMapper->SetInputConnection( yText->GetOutputPort() );
  yLabel->SetMapper( yTextMapper );
  yLabel->SetScale( 0.3 );
  yLabel->SetCamera(renderer->GetActiveCamera());
  yLabel->SetPosition(((vtkProp3D*)collection->GetItemAsObject( 4 ))->GetCenter()); // YAxisTip
  yLabel->PickableOff();
  renderer->AddActor( yLabel );

  vtkSmartPointer<vtkFollower> zLabel =
    vtkSmartPointer<vtkFollower>::New();
  vtkSmartPointer<vtkVectorText> zText =
    vtkSmartPointer<vtkVectorText>::New();
  vtkSmartPointer<vtkPolyDataMapper> zTextMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  zText->SetText( "Z" );
  zTextMapper->SetInputConnection( zText->GetOutputPort() );
  zLabel->SetMapper( zTextMapper );
  zLabel->SetScale( 0.3 );
  zLabel->SetCamera(renderer->GetActiveCamera());
  zLabel->SetPosition(((vtkProp3D*)collection->GetItemAsObject( 5 ))->GetCenter()); // ZAxisTip
  zLabel->PickableOff();
  renderer->AddActor( zLabel );

  // custom callback to set the positions of the labels
  vtkSmartPointer<vtkPositionCallback> callback =
    vtkSmartPointer<vtkPositionCallback>::New();
  callback->XLabel = xLabel;
  callback->YLabel = yLabel;
  callback->ZLabel = zLabel;
  callback->Axes = movableAxes;

  renderer->ResetCamera();
  renderWindow->Render();

  vtkSmartPointer<vtkInteractorStyleTrackballActor> style =
      vtkSmartPointer<vtkInteractorStyleTrackballActor>::New();

  renderWindowInteractor->SetInteractorStyle( style );
  style->AddObserver( vtkCommand::InteractionEvent, callback );

  // begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
