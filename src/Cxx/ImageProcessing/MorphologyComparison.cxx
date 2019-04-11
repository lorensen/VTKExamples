#include <vtkCamera.h>
#include <vtkDataArray.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageDilateErode3D.h>
#include <vtkImageMapper3D.h>
#include <vtkImageProperty.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageSeedConnectivity.h>
#include <vtkInteractorStyleImage.h>
#include <vtkPointData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

#include <vector>

int main (int argc, char *argv[])
{
  // Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> reader;
  reader.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  reader->SetFileName(argv[1]);

  // Dilate
  vtkSmartPointer<vtkImageDilateErode3D> dilate =
    vtkSmartPointer<vtkImageDilateErode3D>::New();
  dilate->SetInputConnection(reader->GetOutputPort());
  dilate->SetDilateValue(0);
  dilate->SetErodeValue(255);
  dilate->SetKernelSize(31, 31, 1);

  // Erode
  vtkSmartPointer<vtkImageDilateErode3D> erode =
    vtkSmartPointer<vtkImageDilateErode3D>::New();
  erode->SetInputConnection(reader->GetOutputPort());
  erode->SetDilateValue(255);
  erode->SetErodeValue(0);
  erode->SetKernelSize(31, 31, 1);

  // Opening - dilate then erode
  vtkSmartPointer<vtkImageDilateErode3D> dilate1 =
    vtkSmartPointer<vtkImageDilateErode3D>::New();
  dilate1->SetInputConnection(reader->GetOutputPort());
  dilate1->SetDilateValue(0);
  dilate1->SetErodeValue(255);
  dilate1->SetKernelSize(31, 31, 1);

  vtkSmartPointer<vtkImageDilateErode3D> erode1 =
    vtkSmartPointer<vtkImageDilateErode3D>::New();
  erode1->SetInputConnection(dilate1->GetOutputPort());
  erode1->SetDilateValue(255);
  erode1->SetErodeValue(0);
  erode1->SetKernelSize(31, 31, 1);

  // Closing - erode then dilate
  vtkSmartPointer<vtkImageDilateErode3D> erode2 =
    vtkSmartPointer<vtkImageDilateErode3D>::New();
  erode2->SetInputConnection(reader->GetOutputPort());
  erode2->SetDilateValue(255);
  erode2->SetErodeValue(0);
  erode2->SetKernelSize(31, 31, 1);

  vtkSmartPointer<vtkImageDilateErode3D> dilate2 =
    vtkSmartPointer<vtkImageDilateErode3D>::New();
  dilate2->SetInputConnection(erode2->GetOutputPort());
  dilate2->SetDilateValue(0);
  dilate2->SetErodeValue(255);
  dilate2->SetKernelSize(31, 31, 1);

  // Connectivity
  vtkSmartPointer<vtkImageSeedConnectivity> con =
    vtkSmartPointer<vtkImageSeedConnectivity>::New();
  con->SetInputConnection(reader->GetOutputPort());
  con->AddSeed(300, 200);
  con->SetInputConnectValue(0);
  con->SetOutputConnectedValue(0);
  con->SetOutputUnconnectedValue(255);

  // Actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(reader->GetOutputPort());
  originalActor->GetProperty()->SetInterpolationTypeToNearest();

  vtkSmartPointer<vtkImageActor> connectedActor =
    vtkSmartPointer<vtkImageActor>::New();
  connectedActor->GetMapper()->SetInputConnection(con->GetOutputPort());
  connectedActor->GetProperty()->SetInterpolationTypeToNearest();

  vtkSmartPointer<vtkImageActor> erodeActor =
    vtkSmartPointer<vtkImageActor>::New();
  erodeActor->GetMapper()->SetInputConnection(erode->GetOutputPort());
  erodeActor->GetProperty()->SetInterpolationTypeToNearest();

  vtkSmartPointer<vtkImageActor> dilateActor =
    vtkSmartPointer<vtkImageActor>::New();
  dilateActor->GetMapper()->SetInputConnection(dilate->GetOutputPort());
  dilateActor->GetProperty()->SetInterpolationTypeToNearest();

  vtkSmartPointer<vtkImageActor> openingActor =
    vtkSmartPointer<vtkImageActor>::New();
  openingActor->GetMapper()->SetInputConnection(dilate2->GetOutputPort());
  openingActor->GetProperty()->SetInterpolationTypeToNearest();

  vtkSmartPointer<vtkImageActor> closingActor =
    vtkSmartPointer<vtkImageActor>::New();
  closingActor->GetMapper()->SetInputConnection(erode1->GetOutputPort());
  closingActor->GetProperty()->SetInterpolationTypeToNearest();

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->AddActor(originalActor);
  vtkSmartPointer<vtkRenderer> connectedRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  connectedRenderer->AddActor(connectedActor);
  vtkSmartPointer<vtkRenderer> dilateRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  dilateRenderer->AddActor(dilateActor);
  vtkSmartPointer<vtkRenderer> erodeRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  erodeRenderer->AddActor(erodeActor);
  vtkSmartPointer<vtkRenderer> closingRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  closingRenderer->AddActor(closingActor);
  vtkSmartPointer<vtkRenderer> openingRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  openingRenderer->AddActor(openingActor);

  std::vector<vtkSmartPointer<vtkRenderer> > renderers;
  renderers.push_back(originalRenderer);
  renderers.push_back(connectedRenderer);
  renderers.push_back(erodeRenderer);
  renderers.push_back(dilateRenderer);
  renderers.push_back(openingRenderer);
  renderers.push_back(closingRenderer); 

  // Setup viewports for the renderers
  int rendererSize = 300;
  unsigned int xGridDimensions = 2;
  unsigned int yGridDimensions = 3;

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(
    rendererSize * xGridDimensions, rendererSize * yGridDimensions);
  for (int row = 0; row < static_cast<int>(yGridDimensions); row++)
  {
    for (int col = 0; col < static_cast<int>(xGridDimensions); col++)
    {
      int index = row * xGridDimensions + col;
      // (xmin, ymin, xmax, ymax)
       double viewport[4] = {
         static_cast<double>(col) / xGridDimensions,
         static_cast<double>(yGridDimensions - (row + 1)) / yGridDimensions,
         static_cast<double>(col + 1) / xGridDimensions,
         static_cast<double>(yGridDimensions - row) / yGridDimensions};
      renderers[index]->SetViewport(viewport);
      renderWindow->AddRenderer(renderers[index]);
    }
  }

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Renderers share one camera
  renderWindow->Render();
  renderers[0]->GetActiveCamera()->Dolly(1.5);
  renderers[0]->ResetCameraClippingRange();

  for (size_t r = 1; r < renderers.size(); ++r)
  {
    renderers[r]->SetActiveCamera(renderers[0]->GetActiveCamera());
  }
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
