#include <vtkSmartPointer.h>
#include <vtkImageResize.h>
#include <vtkImageSincInterpolator.h>

#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkImageActor.h>
#include <vtkActor2D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkNamedColors.h>

#include <string>
#include <vector>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkImageData> imageData;

  double factor = .5;
  int newSize[2];
  int windowFunction = 0;

  // Verify input arguments
  if ( argc > 1 )
  {
    // Read the image
    vtkSmartPointer<vtkImageReader2Factory> readerFactory =
      vtkSmartPointer<vtkImageReader2Factory>::New();
    vtkSmartPointer<vtkImageReader2> reader =
      readerFactory->CreateImageReader2(argv[1]);
    reader->SetFileName(argv[1]);
    reader->Update();

    imageData = reader->GetOutput();
    if (argc > 2)
    {
      factor = atof(argv[2]);
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

  std::cout << "Original dimensions: "
            << imageData->GetDimensions()[0] << ", "
            << imageData->GetDimensions()[1]
            << std::endl;
  newSize[0] = imageData->GetDimensions()[0] * factor;
  newSize[1] = imageData->GetDimensions()[1] * factor;
  std::cout << "New dimensions: "
            << newSize[0] << ", "
            << newSize[1]
            << std::endl;

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // One camera for all
  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();

  // Create one text property for all
  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(20);
  textProperty->SetJustificationToCentered();
  textProperty->SetColor(0.3, 0.3, 0.3);

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();


  std::vector<vtkSmartPointer<vtkRenderer> > renderers;
  for (int i = -1; i <= 10; ++i)
  {
    vtkSmartPointer<vtkImageSincInterpolator> interpolator =
      vtkSmartPointer<vtkImageSincInterpolator>::New();
    windowFunction = i;
    interpolator->UseWindowParameterOn();

    vtkSmartPointer<vtkImageResize> resize =
      vtkSmartPointer<vtkImageResize>::New();
    resize->SetInputData(imageData);
    resize->SetInterpolator(interpolator);
    resize->SetOutputDimensions(newSize[0], newSize[1], 1);
    resize->InterpolateOn();

    // Create an image actor to display the image
    vtkSmartPointer<vtkImageActor> imageActor =
      vtkSmartPointer<vtkImageActor>::New();
    imageActor->GetMapper()->SetInputConnection(resize->GetOutputPort());
    imageActor->InterpolateOff();

    // Create textActors
    vtkSmartPointer<vtkTextMapper> textMapper =
      vtkSmartPointer<vtkTextMapper>::New();
    textMapper->SetTextProperty(textProperty);
    if (windowFunction < 0)
    {
      resize->InterpolateOff();
      textMapper->SetInput("Nearest neighbor");
    }
    else
    {
      resize->InterpolateOn();
      interpolator->SetWindowFunction(windowFunction);
      textMapper->SetInput(interpolator->GetWindowFunctionAsString());
    }

    vtkSmartPointer<vtkActor2D> textActor =
      vtkSmartPointer<vtkActor2D>::New();
    textActor->SetMapper(textMapper);
    textActor->SetPosition(100, 16);
    // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(imageActor);
  renderer->AddActor(textActor);;
  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());
  renderer->SetActiveCamera(camera);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Dolly(5);
  renderer->ResetCameraClippingRange();
  renderers.push_back(renderer);
  renderWindow->AddRenderer(renderer);
  }
  // Setup viewports for the renderers
  int rendererSize = 200;
  unsigned int xGridDimensions = 4;
  unsigned int yGridDimensions = 3;
  renderWindow->SetSize(
    rendererSize * xGridDimensions, rendererSize * yGridDimensions);
  for (int row = 0; row < static_cast<int>(yGridDimensions); row++)
  {
    for (int col = 0; col < static_cast<int>(xGridDimensions); col++)
    {
      int index = row * xGridDimensions + col;

      // (xmin, ymin, xmax, ymax)
      double viewport[4] = {
        static_cast<double>(col) * rendererSize /
        (xGridDimensions * rendererSize),
        static_cast<double>(yGridDimensions - (row + 1)) * rendererSize /
        (yGridDimensions * rendererSize),
        static_cast<double>(col + 1) * rendererSize /
        (xGridDimensions * rendererSize),
        static_cast<double>(yGridDimensions - row) * rendererSize /
        (yGridDimensions * rendererSize)};
      renderers[index]->SetViewport(viewport);
    }
  }

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
