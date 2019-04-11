#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageFFT.h>
#include <vtkImageFourierCenter.h>
#include <vtkImageLogarithmicScale.h>
#include <vtkImageMagnitude.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMapToColors.h>
#include <vtkImageProperty.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkInteractorStyleImage.h>
#include <vtkNamedColors.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkWindowLevelLookupTable.h>

namespace
{
void CreateImageActor(vtkSmartPointer<vtkImageActor> &actor,
                      double colorWindow, double colorLevel);
}
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
  reader->Update();


  vtkSmartPointer<vtkImageFFT> fft =
    vtkSmartPointer<vtkImageFFT>::New();
//  fft->SetFilteredAxes $VTK_IMAGE_X_AXIS $VTK_IMAGE_Y_AXIS
  fft->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageMagnitude> mag =
    vtkSmartPointer<vtkImageMagnitude>::New();
  mag->SetInputConnection(fft->GetOutputPort());

  vtkSmartPointer<vtkImageFourierCenter> center =
    vtkSmartPointer<vtkImageFourierCenter>::New();
  center->SetInputConnection(mag->GetOutputPort());
 
  vtkSmartPointer<vtkImageLogarithmicScale> compress =
    vtkSmartPointer<vtkImageLogarithmicScale>::New();
  compress->SetInputConnection(center->GetOutputPort());
  compress->SetConstant(15);
  compress->Update();

  // Create actors
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(reader->GetOutputPort());
  originalActor->GetProperty()->SetInterpolationTypeToNearest();

  vtkSmartPointer<vtkImageActor> compressedActor =
    vtkSmartPointer<vtkImageActor>::New();
  compressedActor->GetMapper()->SetInputConnection(compress->GetOutputPort());
  compressedActor->GetProperty()->SetInterpolationTypeToNearest();
  CreateImageActor(compressedActor, 160, 120);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double compressedViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  vtkSmartPointer<vtkRenderer> compressedRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  compressedRenderer->SetViewport(compressedViewport);
  compressedRenderer->AddActor(compressedActor);
  compressedRenderer->ResetCamera();
  compressedRenderer->SetBackground(colors->GetColor3d("LightSlateGray").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(compressedRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

namespace
{
void CreateImageActor(vtkSmartPointer<vtkImageActor> &actor,
                      double colorWindow, double colorLevel)
{
  vtkSmartPointer<vtkWindowLevelLookupTable> wlut =
    vtkSmartPointer<vtkWindowLevelLookupTable>::New();
  wlut->SetWindow(colorWindow);
  wlut->SetLevel(colorLevel);
  wlut->Build();

  // Map the image through the lookup table
  vtkSmartPointer<vtkImageMapToColors> color =
    vtkSmartPointer<vtkImageMapToColors>::New();
  color->SetLookupTable(wlut);
  color->SetInputData(actor->GetMapper()->GetInput());

  actor->GetMapper()->SetInputConnection(color->GetOutputPort());
  return;
}
}
