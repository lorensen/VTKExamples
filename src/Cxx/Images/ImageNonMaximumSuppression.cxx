#include <vtkSmartPointer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkImageSinusoidSource.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageGradient.h>
#include <vtkImageGradientMagnitude.h>
#include <vtkImageNonMaximumSuppression.h>
#include <vtkImageCast.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkImageSinusoidSource> source =
    vtkSmartPointer<vtkImageSinusoidSource>::New();
  source->Update();

  vtkSmartPointer<vtkImageCast> sourceCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  sourceCastFilter->SetOutputScalarTypeToUnsignedChar();
  sourceCastFilter->SetInputConnection(source->GetOutputPort());
  sourceCastFilter->Update();

  vtkSmartPointer<vtkImageGradient> gradientFilter =
    vtkSmartPointer<vtkImageGradient>::New();
  gradientFilter->SetInputConnection(source->GetOutputPort());

  vtkSmartPointer<vtkImageGradientMagnitude> gradientMagnitudeFilter =
    vtkSmartPointer<vtkImageGradientMagnitude>::New();
  gradientMagnitudeFilter->SetInputConnection(source->GetOutputPort());

  vtkSmartPointer<vtkImageCast> gradientMagnitudeCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  gradientMagnitudeCastFilter->SetOutputScalarTypeToUnsignedChar();
  gradientMagnitudeCastFilter->SetInputConnection(gradientMagnitudeFilter->GetOutputPort());
  gradientMagnitudeCastFilter->Update();
  
  vtkSmartPointer<vtkImageNonMaximumSuppression> suppressionFilter =
    vtkSmartPointer<vtkImageNonMaximumSuppression>::New();
  suppressionFilter->SetInputConnection(
    0, gradientMagnitudeFilter->GetOutputPort());
  suppressionFilter->SetInputConnection(
    1, gradientFilter->GetOutputPort());
  suppressionFilter->SetDimensionality(2);
  suppressionFilter->Update();

  vtkSmartPointer<vtkImageCast> suppressionCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  suppressionCastFilter->SetOutputScalarTypeToUnsignedChar();
  suppressionCastFilter->SetInputConnection(suppressionFilter->GetOutputPort());
  suppressionCastFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    sourceCastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> gradientMagnitudeActor =
    vtkSmartPointer<vtkImageActor>::New();
  gradientMagnitudeActor->GetMapper()->SetInputConnection(
    gradientMagnitudeCastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> suppressionActor =
    vtkSmartPointer<vtkImageActor>::New();
  suppressionActor->GetMapper()->SetInputConnection(
    suppressionCastFilter->GetOutputPort());
  
  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.33, 1.0};
  double gradientMagnitudeViewport[4] = {0.33, 0.0, 0.66, 1.0};
  double suppressionViewport[4] = {0.66, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> gradientMagnitudeRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  gradientMagnitudeRenderer->SetViewport(gradientMagnitudeViewport);
  gradientMagnitudeRenderer->AddActor(gradientMagnitudeActor);
  gradientMagnitudeRenderer->ResetCamera();
  gradientMagnitudeRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderer> suppressionRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  suppressionRenderer->SetViewport(suppressionViewport);
  suppressionRenderer->AddActor(suppressionActor);
  suppressionRenderer->ResetCamera();
  suppressionRenderer->SetBackground(.3, .5, .8);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(900, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(gradientMagnitudeRenderer);
  renderWindow->AddRenderer(suppressionRenderer);

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
