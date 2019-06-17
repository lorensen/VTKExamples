#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkJPEGReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  //Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.jpeg/jpg) e.g. Pileated.jpg " << std::endl;
    return EXIT_FAILURE;
  }

  //Read the image
  vtkSmartPointer<vtkJPEGReader> jpegReader =
    vtkSmartPointer<vtkJPEGReader>::New();
  jpegReader->SetFileName ( argv[1] );

  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection( jpegReader->GetOutputPort() );
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
