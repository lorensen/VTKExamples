#include <vtkSmartPointer.h>
#include <vtkImageCast.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageDivergence.h>
#include <vtkImageGradient.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageCorrelation.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageActor.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageMandelbrotSource.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageMandelbrotSource> source =
    vtkSmartPointer<vtkImageMandelbrotSource>::New();
  source->Update();

  vtkSmartPointer<vtkImageCast> originalCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  originalCastFilter->SetInputConnection(source->GetOutputPort());
  originalCastFilter->SetOutputScalarTypeToFloat();
  originalCastFilter->Update();
  
  // Compute the gradient (to produce a vector field)
  vtkSmartPointer<vtkImageGradient> gradientFilter =
    vtkSmartPointer<vtkImageGradient>::New();
  gradientFilter->SetInputConnection(source->GetOutputPort());
  gradientFilter->Update();
  
  vtkSmartPointer<vtkImageDivergence> divergenceFilter = 
    vtkSmartPointer<vtkImageDivergence>::New();
  divergenceFilter->SetInputConnection(gradientFilter->GetOutputPort());
  divergenceFilter->Update();

  vtkSmartPointer<vtkImageCast> divergenceCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  divergenceCastFilter->SetInputConnection(divergenceFilter->GetOutputPort());
  divergenceCastFilter->SetOutputScalarTypeToFloat();
  divergenceCastFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    originalCastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> divergenceActor =
    vtkSmartPointer<vtkImageActor>::New();
  divergenceActor->GetMapper()->SetInputConnection(
    divergenceCastFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};
  
  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(leftViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();

  vtkSmartPointer<vtkRenderer> divergenceRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  divergenceRenderer->SetViewport(rightViewport);
  divergenceRenderer->AddActor(divergenceActor);
  divergenceRenderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600,300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(divergenceRenderer);

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
