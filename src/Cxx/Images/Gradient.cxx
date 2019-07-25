#include <vtkActor.h>
#include <vtkArrowSource.h>
#include <vtkCamera.h>
#include <vtkDoubleArray.h>
#include <vtkFieldDataToAttributeDataFilter.h>
#include <vtkGlyph3D.h>
#include <vtkImageActor.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageData.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageGradient.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMathematics.h>
#include <vtkImageRGBToHSV.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageShiftScale.h>
#include <vtkMaskPoints.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

int main(int argc, char* argv[])
{
  auto namedColors = vtkSmartPointer<vtkNamedColors>::New();
  namedColors->SetColor("Bkg", 0.2, 0.3, 0.6);

  vtkSmartPointer<vtkImageData> originalImage;
  vtkSmartPointer<vtkImageData> image;

  int onRatio = 1;
  double scaleFactor = 1.0;
  if (argc < 2)
  {
    // Create an image
    auto imageSource = vtkSmartPointer<vtkImageCanvasSource2D>::New();
    imageSource->SetScalarTypeToDouble();
    imageSource->SetNumberOfScalarComponents(1);
    imageSource->SetExtent(0, 6, 0, 6, 0, 0);
    imageSource->SetDrawColor(127, 127, 127); // Gray
    imageSource->FillBox(0, 6, 0, 6);
    imageSource->SetDrawColor(255, 255, 255); // White
    imageSource->FillBox(2, 4, 2, 4);
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
    auto readerFactory = vtkSmartPointer<vtkImageReader2Factory>::New();
    vtkSmartPointer<vtkImageReader2> reader;
    reader.TakeReference(readerFactory->CreateImageReader2(argv[1]));
    reader->SetFileName(argv[1]);

    // Convert to HSV and extract the Value
    auto hsvFilter = vtkSmartPointer<vtkImageRGBToHSV>::New();
    hsvFilter->SetInputConnection(reader->GetOutputPort());

    auto extractValue = vtkSmartPointer<vtkImageExtractComponents>::New();
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
  auto gradientFilter = vtkSmartPointer<vtkImageGradient>::New();
  gradientFilter->SetInputData(image);
  gradientFilter->SetDimensionality(2);
  gradientFilter->Update();

  // Extract the x component of the gradient
  auto extractXFilter = vtkSmartPointer<vtkImageExtractComponents>::New();
  extractXFilter->SetComponents(0);
  extractXFilter->SetInputConnection(gradientFilter->GetOutputPort());

  double xRange[2];

  extractXFilter->Update();
  extractXFilter->GetOutput()->GetPointData()->GetScalars()->GetRange(xRange);

  // Gradient could be negative, so take the absolute value
  auto imageAbsX = vtkSmartPointer<vtkImageMathematics>::New();
  imageAbsX->SetOperationToAbsoluteValue();
  imageAbsX->SetInputConnection(extractXFilter->GetOutputPort());

  // Scale the output (0,255)
  auto shiftScaleX = vtkSmartPointer<vtkImageShiftScale>::New();
  shiftScaleX->SetOutputScalarTypeToUnsignedChar();
  shiftScaleX->SetScale(255 / xRange[1]);
  shiftScaleX->SetInputConnection(imageAbsX->GetOutputPort());

  // Extract the y component of the gradient
  auto extractYFilter = vtkSmartPointer<vtkImageExtractComponents>::New();
  extractYFilter->SetComponents(1);
  extractYFilter->SetInputConnection(gradientFilter->GetOutputPort());

  double yRange[2];
  extractYFilter->Update();
  extractYFilter->GetOutput()->GetPointData()->GetScalars()->GetRange(yRange);

  // Gradient could be negative, so take the absolute value
  auto imageAbsY = vtkSmartPointer<vtkImageMathematics>::New();
  imageAbsY->SetOperationToAbsoluteValue();
  imageAbsY->SetInputConnection(extractYFilter->GetOutputPort());

  // Scale the output (0,255)
  auto shiftScaleY = vtkSmartPointer<vtkImageShiftScale>::New();
  shiftScaleY->SetOutputScalarTypeToUnsignedChar();
  shiftScaleY->SetScale(255 / yRange[1]);
  shiftScaleY->SetInputConnection(imageAbsY->GetOutputPort());

  // Create the Glyphs for the gradient
  auto arrowSource = vtkSmartPointer<vtkArrowSource>::New();

  // The gradient is 2D but Glyph3D needs 3D vectors. Add a 0 z-component
  // Also, ImageGradient generates a 2-component scalar for the
  // gradient, but Glyph3D needs normals or vectors
  auto zeroes = vtkSmartPointer<vtkDoubleArray>::New();
  zeroes->SetNumberOfComponents(1);
  zeroes->SetName("Zero");
  zeroes->SetNumberOfTuples(gradientFilter->GetOutput()
                                ->GetPointData()
                                ->GetScalars()
                                ->GetNumberOfTuples());
  zeroes->FillComponent(0, 0.0);
  gradientFilter->GetOutput()->GetPointData()->AddArray(zeroes);

  std::string scalarName =
      gradientFilter->GetOutput()->GetPointData()->GetScalars()->GetName();

  auto scalarsToVectors =
      vtkSmartPointer<vtkFieldDataToAttributeDataFilter>::New();
  scalarsToVectors->SetInputConnection(gradientFilter->GetOutputPort());
  scalarsToVectors->SetInputFieldToPointDataField();
  scalarsToVectors->SetOutputAttributeDataToPointData();
  scalarsToVectors->SetVectorComponent(0, scalarName.c_str(), 0);
  scalarsToVectors->SetVectorComponent(1, scalarName.c_str(), 1);
  scalarsToVectors->SetVectorComponent(2, "Zero", 0);

  // Select a small percentage of the gradients
  auto maskPoints = vtkSmartPointer<vtkMaskPoints>::New();
  maskPoints->SetInputConnection(scalarsToVectors->GetOutputPort());
  maskPoints->RandomModeOff();
  maskPoints->SetOnRatio(onRatio);

  auto vectorGradientGlyph = vtkSmartPointer<vtkGlyph3D>::New();
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

  auto vectorGradientMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  vectorGradientMapper->SetInputConnection(
      vectorGradientGlyph->GetOutputPort());
  vectorGradientMapper->ScalarVisibilityOff();

  auto vectorGradientActor = vtkSmartPointer<vtkActor>::New();
  vectorGradientActor->SetMapper(vectorGradientMapper);
  vectorGradientActor->GetProperty()->SetColor(
      namedColors->GetColor3d("Tomato").GetData());

  // Create a renderer, render window, and interactor
  // vtkSmartPointer<vtkCamera> sharedCamera =
  //  vtkSmartPointer<vtkCamera>::New();
  auto originalRenderer = vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->SetBackground(namedColors->GetColor3d("Bkg").GetData());

  auto xGradientRenderer = vtkSmartPointer<vtkRenderer>::New();
  xGradientRenderer->SetViewport(xGradientViewport);
  xGradientRenderer->SetBackground(namedColors->GetColor3d("Bkg").GetData());

  auto yGradientRenderer = vtkSmartPointer<vtkRenderer>::New();
  yGradientRenderer->SetViewport(yGradientViewport);
  yGradientRenderer->SetBackground(namedColors->GetColor3d("Bkg").GetData());

  auto vectorGradientRenderer = vtkSmartPointer<vtkRenderer>::New();
  vectorGradientRenderer->SetViewport(vectorGradientViewport);
  vectorGradientRenderer->SetBackground(
      namedColors->GetColor3d("Bkg").GetData());

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(1000, 250);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(xGradientRenderer);
  renderWindow->AddRenderer(yGradientRenderer);
  renderWindow->AddRenderer(vectorGradientRenderer);

  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  auto originalActor = vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputData(originalImage);
  originalActor->InterpolateOff();

  auto xGradientActor = vtkSmartPointer<vtkImageActor>::New();
  xGradientActor->InterpolateOff();

  xGradientActor->GetMapper()->SetInputConnection(shiftScaleX->GetOutputPort());

  auto yGradientActor = vtkSmartPointer<vtkImageActor>::New();

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
