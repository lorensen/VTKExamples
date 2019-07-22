#include <vtkSmartPointer.h>
#include <vtkImageMapper3D.h>
#include <vtkMath.h>
#include <vtkImageData.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageMathematics.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetNumberOfScalarComponents(3);
  imageSource->SetScalarTypeToUnsignedChar();
  imageSource->SetExtent(0, 4, 0, 4, 0, 0);
  imageSource->SetDrawColor(100.0, 0, 0);
  imageSource->FillBox(0, 4, 0, 4);
  imageSource->Update();
  
  vtkSmartPointer<vtkImageMathematics> imageMath = 
    vtkSmartPointer<vtkImageMathematics>::New();
  imageMath->SetOperationToMultiplyByK();
  imageMath->SetConstantK(2.0);
  imageMath->SetInputConnection(imageSource->GetOutputPort());
  imageMath->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    imageSource->GetOutputPort());

  vtkSmartPointer<vtkImageActor> mathActor =
    vtkSmartPointer<vtkImageActor>::New();
  mathActor->GetMapper()->SetInputConnection(
    imageMath->GetOutputPort());

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

  vtkSmartPointer<vtkRenderer> mathRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  mathRenderer->SetViewport(rightViewport);
  mathRenderer->AddActor(mathActor);
  mathRenderer->ResetCamera();
  mathRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(mathRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  renderWindowInteractor->SetInteractorStyle(style);

  renderWindow->Render();
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
