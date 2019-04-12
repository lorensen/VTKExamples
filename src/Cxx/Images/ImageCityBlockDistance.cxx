#include <vtkSmartPointer.h>
#include <vtkImageCityBlockDistance.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCast.h>
#include <vtkImageThreshold.h>
#include <vtkImageExtractComponents.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

int main(int argc, char *argv[])
{
  // Verify command line arguments
  if (argc < 2 )
  {
    std::cout << "Usage: " << argv[0] << " BinaryImage" << std::endl;
    return EXIT_FAILURE;
  }

  // Read file
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> reader;
  reader.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkImageCast> castFilter =
    vtkSmartPointer<vtkImageCast>::New();
  castFilter->SetOutputScalarTypeToShort();
  castFilter->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageCityBlockDistance> cityBlockDistanceFilter =
    vtkSmartPointer<vtkImageCityBlockDistance>::New();
  cityBlockDistanceFilter->SetInputConnection(castFilter->GetOutputPort());
  cityBlockDistanceFilter->SetDimensionality(2);
  cityBlockDistanceFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageCast> inputCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  inputCastFilter->SetOutputScalarTypeToUnsignedChar();
  inputCastFilter->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> inputActor =
    vtkSmartPointer<vtkImageActor>::New();
  inputActor->GetMapper()->SetInputConnection(inputCastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageCast> distanceCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  distanceCastFilter->SetOutputScalarTypeToUnsignedChar();
  distanceCastFilter->SetInputConnection(cityBlockDistanceFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> distanceActor =
    vtkSmartPointer<vtkImageActor>::New();
  distanceActor->GetMapper()->SetInputConnection(
    distanceCastFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double inputViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double distanceViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> inputRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  inputRenderer->SetViewport(inputViewport);
  inputRenderer->AddActor(inputActor);
  inputRenderer->ResetCamera();
  inputRenderer->SetBackground(.4, .5, .9);

  vtkSmartPointer<vtkRenderer> distanceRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  distanceRenderer->SetViewport(distanceViewport);
  distanceRenderer->AddActor(distanceActor);
  distanceRenderer->ResetCamera();
  distanceRenderer->SetBackground(.4, .5, .7);

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(inputRenderer);
  renderWindow->AddRenderer(distanceRenderer);

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
