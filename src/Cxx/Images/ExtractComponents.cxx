#include <vtkSmartPointer.h>
#include <vtkImageExtractComponents.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <vtkNamedColors.h>

int main(int argc, char *argv[])
{
  // Verify command line arguments
  if (argc != 2 )
  {
    std::cout << "Usage: " << argv[0] << " InputFilename" << std::endl;
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

  vtkSmartPointer<vtkImageExtractComponents> extractRedFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractRedFilter->SetInputConnection(reader->GetOutputPort());
  extractRedFilter->SetComponents(0);
  extractRedFilter->Update();

  vtkSmartPointer<vtkImageExtractComponents> extractGreenFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractGreenFilter->SetInputConnection(reader->GetOutputPort());
  extractGreenFilter->SetComponents(1);
  extractGreenFilter->Update();

  vtkSmartPointer<vtkImageExtractComponents> extractBlueFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractBlueFilter->SetInputConnection(reader->GetOutputPort());
  extractBlueFilter->SetComponents(2);
  extractBlueFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> inputActor =
    vtkSmartPointer<vtkImageActor>::New();
  inputActor->GetMapper()->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> redActor =
    vtkSmartPointer<vtkImageActor>::New();
  redActor->GetMapper()->SetInputConnection(extractRedFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> greenActor =
    vtkSmartPointer<vtkImageActor>::New();
  greenActor->GetMapper()->SetInputConnection(extractGreenFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> blueActor =
    vtkSmartPointer<vtkImageActor>::New();
  blueActor->GetMapper()->SetInputConnection(extractBlueFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double inputViewport[4] = {0.0, 0.0, 0.25, 1.0};
  double redViewport[4] = {0.25, 0.0, 0.5, 1.0};
  double greenViewport[4] = {0.5, 0.0, 0.75, 1.0};
  double blueViewport[4] = {0.75, 0.0, 1.0, 1.0};

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Setup renderers
  vtkSmartPointer<vtkRenderer> inputRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  inputRenderer->SetViewport(inputViewport);
  inputRenderer->AddActor(inputActor);
  inputRenderer->ResetCamera();
  inputRenderer->SetBackground(colors->GetColor3d("Snow").GetData());

  vtkSmartPointer<vtkRenderer> redRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  redRenderer->SetViewport(redViewport);
  redRenderer->AddActor(redActor);
  redRenderer->ResetCamera();
  redRenderer->SetBackground(colors->GetColor3d("Tomato").GetData());

  vtkSmartPointer<vtkRenderer> greenRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  greenRenderer->SetViewport(greenViewport);
  greenRenderer->AddActor(greenActor);
  greenRenderer->ResetCamera();
  greenRenderer->SetBackground(colors->GetColor3d("Mint").GetData());

  vtkSmartPointer<vtkRenderer> blueRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  blueRenderer->SetViewport(blueViewport);
  blueRenderer->AddActor(blueActor);
  blueRenderer->ResetCamera();
  blueRenderer->SetBackground(colors->GetColor3d("Peacock").GetData());

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(1000, 250);
  renderWindow->AddRenderer(inputRenderer);
  renderWindow->AddRenderer(redRenderer);
  renderWindow->AddRenderer(greenRenderer);
  renderWindow->AddRenderer(blueRenderer);

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
