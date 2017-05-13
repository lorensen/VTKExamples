#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkImageSinusoidSource.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkImageSinusoidSource> sinusoidSource =
    vtkSmartPointer<vtkImageSinusoidSource>::New();
  sinusoidSource->Update();

  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(sinusoidSource->GetOutputPort());
  imageViewer->GetRenderWindow()->SetSize( 500, 500 );
  imageViewer->GetRenderer()->ResetCamera();

  // Set up an interactor that does not respond to mouse events
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  imageViewer->GetRenderWindow()->SetInteractor( renderWindowInteractor );
  renderWindowInteractor->SetInteractorStyle( 0 );
  imageViewer->Render();

  // Start the event loop
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
