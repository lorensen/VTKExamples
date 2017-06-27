#include <vtkImageBlend.h>
#include <vtkSmartPointer.h>

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkNamedColors.h>

#include <string>

int main ( int argc, char* argv[] )
{
  // Parse input arguments
  if ( argc != 3 )
  {
    std::cerr << "Usage: " << argv[0]
              << " Input1Filename Input2Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string input1Filename = argv[1];
  std::string input2Filename = argv[2];

  // Read the images
  vtkSmartPointer<vtkJPEGReader> jPEGReader1 =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader1->SetFileName ( input1Filename.c_str() );

  vtkSmartPointer<vtkJPEGReader> jPEGReader2 =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader2->SetFileName ( input2Filename.c_str() );

  // Combine the images (blend takes multiple connections on the 0th input port)
  vtkSmartPointer<vtkImageBlend> blend =
    vtkSmartPointer<vtkImageBlend>::New();
  blend->AddInputConnection(jPEGReader1->GetOutputPort());
  blend->AddInputConnection(jPEGReader2->GetOutputPort());
  blend->SetOpacity(0,.5);
  blend->SetOpacity(1,.5);

  // Display the result
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(blend->GetOutputPort());
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->GetRenderer()->SetBackground(
    colors->GetColor3d("Wheat").GetData());

  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
