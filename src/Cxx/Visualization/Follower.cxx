#include <vtkActor.h>
#include <vtkCubeSource.h>
#include <vtkFollower.h>
#include <vtkInteractorStyle.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkVectorText.h>

int main(int, char *[])
{
  // Create some text
  vtkSmartPointer<vtkVectorText> textSource = 
    vtkSmartPointer<vtkVectorText>::New();
  textSource->SetText( "Hello" );

  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection( textSource->GetOutputPort() );

  // Create a subclass of vtkActor: a vtkFollower that remains facing the camera
  vtkSmartPointer<vtkFollower> follower = 
    vtkSmartPointer<vtkFollower>::New();
  follower->SetMapper( mapper );
  follower->GetProperty()->SetColor( 1, 0, 0 ); // red 

  // Create a transparent cube that does not move around to face the camera
  vtkSmartPointer<vtkCubeSource> cubeSource = 
    vtkSmartPointer<vtkCubeSource>::New();
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection( cubeSource->GetOutputPort() );
  vtkSmartPointer<vtkActor> cubeActor = 
    vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper( cubeMapper );
  cubeActor->GetProperty()->SetColor( 0, 0, 1 ); // blue
  cubeActor->GetProperty()->SetOpacity( 0.3 );

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  dynamic_cast<vtkInteractorStyle*>(renderWindowInteractor->GetInteractorStyle())->AutoAdjustCameraClippingRangeOn();
  renderWindowInteractor->SetRenderWindow( renderWindow );

  // Add the actor to the scene
  renderer->AddActor( follower );
  renderer->AddActor( cubeActor );
  renderer->SetBackground( 1, 1, 1 ); // Background color white
  follower->SetCamera( renderer->GetActiveCamera() );

  // Render and interact
  renderWindow->Render();
  renderer->ResetCamera();
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
