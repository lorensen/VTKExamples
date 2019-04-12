#include <vtkSmartPointer.h>
#include <vtkImageRange3D.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageMapper3D.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>

int main(int argc, char* argv[])
{
  // Parse input arguments
  if ( argc != 2 )
  {
    std::cout << "Required parameters: Filename.jpg" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> reader;
  reader.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  reader->SetFileName(argv[1]);

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    reader->GetOutputPort());

  vtkSmartPointer<vtkImageRange3D> rangeFilter =
    vtkSmartPointer<vtkImageRange3D>::New();
  rangeFilter->SetInputConnection(reader->GetOutputPort());
  rangeFilter->SetKernelSize(5,5,5);
  rangeFilter->Update();


  vtkSmartPointer<vtkImageCast> rangeCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  rangeCastFilter->SetInputConnection(rangeFilter->GetOutputPort());
  rangeCastFilter->SetOutputScalarTypeToUnsignedChar();
  rangeCastFilter->Update();

  vtkSmartPointer<vtkImageActor> rangeActor =
    vtkSmartPointer<vtkImageActor>::New();
  rangeActor->GetMapper()->SetInputConnection(
    rangeCastFilter->GetOutputPort());

   // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rangeViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> rangeRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  rangeRenderer->SetViewport(rangeViewport);
  rangeRenderer->AddActor(rangeActor);
  rangeRenderer->ResetCamera();
  rangeRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(rangeRenderer);

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
