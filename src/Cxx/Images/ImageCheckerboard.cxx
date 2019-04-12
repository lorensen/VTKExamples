#include <vtkImageCheckerboard.h>
#include <vtkSmartPointer.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkNamedColors.h>

int main ( int argc, char* argv[] )
{
  // Verify input arguments
  if ( argc != 3 )
  {
    std::cerr << "Usage: " << argv[0]
              << " Input1Filename Input2Filename" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the images
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> reader1;
  reader1.TakeReference(readerFactory->CreateImageReader2(argv[1]));
  reader1->SetFileName(argv[1]);

  vtkSmartPointer<vtkImageReader2> reader2;
  reader2.TakeReference(
    readerFactory->CreateImageReader2(argv[2]));
  reader2->SetFileName(argv[2]);

  vtkSmartPointer<vtkImageCheckerboard> checkerboardFilter =
    vtkSmartPointer<vtkImageCheckerboard>::New();
  checkerboardFilter->SetInputConnection(0, reader1->GetOutputPort());
  checkerboardFilter->SetInputConnection(1, reader2->GetOutputPort());
  checkerboardFilter->SetNumberOfDivisions(3,3,1);

  // Visualize
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(checkerboardFilter->GetOutputPort());
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->GetRenderer()->SetBackground(
    colors->GetColor3d("Wheat").GetData());
  imageViewer->GetRenderWindow()->Render();
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
