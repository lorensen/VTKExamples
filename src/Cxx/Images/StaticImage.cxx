#include <vtkSmartPointer.h>

#include <vtkImageViewer2.h>
#include <vtkJPEGReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  // Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.jpeg)" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkJPEGReader> jpegReader =
    vtkSmartPointer<vtkJPEGReader>::New();
  if(!jpegReader->CanReadFile(argv[1]))
  {
    std::cout << argv[0]
              << ": Error reading file " << argv[1] << std::endl
              << " Exiting..." << std::endl;
    return EXIT_FAILURE;
  }

  jpegReader->SetFileName ( argv[1] );

  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection( jpegReader->GetOutputPort() );
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
