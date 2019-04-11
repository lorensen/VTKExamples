#include <vtkSmartPointer.h>
#include <vtkImageRGBToYIQ.h>

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

  vtkSmartPointer<vtkImageRGBToYIQ> yiqFilter =
    vtkSmartPointer<vtkImageRGBToYIQ>::New();
  yiqFilter->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageExtractComponents> extractYFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractYFilter->SetInputConnection(yiqFilter->GetOutputPort());
  extractYFilter->SetComponents(0);

  vtkSmartPointer<vtkImageExtractComponents> extractIFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractIFilter->SetInputConnection(yiqFilter->GetOutputPort());
  extractIFilter->SetComponents(1);

  vtkSmartPointer<vtkImageExtractComponents> extractQFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractQFilter->SetInputConnection(yiqFilter->GetOutputPort());
  extractQFilter->SetComponents(2);

  // Create actors
  vtkSmartPointer<vtkImageActor> inputActor =
    vtkSmartPointer<vtkImageActor>::New();
  inputActor->GetMapper()->SetInputConnection(
    reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> yActor =
    vtkSmartPointer<vtkImageActor>::New();
  yActor->GetMapper()->SetInputConnection(
    extractYFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> iActor =
    vtkSmartPointer<vtkImageActor>::New();
  iActor->GetMapper()->SetInputConnection(
    extractIFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> qActor =
    vtkSmartPointer<vtkImageActor>::New();
  qActor->GetMapper()->SetInputConnection(
    extractQFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double inputViewport[4] = {0.0, 0.0, 0.25, 1.0};
  double yViewport[4] = {0.25, 0.0, 0.5, 1.0};
  double iViewport[4] = {0.5, 0.0, 0.75, 1.0};
  double qViewport[4] = {0.75, 0.0, 1.0, 1.0};

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

  vtkSmartPointer<vtkRenderer> yRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  yRenderer->SetViewport(yViewport);
  yRenderer->AddActor(yActor);
  yRenderer->SetActiveCamera(sharedCamera);
  yRenderer->SetBackground(colors->GetColor3d("Gainsboro").GetData());

  vtkSmartPointer<vtkRenderer> iRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  iRenderer->SetViewport(iViewport);
  iRenderer->AddActor(iActor);
  iRenderer->SetActiveCamera(sharedCamera);
  iRenderer->SetBackground(colors->GetColor3d("LightGrey").GetData());

  vtkSmartPointer<vtkRenderer> qRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  qRenderer->SetViewport(qViewport);
  qRenderer->AddActor(qActor);
  qRenderer->SetActiveCamera(sharedCamera);
  qRenderer->SetBackground(colors->GetColor3d("Silver").GetData());

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(1000, 250);
  renderWindow->AddRenderer(inputRenderer);
  renderWindow->AddRenderer(yRenderer);
  renderWindow->AddRenderer(iRenderer);
  renderWindow->AddRenderer(qRenderer);
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
