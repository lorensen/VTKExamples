#include <vtkImageActor.h>
#include <vtkImageCast.h>
#include <vtkImageCast.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMathematics.h>
#include <vtkImageProperty.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageShiftScale.h>
#include <vtkInteractorStyleImage.h>
#include <vtkInteractorStyleImage.h>
#include <vtkNamedColors.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSampleFunction.h>
#include <vtkSmartPointer.h>
#include <vtkSphere.h>

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

  vtkSmartPointer<vtkImageCast> cast =
    vtkSmartPointer<vtkImageCast>::New();
  cast->SetInputConnection(reader->GetOutputPort());
  cast->SetOutputScalarTypeToDouble();

// get rid of discrete scalars);
  vtkSmartPointer<vtkImageGaussianSmooth> smooth =
    vtkSmartPointer<vtkImageGaussianSmooth>::New();
  smooth->SetInputConnection(cast->GetOutputPort());
  smooth->SetStandardDeviations(0.8, 0.8, 0);

  vtkSmartPointer<vtkSphere> m1 =
    vtkSmartPointer<vtkSphere>::New();
  m1->SetCenter(310, 130, 0);
  m1->SetRadius(0);

  vtkSmartPointer<vtkSampleFunction> m2 =
    vtkSmartPointer<vtkSampleFunction>::New();
  m2->SetImplicitFunction(m1);
  m2->SetModelBounds(0, 264, 0, 264, 0, 1);
  m2->SetSampleDimensions(264, 264, 1);

  vtkSmartPointer<vtkImageShiftScale> m3 =
    vtkSmartPointer<vtkImageShiftScale>::New();
  m3->SetInputConnection(m2->GetOutputPort());
  m3->SetScale(0.000095);

  vtkSmartPointer<vtkImageMathematics> div =
    vtkSmartPointer<vtkImageMathematics>::New();
  div->SetInputConnection(0, smooth->GetOutputPort());
  div->SetInputConnection(1, m3->GetOutputPort());
  div->SetOperationToMultiply();

  // Create actors
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  double colorWindow = 256.0;
  double colorLevel = 127.5;
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(cast->GetOutputPort());
  originalActor->GetProperty()->SetColorWindow(colorWindow);
  originalActor->GetProperty()->SetColorLevel(colorLevel);

  vtkSmartPointer<vtkImageActor> filteredActor =
    vtkSmartPointer<vtkImageActor>::New();
  filteredActor->GetMapper()->SetInputConnection(div->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double filteredViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  vtkSmartPointer<vtkRenderer> filteredRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  filteredRenderer->SetViewport(filteredViewport);
  filteredRenderer->AddActor(filteredActor);
  filteredRenderer->ResetCamera();
  filteredRenderer->SetBackground(colors->GetColor3d("LightSlateGray").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(filteredRenderer);

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
