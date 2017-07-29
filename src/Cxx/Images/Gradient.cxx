#include <vtkSmartPointer.h>
#include <vtkVersion.h>

#include <vtkImageData.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>

#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>
#include <vtkPolyDataMapper.h>

#include <vtkImageMapper3D.h>
#include <vtkProperty.h>
#include <vtkImageActor.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageRGBToHSV.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageGradient.h>
#include <vtkImageShiftScale.h>
#include <vtkFieldDataToAttributeDataFilter.h>
#include <vtkImageMathematics.h>
#include <vtkMaskPoints.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkImageData> originalImage =
    vtkSmartPointer<vtkImageData>::New();
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();

  int onRatio;
  double scaleFactor;
  if (argc < 2)
  {
    // Create an image
    vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
      vtkSmartPointer<vtkImageCanvasSource2D>::New();
    imageSource->SetScalarTypeToDouble();
    imageSource->SetNumberOfScalarComponents(1);
    imageSource->SetExtent(0, 6, 0, 6, 0, 0);
    imageSource->SetDrawColor(127, 127, 127);
    imageSource->FillBox(0, 6, 0, 6);
    imageSource->SetDrawColor(255, 255, 255);
    imageSource->FillBox(2, 4,  2, 4);
    imageSource->Update();

    originalImage = imageSource->GetOutput();
    image = imageSource->GetOutput();

    // Use all of the points
    onRatio = 1;
    scaleFactor = .01;
  }
  else
  {
    // Read an image
    vtkSmartPointer<vtkImageReader2Factory> readerFactory =
      vtkSmartPointer<vtkImageReader2Factory>::New();
    vtkSmartPointer<vtkImageReader2> reader = readerFactory->CreateImageReader2(argv[1]);
    reader->SetFileName(argv[1]);
    reader->Update();

    // Convert to HSV and extract the Value
    vtkSmartPointer<vtkImageRGBToHSV> hsvFilter =
      vtkSmartPointer<vtkImageRGBToHSV>::New();
    hsvFilter->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkImageExtractComponents> extractValue =
      vtkSmartPointer<vtkImageExtractComponents>::New();
    extractValue->SetInputConnection(hsvFilter->GetOutputPort());
    extractValue->SetComponents(2);
    extractValue->Update();

    image = extractValue->GetOutput();
    originalImage = reader->GetOutput();

    // Use 1% of the points
    onRatio = image->GetPointData()->GetScalars()->GetNumberOfTuples() /
      (image->GetPointData()->GetScalars()->GetNumberOfTuples() * .01);
    scaleFactor = 1.0;
  }

  // Compute the gradient of the Value
  vtkSmartPointer<vtkImageGradient> gradientFilter =
    vtkSmartPointer<vtkImageGradient>::New();
#if VTK_MAJOR_VERSION <= 5
  gradientFilter->SetInput(image);
#else
  gradientFilter->SetInputData(image);
#endif
  gradientFilter->SetDimensionality(2);
  gradientFilter->Update();

  // Extract the x component of the gradient
  vtkSmartPointer<vtkImageExtractComponents> extractXFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractXFilter->SetComponents(0);
  extractXFilter->SetInputConnection(gradientFilter->GetOutputPort());

  double xRange[2];

  extractXFilter->Update();
  extractXFilter->GetOutput()->GetPointData()->GetScalars()->GetRange(xRange);

  // Gradient could be negative, so take the absolute value
  vtkSmartPointer<vtkImageMathematics> imageAbsX =
    vtkSmartPointer<vtkImageMathematics>::New();
  imageAbsX->SetOperationToAbsoluteValue();
  imageAbsX->SetInputConnection(extractXFilter->GetOutputPort());

  // Scale the output (0,255)
  vtkSmartPointer<vtkImageShiftScale> shiftScaleX =
    vtkSmartPointer<vtkImageShiftScale>::New();
  shiftScaleX->SetOutputScalarTypeToUnsignedChar();
  shiftScaleX->SetScale(255 / xRange[1]);
  shiftScaleX->SetInputConnection(imageAbsX->GetOutputPort());

  // Extract the y component of the gradient
  vtkSmartPointer<vtkImageExtractComponents> extractYFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractYFilter->SetComponents(1);
  extractYFilter->SetInputConnection(gradientFilter->GetOutputPort());

  double yRange[2];
  extractYFilter->Update();
  extractYFilter->GetOutput()->GetPointData()->GetScalars()->GetRange(yRange);

  // Gradient could be negative, so take the absolute value
  vtkSmartPointer<vtkImageMathematics> imageAbsY =
    vtkSmartPointer<vtkImageMathematics>::New();
  imageAbsY->SetOperationToAbsoluteValue();
  imageAbsY->SetInputConnection(extractYFilter->GetOutputPort());

  // Scale the output (0,255)
  vtkSmartPointer<vtkImageShiftScale> shiftScaleY =
    vtkSmartPointer<vtkImageShiftScale>::New();
  shiftScaleY->SetOutputScalarTypeToUnsignedChar();
  shiftScaleY->SetScale(255 / yRange[1]);
  shiftScaleY->SetInputConnection(imageAbsY->GetOutputPort());

  // Create the Glyphs for the gradient
  vtkSmartPointer<vtkArrowSource> arrowSource =
    vtkSmartPointer<vtkArrowSource>::New();

  // The gradient is 2D but Glyph3D needs 3D vectors. Add a 0 z-component
  // Also, ImageGradient generates a 2-component scalar for the
  // gradient, but Glyph3D needs normals or vectors
  vtkSmartPointer<vtkDoubleArray> zeroes =
    vtkSmartPointer<vtkDoubleArray>::New();
  zeroes->SetNumberOfComponents(1);
  zeroes->SetName("Zero");
  zeroes->SetNumberOfTuples(gradientFilter->GetOutput()->GetPointData()->GetScalars()->GetNumberOfTuples());
  zeroes->FillComponent(0, 0.0);
  gradientFilter->GetOutput()->GetPointData()->AddArray(zeroes);

  std::string scalarName =
    gradientFilter->GetOutput()->GetPointData()->GetScalars()->GetName();

  vtkSmartPointer<vtkFieldDataToAttributeDataFilter> scalarsToVectors =
    vtkSmartPointer<vtkFieldDataToAttributeDataFilter>::New();
  scalarsToVectors->SetInputConnection(gradientFilter->GetOutputPort());
  scalarsToVectors->SetInputFieldToPointDataField();
  scalarsToVectors->SetOutputAttributeDataToPointData();
  scalarsToVectors->SetVectorComponent(0, scalarName.c_str(), 0);
  scalarsToVectors->SetVectorComponent(1, scalarName.c_str(), 1);
  scalarsToVectors->SetVectorComponent(2, "Zero", 0);

  // Select a small percentage of the gradients
  vtkSmartPointer<vtkMaskPoints> maskPoints =
    vtkSmartPointer<vtkMaskPoints>::New();
  maskPoints->SetInputConnection(scalarsToVectors->GetOutputPort());
  maskPoints->RandomModeOff();
  maskPoints->SetOnRatio(onRatio);

  vtkSmartPointer<vtkGlyph3D> vectorGradientGlyph =
    vtkSmartPointer<vtkGlyph3D>::New();
  vectorGradientGlyph->SetSourceConnection(arrowSource->GetOutputPort());
  vectorGradientGlyph->SetInputConnection(maskPoints->GetOutputPort());
  vectorGradientGlyph->SetScaleModeToScaleByVector();
  vectorGradientGlyph->SetVectorModeToUseVector();
  vectorGradientGlyph->SetScaleFactor(scaleFactor);

  // Visualize

  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.25, 1.0};
  double xGradientViewport[4] = {0.25, 0.0, 0.5, 1.0};
  double yGradientViewport[4] = {0.5, 0.0, 0.75, 1.0};
  double vectorGradientViewport[4] = {0.75, 0.0, 1.0, 1.0};

  vtkSmartPointer<vtkPolyDataMapper> vectorGradientMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vectorGradientMapper->SetInputConnection(vectorGradientGlyph->GetOutputPort());
  vectorGradientMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> vectorGradientActor =
    vtkSmartPointer<vtkActor>::New();
  vectorGradientActor->SetMapper(vectorGradientMapper);
  vectorGradientActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkCamera> sharedCamera =
    vtkSmartPointer<vtkCamera>::New();
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->SetBackground(.2, .3, .6);

  vtkSmartPointer<vtkRenderer> xGradientRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  xGradientRenderer->SetViewport(xGradientViewport);
  xGradientRenderer->SetBackground(.2, .3, .6);

  vtkSmartPointer<vtkRenderer> yGradientRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  yGradientRenderer->SetViewport(yGradientViewport);
  yGradientRenderer->SetBackground(.2, .3, .6);

  vtkSmartPointer<vtkRenderer> vectorGradientRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  vectorGradientRenderer->SetViewport(vectorGradientViewport);
  vectorGradientRenderer->SetBackground(.2, .3, .6);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(1000,250);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(xGradientRenderer);
  renderWindow->AddRenderer(yGradientRenderer);
  renderWindow->AddRenderer(vectorGradientRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  originalActor->GetMapper()->SetInput(originalImage);
#else
  originalActor->GetMapper()->SetInputData(originalImage);
#endif
  originalActor->InterpolateOff();

  vtkSmartPointer<vtkImageActor> xGradientActor =
    vtkSmartPointer<vtkImageActor>::New();
  xGradientActor->InterpolateOff();

  xGradientActor->GetMapper()->SetInputConnection(shiftScaleX->GetOutputPort());

  vtkSmartPointer<vtkImageActor> yGradientActor =
    vtkSmartPointer<vtkImageActor>::New();

  yGradientActor->GetMapper()->SetInputConnection(shiftScaleY->GetOutputPort());
  yGradientActor->InterpolateOff();

  // Add the actors to the scenes
  originalRenderer->AddActor(originalActor);
  xGradientRenderer->AddActor(xGradientActor);
  yGradientRenderer->AddActor(yGradientActor);
  vectorGradientRenderer->AddActor(vectorGradientActor);
  vectorGradientRenderer->AddActor(originalActor);

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
