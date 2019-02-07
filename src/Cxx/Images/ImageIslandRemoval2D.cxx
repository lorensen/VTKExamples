#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageIslandRemoval2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageEllipsoidSource.h>
#include <vtkImageCast.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetScalarTypeToUnsignedChar();
  imageSource->SetNumberOfScalarComponents(1);
  imageSource->SetExtent(0, 200, 0, 200, 0, 0);
  
  // Blank the image
  imageSource->SetDrawColor(0.0);
  imageSource->FillBox(0,200,0,200);

  // Draw a small box
  imageSource->SetDrawColor(255.0);
  imageSource->FillBox(100, 105, 100, 105);

  // Draw a large box
  imageSource->SetDrawColor(255.0);
  imageSource->FillBox(150, 170, 150, 170);
  
  imageSource->Update();

  vtkSmartPointer<vtkImageIslandRemoval2D> islandRemovalFilter = 
    vtkSmartPointer<vtkImageIslandRemoval2D>::New();
  islandRemovalFilter->SetAreaThreshold(50);
  islandRemovalFilter->SetIslandValue(255.0);
  islandRemovalFilter->SetReplaceValue(0.0);
  islandRemovalFilter->SetInputConnection(imageSource->GetOutputPort());
  islandRemovalFilter->Update();

  // Visualize
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(imageSource->GetOutputPort());

  vtkSmartPointer<vtkImageActor> islandRemovalActor =
    vtkSmartPointer<vtkImageActor>::New();
  islandRemovalActor->GetMapper()->SetInputConnection(
    islandRemovalFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double islandRemovalViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> islandRemovalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  islandRemovalRenderer->SetViewport(islandRemovalViewport);
  islandRemovalRenderer->AddActor(islandRemovalActor);
  islandRemovalRenderer->ResetCamera();
  islandRemovalRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(islandRemovalRenderer);

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
