#include <vtkImageResize.h>
#include <vtkImageSincInterpolator.h>

#include <vtkVersion.h>
#include <vtkImageActor.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageData.h>
#include <vtkJPEGReader.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkSmartPointer.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkImageData> imageData;

  int newSize[2] = {200, 10};
  int windowFunction = 0;

  // Verify input arguments
  if ( argc > 1 )
  {
    //Read the image
    vtkSmartPointer<vtkJPEGReader> jpegReader =
      vtkSmartPointer<vtkJPEGReader>::New();
    jpegReader->SetFileName ( argv[1] );
    jpegReader->Update();

    imageData = jpegReader->GetOutput();
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
  if (windowFunction >= 0 && windowFunction <= 10)
  {
    interpolator->SetWindowFunction(windowFunction);
  }

  vtkSmartPointer<vtkImageResize> resize =
    vtkSmartPointer<vtkImageResize>::New();
#if VTK_MAJOR_VERSION <= 5
  resize->SetInput(imageData);
#else
  resize->SetInputData(imageData);
#endif
  resize->SetOutputDimensions(newSize[0], newSize[1], 1);
  resize->Update();
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

 // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(imageActor);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
