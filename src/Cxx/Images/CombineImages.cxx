#include <vtkImageBlend.h>
#include <vtkSmartPointer.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
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

  // Read the images
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> imgReader1;
  imgReader1.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  imgReader1->SetFileName(argv[1]);

  vtkSmartPointer<vtkImageReader2> imgReader2;
  imgReader2.TakeReference(
    readerFactory->CreateImageReader2(argv[2]));
  imgReader2->SetFileName(argv[2]);

  // Combine the images (blend takes multiple connections on the 0th input port)
  vtkSmartPointer<vtkImageBlend> blend =
    vtkSmartPointer<vtkImageBlend>::New();
  blend->AddInputConnection(imgReader1->GetOutputPort());
  blend->AddInputConnection(imgReader2->GetOutputPort());
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

  imageViewer->GetRenderer()->Render();
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
