#include <vtkSmartPointer.h>
#include <vtkImageRGBToHSI.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageExtractComponents.h>
#include <vtkNamedColors.h>

int main(int argc, char *argv[])
{
  // Verify command line arguments
  if(argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << "image" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> reader;
  reader.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkImageRGBToHSI> hsiFilter =
    vtkSmartPointer<vtkImageRGBToHSI>::New();
  hsiFilter->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageExtractComponents> extractHFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractHFilter->SetInputConnection(hsiFilter->GetOutputPort());
  extractHFilter->SetComponents(0);

  vtkSmartPointer<vtkImageExtractComponents> extractSFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractSFilter->SetInputConnection(hsiFilter->GetOutputPort());
  extractSFilter->SetComponents(1);

  vtkSmartPointer<vtkImageExtractComponents> extractIFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractIFilter->SetInputConnection(hsiFilter->GetOutputPort());
  extractIFilter->SetComponents(2);

  // Create actors
  vtkSmartPointer<vtkImageActor> inputActor =
    vtkSmartPointer<vtkImageActor>::New();
  inputActor->GetMapper()->SetInputConnection(
    reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> hActor =
    vtkSmartPointer<vtkImageActor>::New();
  hActor->GetMapper()->SetInputConnection(
    extractHFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> sActor =
    vtkSmartPointer<vtkImageActor>::New();
  sActor->GetMapper()->SetInputConnection(
    extractSFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> iActor =
    vtkSmartPointer<vtkImageActor>::New();
  iActor->GetMapper()->SetInputConnection(
    extractIFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double inputViewport[4] = {0.0, 0.0, 0.25, 1.0};
  double hViewport[4] = {0.25, 0.0, 0.5, 1.0};
  double sViewport[4] = {0.5, 0.0, 0.75, 1.0};
  double iViewport[4] = {0.75, 0.0, 1.0, 1.0};

  // Shared camera
  vtkSmartPointer<vtkCamera> sharedCamera =
    vtkSmartPointer<vtkCamera>::New();

  // Setup renderers
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkSmartPointer<vtkRenderer> inputRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  inputRenderer->SetViewport(inputViewport);
  inputRenderer->AddActor(inputActor);
  inputRenderer->SetActiveCamera(sharedCamera);
  inputRenderer->SetBackground(colors->GetColor3d("Tomato").GetData());

  vtkSmartPointer<vtkRenderer> hRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  hRenderer->SetViewport(hViewport);
  hRenderer->AddActor(hActor);
  hRenderer->SetActiveCamera(sharedCamera);
  hRenderer->SetBackground(colors->GetColor3d("Gainsboro").GetData());

  vtkSmartPointer<vtkRenderer> sRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  sRenderer->SetViewport(sViewport);
  sRenderer->AddActor(sActor);
  sRenderer->SetActiveCamera(sharedCamera);
  sRenderer->SetBackground(colors->GetColor3d("LightGrey").GetData());

  vtkSmartPointer<vtkRenderer> iRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  iRenderer->SetViewport(iViewport);
  iRenderer->AddActor(iActor);
  iRenderer->SetActiveCamera(sharedCamera);
  iRenderer->SetBackground(colors->GetColor3d("Silver").GetData());

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(1000, 250);
  renderWindow->AddRenderer(inputRenderer);
  renderWindow->AddRenderer(hRenderer);
  renderWindow->AddRenderer(sRenderer);
  renderWindow->AddRenderer(iRenderer);
  inputRenderer->ResetCamera();

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
