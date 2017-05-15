#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkImageCheckerboard.h>

int main ( int argc, char* argv[] )
{
  // Verify input arguments
  if ( argc != 3 )
  {
    std::cerr << "Usage: " << argv[0]
              << " Input1Filename Input2Filename" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse input arguments
  std::string inputFilename1 = argv[1];
  std::string inputFilename2 = argv[2];

  // Read the images
  vtkSmartPointer<vtkJPEGReader> jPEGReader1 =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader1->SetFileName ( inputFilename1.c_str() );

  vtkSmartPointer<vtkJPEGReader> jPEGReader2 =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader2->SetFileName ( inputFilename2.c_str() );

  vtkSmartPointer<vtkImageCheckerboard> checkerboardFilter =
    vtkSmartPointer<vtkImageCheckerboard>::New();
  checkerboardFilter->SetInputConnection(0, jPEGReader1->GetOutputPort());
  checkerboardFilter->SetInputConnection(1, jPEGReader2->GetOutputPort());
  checkerboardFilter->SetNumberOfDivisions(3,3,1);

  // Visualize
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(checkerboardFilter->GetOutputPort());
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->GetRenderer()->SetBackground(1,0,0);
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
