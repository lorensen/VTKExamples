#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageMedian3D.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetNumberOfScalarComponents(1);
  imageSource->SetScalarTypeToUnsignedChar();
  unsigned int xmin = 0;
  unsigned int xmax = 20;
  unsigned int ymin = 0;
  unsigned int ymax = 20;
  imageSource->SetExtent(xmin, xmax, ymin, ymax, 0, 0);
  
  // Make the image all black
  imageSource->SetDrawColor(0.0);
  imageSource->FillBox(xmin, xmax, ymin, ymax);

  // Draw a big white square
  imageSource->SetDrawColor(255.0);
  imageSource->FillBox(5, 15, 5, 15);

  // Add some single white pixels
  imageSource->SetDrawColor(255.0);
  imageSource->FillBox(1, 1, 1, 1);
  imageSource->FillBox(17, 17, 17, 17);

  imageSource->Update();
  
  vtkSmartPointer<vtkImageMedian3D> medianFilter = 
    vtkSmartPointer<vtkImageMedian3D>::New();
  medianFilter->SetInputConnection(imageSource->GetOutputPort());
  medianFilter->SetKernelSize(3,3,1);
  medianFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    imageSource->GetOutputPort());

  vtkSmartPointer<vtkImageActor> medianActor =
    vtkSmartPointer<vtkImageActor>::New();
  medianActor->GetMapper()->SetInputConnection(
    medianFilter->GetOutputPort());

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
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> gradientMagnitudeRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  gradientMagnitudeRenderer->SetViewport(rightViewport);
  gradientMagnitudeRenderer->AddActor(medianActor);
  gradientMagnitudeRenderer->ResetCamera();
  gradientMagnitudeRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(gradientMagnitudeRenderer);

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
