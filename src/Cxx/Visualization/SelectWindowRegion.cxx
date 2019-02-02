#include <vtkSmartPointer.h>

#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkInteractorStyleRubberBand2D.h>
#include <vtkJPEGReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

static void SelectionChangedCallbackFunction (
  vtkObject* caller,
  long unsigned int eventId,
  void* clientData,
  void* callData );

int main(int argc, char* argv[])
{
  // Parse input arguments
  if ( argc != 2 )
  {
    std::cout << "Required parameters: Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  // Read the image
  vtkSmartPointer<vtkJPEGReader> jPEGReader =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader->SetFileName ( inputFilename.c_str() );
  jPEGReader->Update();

  // Create an actor
  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection ( jPEGReader->GetOutputPort() );

  // Setup the SelectionChangedEvent callback
  vtkSmartPointer<vtkCallbackCommand> selectionChangedCallback =
    vtkSmartPointer<vtkCallbackCommand>::New();
  selectionChangedCallback->SetCallback ( SelectionChangedCallbackFunction );

  // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor ( actor );
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer ( renderer );

  // Setup 2D interaction style
  vtkSmartPointer<vtkInteractorStyleRubberBand2D> style =
    vtkSmartPointer<vtkInteractorStyleRubberBand2D>::New();
  style->AddObserver ( vtkCommand::SelectionChangedEvent, selectionChangedCallback );

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetInteractorStyle ( style );

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow ( renderWindow );
  renderWindow->Render();
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void SelectionChangedCallbackFunction (
  vtkObject* vtkNotUsed(caller),
  long unsigned int vtkNotUsed(eventId),
  void* vtkNotUsed(clientData),
  void* callData )
{
  std::cout << "Selection changed callback" << std::endl;

  unsigned int* rect = reinterpret_cast<unsigned int*> ( callData );
  unsigned int pos1X = rect[0];
  unsigned int pos1Y = rect[1];
  unsigned int pos2X = rect[2];
  unsigned int pos2Y = rect[3];

  std::cout << "Start x: " << pos1X
            << " Start y: " << pos1Y
            << " End x: " << pos2X
            << " End y: " << pos2Y << std::endl;
}

/*
//You could override this, but then you have to reimplement the functionality.
//Instead, you should use an observer

void vtkInteractorStyleRubberBand2D::OnLeftButtonUp()
{
  std::cout << "LeftButtonUp!" << std::endl;

  std::cout << "Start: " << this->StartPosition[0] << " " << this->StartPosition[1] << std::endl;
  std::cout << "End: " << this->EndPosition[0] << " " << this->EndPosition[1] << std::endl;

  //this->Superclass.OnLeftButtonUp(); //doesn't work

  InvokeEvent(vtkCommand::EndPickEvent);
  InvokeEvent(vtkCommand::SelectionChangedEvent);

}
*/
