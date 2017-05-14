#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageThreshold.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageMapper3D.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>
#include <vtkImageMandelbrotSource.h>
 
int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageMandelbrotSource> imageSource =
    vtkSmartPointer<vtkImageMandelbrotSource>::New();
  imageSource->Update();
 
  vtkSmartPointer<vtkImageThreshold> imageThreshold = 
    vtkSmartPointer<vtkImageThreshold>::New();
  imageThreshold->SetInputConnection(imageSource->GetOutputPort());
  unsigned char lower = 100;
  unsigned char upper = 200;
 
  imageThreshold->ThresholdBetween(lower, upper);
  imageThreshold->ReplaceInOn();
  imageThreshold->SetInValue(255);
  imageThreshold->Update();
 
  // Create actors
  vtkSmartPointer<vtkImageActor> inputActor =
    vtkSmartPointer<vtkImageActor>::New();
  inputActor->GetMapper()->SetInputConnection(
    imageSource->GetOutputPort());
 
  vtkSmartPointer<vtkImageActor> thresholdedActor =
    vtkSmartPointer<vtkImageActor>::New();
  thresholdedActor->GetMapper()->SetInputConnection(
    imageThreshold->GetOutputPort());
 
  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
 
  // And one interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
 
  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};
 
  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);
 
  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);
 
  leftRenderer->AddActor(inputActor);
  rightRenderer->AddActor(thresholdedActor);
 
  leftRenderer->ResetCamera();
  rightRenderer->ResetCamera();
 
  renderWindow->Render();
  interactor->Start();
 
  return EXIT_SUCCESS;
}
