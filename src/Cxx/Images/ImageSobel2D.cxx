#include <vtkSmartPointer.h>
#include <vtkImageMathematics.h>
#include <vtkPointData.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageSobel2D.h>
#include <vtkImageMagnitude.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageShiftScale.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageEllipsoidSource.h>
#include <vtkImageCast.h>
#include <vtkGlyph3DMapper.h>
#include <vtkArrowSource.h>

int main(int, char *[])
{
  // Create an image of a rectangle
  vtkSmartPointer<vtkImageCanvasSource2D> source = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetScalarTypeToUnsignedChar();
  source->SetExtent(0, 200, 0, 200, 0, 0);
  source->SetDrawColor(0,0,0);
  source->FillBox(0,200,0,200);
  source->SetDrawColor(255,0,0);
  source->FillBox(100,120,100,120);
  source->Update();

  // Find the x and y gradients using a sobel filter
  vtkSmartPointer<vtkImageSobel2D> sobelFilter = 
    vtkSmartPointer<vtkImageSobel2D>::New();
  sobelFilter->SetInputConnection(source->GetOutputPort());
  sobelFilter->Update();
  
  // Extract the x component of the gradient
  vtkSmartPointer<vtkImageExtractComponents> extractXFilter = 
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractXFilter->SetComponents(0);
  extractXFilter->SetInputConnection(sobelFilter->GetOutputPort());
  extractXFilter->Update();
  
  double xRange[2];
  extractXFilter->GetOutput()->GetPointData()->GetScalars()->GetRange( xRange );

  vtkSmartPointer<vtkImageMathematics> xImageAbs =
  vtkSmartPointer<vtkImageMathematics>::New();
  xImageAbs->SetOperationToAbsoluteValue();
  xImageAbs->SetInputConnection(extractXFilter->GetOutputPort());
  xImageAbs->Update();
  
  vtkSmartPointer<vtkImageShiftScale> xShiftScale =
    vtkSmartPointer<vtkImageShiftScale>::New();
  xShiftScale->SetOutputScalarTypeToUnsignedChar();
  xShiftScale->SetScale( 255 / xRange[1] );
  xShiftScale->SetInputConnection(xImageAbs->GetOutputPort());
  xShiftScale->Update();

  // Extract the y component of the gradient
  vtkSmartPointer<vtkImageExtractComponents> extractYFilter = 
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractYFilter->SetComponents(1);
  extractYFilter->SetInputConnection(sobelFilter->GetOutputPort());
  extractYFilter->Update();
  
  double yRange[2];
  extractYFilter->GetOutput()->GetPointData()->GetScalars()->GetRange(yRange);
  
  vtkSmartPointer<vtkImageMathematics> yImageAbs =
    vtkSmartPointer<vtkImageMathematics>::New();
  yImageAbs->SetOperationToAbsoluteValue();
  yImageAbs->SetInputConnection(extractYFilter->GetOutputPort());
  yImageAbs->Update();
  
  vtkSmartPointer<vtkImageShiftScale> yShiftScale =
      vtkSmartPointer<vtkImageShiftScale>::New();
  yShiftScale->SetOutputScalarTypeToUnsignedChar();
  yShiftScale->SetScale( 255 / yRange[1] );
  yShiftScale->SetInputConnection(yImageAbs->GetOutputPort());
  yShiftScale->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(source->GetOutputPort());

  vtkSmartPointer<vtkImageActor> xActor =
    vtkSmartPointer<vtkImageActor>::New();
  xActor->GetMapper()->SetInputConnection(xShiftScale->GetOutputPort());

  vtkSmartPointer<vtkImageActor> yActor =
    vtkSmartPointer<vtkImageActor>::New();
  yActor->GetMapper()->SetInputConnection(yShiftScale->GetOutputPort());

  vtkSmartPointer<vtkArrowSource> arrowSource =
    vtkSmartPointer<vtkArrowSource>::New();
  sobelFilter->GetOutput()->GetPointData()->SetActiveVectors("ImageScalarsGradient");

  vtkSmartPointer<vtkGlyph3DMapper> sobelMapper =
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  sobelMapper->ScalingOn();
  sobelMapper->SetScaleFactor(.05);
  sobelMapper->SetSourceConnection(arrowSource->GetOutputPort());
  sobelMapper->SetInputConnection(sobelFilter->GetOutputPort());
  sobelMapper->Update();

  vtkSmartPointer<vtkActor> sobelActor =
    vtkSmartPointer<vtkActor>::New();
  sobelActor->SetMapper(sobelMapper);

   // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.25, 1.0};
  double xViewport[4] = {0.25, 0.0, 0.5, 1.0};
  double yViewport[4] = {0.5, 0.0, 0.75, 1.0};
  double sobelViewport[4] = {0.75, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> xRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  xRenderer->SetViewport(xViewport);
  xRenderer->AddActor(xActor);
  xRenderer->ResetCamera();
  xRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderer> yRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  yRenderer->SetViewport(yViewport);
  yRenderer->AddActor(yActor);
  yRenderer->ResetCamera();
  yRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderer> sobelRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  sobelRenderer->SetViewport(sobelViewport);
  sobelRenderer->AddActor(sobelActor);
  sobelRenderer->ResetCamera();
  sobelRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(1000,250);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(xRenderer);
  renderWindow->AddRenderer(yRenderer);
  renderWindow->AddRenderer(sobelRenderer);

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
