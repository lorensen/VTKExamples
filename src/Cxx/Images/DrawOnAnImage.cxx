#include <vtkSmartPointer.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageViewer2.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageBlend.h>

int main ( int argc, char* argv[] )
{
  //Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " InputImageFilename" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> imgReader;
  imgReader.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  imgReader->SetFileName(argv[1]);
  imgReader->Update();

  vtkImageData* image = imgReader->GetOutput();

  // Find center of image
  int center[2];
  center[0] = (image->GetExtent()[1] + image->GetExtent()[0]) / 2;
  center[1] = (image->GetExtent()[3] + image->GetExtent()[2]) / 2;

  // Pick a radius for the circle
  int radius;
  radius = (image->GetExtent()[1] < image->GetExtent()[3]) ?
    image->GetExtent()[1] * 2 / 5 : image->GetExtent()[3] * 2 / 5;

  // Draw a circle in the center of the image
  vtkSmartPointer<vtkImageCanvasSource2D> drawing =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetScalarTypeToUnsignedChar();
  drawing->SetExtent(image->GetExtent());
  drawing->SetDrawColor(0.0, 0.0, 0.0);
  drawing->FillBox(image->GetExtent()[0], image->GetExtent()[1],
    image->GetExtent()[2], image->GetExtent()[3]);
  drawing->SetDrawColor(255.0, 255.0, 255.0);
  drawing->DrawCircle(center[0], center[1], radius);

  // Combine the images (blend takes multiple connections on the 0th
  // input port)
  vtkSmartPointer<vtkImageBlend> blend =
    vtkSmartPointer<vtkImageBlend>::New();
  blend->AddInputConnection(imgReader->GetOutputPort());
  blend->AddInputConnection(drawing->GetOutputPort());
  blend->SetOpacity(0,.6);
  blend->SetOpacity(1,.4);

  // Display the result
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(blend->GetOutputPort());
  imageViewer->SetSize(640, 512);
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->GetRenderer()->SetBackground(1,0,0); //red

  imageViewer->GetRenderWindow()->Render();
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
