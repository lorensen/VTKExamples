#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageConvolve.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageMandelbrotSource> source =
    vtkSmartPointer<vtkImageMandelbrotSource>::New();
  source->Update();

  vtkSmartPointer<vtkImageCast> originalCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  originalCastFilter->SetInputConnection(source->GetOutputPort());
  originalCastFilter->SetOutputScalarTypeToUnsignedChar();
  originalCastFilter->Update();
  
  vtkSmartPointer<vtkImageConvolve> convolveFilter =
    vtkSmartPointer<vtkImageConvolve>::New();
  convolveFilter->SetInputConnection(source->GetOutputPort());
  double kernel[9] = {1,1,1,1,1,1,1,1,1};
  convolveFilter->SetKernel3x3(kernel);
  convolveFilter->Update();

  vtkSmartPointer<vtkImageCast> convolvedCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  convolvedCastFilter->SetInputConnection(convolveFilter->GetOutputPort());
  convolvedCastFilter->SetOutputScalarTypeToUnsignedChar();
  convolvedCastFilter->Update();

  // Create an actor
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    originalCastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> convolvedActor =
    vtkSmartPointer<vtkImageActor>::New();
  convolvedActor->GetMapper()->SetInputConnection(
    convolvedCastFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};
  
  // Setup renderer
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(leftViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();

  vtkSmartPointer<vtkRenderer> convolvedRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  convolvedRenderer->SetViewport(rightViewport);
  convolvedRenderer->AddActor(convolvedActor);
  convolvedRenderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600,300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(convolvedRenderer);

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
