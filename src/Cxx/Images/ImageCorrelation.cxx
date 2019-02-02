#include <vtkSmartPointer.h>
#include <vtkImageShiftScale.h>
#include <vtkImageCast.h>
#include <vtkImageMapper3D.h>
#include <vtkMath.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageCorrelation.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageActor.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetNumberOfScalarComponents(3);
  imageSource->SetScalarTypeToUnsignedChar();
  imageSource->SetExtent(0, 300, 0, 300, 0, 0);
  imageSource->SetDrawColor(0, 0, 0);
  imageSource->FillBox(0, 300, 0, 300);
  imageSource->SetDrawColor(255, 0, 0); //red
  imageSource->FillTriangle(10, 100,  190, 150,  40, 250);
  imageSource->Update();

  // Create an actor
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    imageSource->GetOutputPort());
 
  // Create a kernel
  vtkSmartPointer<vtkImageCanvasSource2D> kernelSource = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  kernelSource->SetNumberOfScalarComponents(3);
  kernelSource->SetScalarTypeToUnsignedChar();
  kernelSource->SetExtent(0, 30, 0, 30, 0, 0);
  kernelSource->SetDrawColor(0, 0, 0);
  kernelSource->FillBox(0, 30, 0, 30);
  kernelSource->SetDrawColor(255, 0, 0); //red
  kernelSource->FillTriangle(10, 1,  25, 10,  1, 5);
  kernelSource->Update();

  // Create an actor
  vtkSmartPointer<vtkImageActor> kernelActor =
    vtkSmartPointer<vtkImageActor>::New();
  kernelActor->GetMapper()->SetInputConnection(
    kernelSource->GetOutputPort());

  // Compute the correlation
  vtkSmartPointer<vtkImageCorrelation> correlationFilter = 
    vtkSmartPointer<vtkImageCorrelation>::New();
  correlationFilter->SetInputConnection(0, imageSource->GetOutputPort());
  correlationFilter->SetInputConnection(1, kernelSource->GetOutputPort());
  correlationFilter->Update();

  // At this point, corr pixels are doubles
  // So, get the scalar range
  vtkImageData* corr = correlationFilter->GetOutput();
  double corrRange[2];
  corr->GetPointData()->GetScalars()->GetRange( corrRange );
 
  // Rescale the correlation filter output. note that it implies
  // that minimum correlation is always zero.
  vtkSmartPointer<vtkImageShiftScale> imageScale =
    vtkSmartPointer<vtkImageShiftScale>::New();
  imageScale->SetInputConnection( correlationFilter->GetOutputPort( ));
  imageScale->SetScale( 255 / corrRange[1] );
  imageScale->SetOutputScalarTypeToUnsignedChar( );
  imageScale->Update();

  vtkSmartPointer<vtkImageCast> correlationCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  correlationCastFilter->SetInputConnection(imageScale->GetOutputPort());
  correlationCastFilter->SetOutputScalarTypeToUnsignedChar();
  correlationCastFilter->Update();

  // Create an actor
  vtkSmartPointer<vtkImageActor> correlationActor =
    vtkSmartPointer<vtkImageActor>::New();
  correlationActor->GetMapper()->SetInputConnection(
    correlationCastFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.33, 1.0};
  double kernelViewport[4] = {0.33, 0.0, 0.66, 1.0};
  double correlationViewport[4] = {0.66, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();

  vtkSmartPointer<vtkRenderer> kernelRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  kernelRenderer->SetViewport(kernelViewport);
  kernelRenderer->AddActor(kernelActor);
  kernelRenderer->ResetCamera();

  vtkSmartPointer<vtkRenderer> correlationRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  correlationRenderer->SetViewport(correlationViewport);
  correlationRenderer->AddActor(correlationActor);
  correlationRenderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(900,300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(kernelRenderer);
  renderWindow->AddRenderer(correlationRenderer);

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
