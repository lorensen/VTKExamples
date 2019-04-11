#include <vtkCamera.h>
#include <vtkImageActor.h>
#include <vtkImageButterworthHighPass.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageFFT.h>
#include <vtkImageIdealHighPass.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMapToWindowLevelColors.h>
#include <vtkImageProperty.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageRFFT.h>
#include <vtkInteractorStyleImage.h>
#include <vtkNamedColors.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

 int main (int argc, char *argv[])
{
  // Verify input arguments
  if ( argc < 2 )
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
  fft->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageIdealHighPass> idealHighPass =
    vtkSmartPointer<vtkImageIdealHighPass>::New();
  idealHighPass->SetInputConnection(fft->GetOutputPort());
  idealHighPass->SetXCutOff(0.1);
  idealHighPass->SetYCutOff(0.1);

  vtkSmartPointer<vtkImageRFFT> idealRfft =
    vtkSmartPointer<vtkImageRFFT>::New();
  idealRfft->SetInputConnection(idealHighPass->GetOutputPort());
 
  vtkSmartPointer<vtkImageExtractComponents> idealReal =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  idealReal->SetInputConnection(idealRfft->GetOutputPort());
  idealReal->SetComponents(0);

  vtkSmartPointer<vtkImageButterworthHighPass> butterworthHighPass =
    vtkSmartPointer<vtkImageButterworthHighPass>::New();
  butterworthHighPass->SetInputConnection(fft->GetOutputPort());
  butterworthHighPass->SetXCutOff(0.1);
  butterworthHighPass->SetYCutOff(0.1);

  vtkSmartPointer<vtkImageRFFT> butterworthRfft =
    vtkSmartPointer<vtkImageRFFT>::New();
  butterworthRfft->SetInputConnection(butterworthHighPass->GetOutputPort());
 
  vtkSmartPointer<vtkImageExtractComponents> butterworthReal =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  butterworthReal->SetInputConnection(butterworthRfft->GetOutputPort());
  butterworthReal->SetComponents(0);

  // Create actors
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkImageMapToWindowLevelColors> idealColor =
    vtkSmartPointer<vtkImageMapToWindowLevelColors>::New();
  idealColor->SetWindow(500);
  idealColor->SetLevel(0);
  idealColor->SetInputConnection(idealReal->GetOutputPort());

  vtkSmartPointer<vtkImageActor> idealActor =
    vtkSmartPointer<vtkImageActor>::New();
  idealActor->GetMapper()->SetInputConnection(idealColor->GetOutputPort());
  idealActor->GetProperty()->SetInterpolationTypeToNearest();

  vtkSmartPointer<vtkImageMapToWindowLevelColors> butterworthColor =
    vtkSmartPointer<vtkImageMapToWindowLevelColors>::New();
  butterworthColor->SetWindow(500);
  butterworthColor->SetLevel(0);
  butterworthColor->SetInputConnection(butterworthReal->GetOutputPort());

  vtkSmartPointer<vtkImageActor> butterworthActor =
    vtkSmartPointer<vtkImageActor>::New();
  butterworthActor->GetMapper()->SetInputConnection(butterworthColor->GetOutputPort());
  butterworthActor->GetProperty()->SetInterpolationTypeToNearest();

  // Setup renderers
  vtkSmartPointer<vtkRenderer> idealRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  idealRenderer->SetViewport(0.0, 0.0, 0.5, 1.0);
  idealRenderer->AddActor(idealActor);
  idealRenderer->ResetCamera();
  idealRenderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  vtkSmartPointer<vtkRenderer> butterworthRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  butterworthRenderer->SetViewport(0.5, 0.0, 1.0, 1.0);
  butterworthRenderer->AddActor(butterworthActor);
  butterworthRenderer->SetActiveCamera(idealRenderer->GetActiveCamera());
  butterworthRenderer->SetBackground(colors->GetColor3d("LightSlateGray").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(idealRenderer);
  renderWindow->AddRenderer(butterworthRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  idealRenderer->GetActiveCamera()->Dolly(1.4);
  idealRenderer->ResetCameraClippingRange();
  renderWindow->Render();
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
