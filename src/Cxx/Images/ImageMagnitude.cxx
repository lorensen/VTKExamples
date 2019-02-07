#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageMagnitude.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

int main(int, char *[])
{
  // Create an image of a rectangle
  vtkSmartPointer<vtkImageCanvasSource2D> source =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetScalarTypeToUnsignedChar();
  source->SetNumberOfScalarComponents(3);
  source->SetExtent(0, 200, 0, 200, 0, 0);

  // Clear the image
  source->SetDrawColor(0,0,0);
  source->FillBox(0,200,0,200);

  // Draw a red box
  source->SetDrawColor(255,0,0);
  source->FillBox(100,120,100,120);
  source->Update();

  vtkSmartPointer<vtkImageMagnitude> magnitudeFilter =
      vtkSmartPointer<vtkImageMagnitude>::New();
  magnitudeFilter->SetInputConnection(source->GetOutputPort());
  magnitudeFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    source->GetOutputPort());

  vtkSmartPointer<vtkImageActor> magnitudeActor =
    vtkSmartPointer<vtkImageActor>::New();
  magnitudeActor->GetMapper()->SetInputConnection(
    magnitudeFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double magnitudeViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> magnitudeRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  magnitudeRenderer->SetViewport(magnitudeViewport);
  magnitudeRenderer->AddActor(magnitudeActor);
  magnitudeRenderer->ResetCamera();
  magnitudeRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(magnitudeRenderer);

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
