#include <vtkSmartPointer.h>
#include <vtkImageResize.h>
#include <vtkImageSincInterpolator.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkCamera.h>
#include <vtkImageActor.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkNamedColors.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkImageData> imageData;

  int newSize[2] = {200, 10};
  int windowFunction = 0;

  // Verify input arguments
  if ( argc > 1 )
  {
    // Read the image
    vtkSmartPointer<vtkImageReader2Factory> readerFactory =
      vtkSmartPointer<vtkImageReader2Factory>::New();
    vtkSmartPointer<vtkImageReader2> reader;
    reader.TakeReference(
      readerFactory->CreateImageReader2(argv[1]));
    reader->SetFileName(argv[1]);
    reader->Update();

    imageData = reader->GetOutput();

    if (argc >3)
    {
      newSize[0] = atoi(argv[2]);
      newSize[1] = atoi(argv[3]);
    }
    if (argc > 4)
    {
      windowFunction = atoi(argv[4]);
    }
  }
  else
  {
    vtkSmartPointer<vtkImageCanvasSource2D> canvasSource =
      vtkSmartPointer<vtkImageCanvasSource2D>::New();
    canvasSource->SetExtent(0, 100, 0, 100, 0, 0);
    canvasSource->SetScalarTypeToUnsignedChar();
    canvasSource->SetNumberOfScalarComponents(3);
    canvasSource->SetDrawColor(127, 127, 100);
    canvasSource->FillBox(0, 100, 0, 100);
    canvasSource->SetDrawColor(100, 255, 255);
    canvasSource->FillTriangle(10, 10, 25, 10, 25, 25);
    canvasSource->SetDrawColor(255, 100, 255);
    canvasSource->FillTube(75, 75, 0, 75, 5.0);
    canvasSource->Update();
    imageData = canvasSource->GetOutput();
  }

  vtkSmartPointer<vtkImageSincInterpolator> interpolator =
    vtkSmartPointer<vtkImageSincInterpolator>::New();
  interpolator->UseWindowParameterOn();
  if (windowFunction >= 0 && windowFunction <= 10)
  {
    interpolator->SetWindowFunction(windowFunction);
  }

  vtkSmartPointer<vtkImageResize> resize =
    vtkSmartPointer<vtkImageResize>::New();
  resize->SetInputData(imageData);
  resize->SetInterpolator(interpolator);
  resize->SetOutputDimensions(newSize[0], newSize[1], 1);
  resize->InterpolateOn();

  if (windowFunction < 0)
  {
    resize->InterpolateOff();
    std::cout << "Using nearest neighbor interpolation" << std::endl;;
  }
  else
  {
    std::cout << "Using window function : "
              << interpolator->GetWindowFunctionAsString() << std::endl;;
  }

  // Create an image actor to display the image
  vtkSmartPointer<vtkImageActor> imageActor =
    vtkSmartPointer<vtkImageActor>::New();
  imageActor->GetMapper()->SetInputConnection(resize->GetOutputPort());
  imageActor->InterpolateOff();

  // Setup renderer
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(imageActor);
  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Dolly(5.0);
  renderer->ResetCameraClippingRange();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(1280, 1024);

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
