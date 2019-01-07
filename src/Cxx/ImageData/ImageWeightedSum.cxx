#include <vtkImageActor.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageCast.h>
#include <vtkImageData.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkImageMapper3D.h>
#include <vtkImageSinusoidSource.h>
#include <vtkImageWeightedSum.h>
#include <vtkInteractorStyleImage.h>
#include <vtkNamedColors.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <array>

int main(int, char *[]) {
  vtkNew<vtkNamedColors> colors;

  std::array<double, 4> bkgL = {{0.6, 0.5, 0.4, 1.0}};
  std::array<double, 4> bkgC = {{0.1, 0.5, 0.4, 1.0}};
  std::array<double, 4> bkgR = {{0.4, 0.5, 0.6, 1.0}};
  colors->SetColor("leftBkg", bkgL.data());
  colors->SetColor("centreBkg", bkgC.data());
  colors->SetColor("rightBkg", bkgR.data());

  // create an image
  vtkSmartPointer<vtkImageMandelbrotSource> source1 =
      vtkSmartPointer<vtkImageMandelbrotSource>::New();
  source1->SetWholeExtent(0, 255, 0, 255, 0, 0);
  source1->Update();

  vtkSmartPointer<vtkImageCast> source1Double =
      vtkSmartPointer<vtkImageCast>::New();
  source1Double->SetInputConnection(0, source1->GetOutputPort());
  source1Double->SetOutputScalarTypeToDouble();

  vtkSmartPointer<vtkImageSinusoidSource> source2 =
      vtkSmartPointer<vtkImageSinusoidSource>::New();
  source2->SetWholeExtent(0, 255, 0, 255, 0, 0);
  source2->Update();

  vtkSmartPointer<vtkImageWeightedSum> sumFilter =
      vtkSmartPointer<vtkImageWeightedSum>::New();
  sumFilter->SetWeight(0, .8);
  sumFilter->SetWeight(1, .2);
  sumFilter->AddInputConnection(source1Double->GetOutputPort());
  sumFilter->AddInputConnection(source2->GetOutputPort());

  sumFilter->Update();

  vtkSmartPointer<vtkImageCast> source1CastFilter =
      vtkSmartPointer<vtkImageCast>::New();
  source1CastFilter->SetInputConnection(source1->GetOutputPort());
  source1CastFilter->SetOutputScalarTypeToUnsignedChar();
  source1CastFilter->Update();

  vtkSmartPointer<vtkImageCast> source2CastFilter =
      vtkSmartPointer<vtkImageCast>::New();
  source2CastFilter->SetInputConnection(source2->GetOutputPort());
  source2CastFilter->SetOutputScalarTypeToUnsignedChar();
  source2CastFilter->Update();

  vtkSmartPointer<vtkImageCast> summedCastFilter =
      vtkSmartPointer<vtkImageCast>::New();
  summedCastFilter->SetInputConnection(sumFilter->GetOutputPort());
  summedCastFilter->SetOutputScalarTypeToUnsignedChar();
  summedCastFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> source1Actor =
      vtkSmartPointer<vtkImageActor>::New();
  source1Actor->GetMapper()->SetInputConnection(
      source1CastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> source2Actor =
      vtkSmartPointer<vtkImageActor>::New();
  source2Actor->GetMapper()->SetInputConnection(
      source2CastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> summedActor =
      vtkSmartPointer<vtkImageActor>::New();
  summedActor->GetMapper()->SetInputConnection(
      summedCastFilter->GetOutputPort());

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
  double leftViewport[4] = {0.0, 0.0, 0.33, 1.0};
  double centerViewport[4] = {0.33, 0.0, .66, 1.0};
  double rightViewport[4] = {0.66, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
      vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(colors->GetColor3d("leftBkg").GetData());

  vtkSmartPointer<vtkRenderer> centerRenderer =
      vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(centerRenderer);
  centerRenderer->SetViewport(centerViewport);
  centerRenderer->SetBackground(colors->GetColor3d("centreBkg").GetData());

  vtkSmartPointer<vtkRenderer> rightRenderer =
      vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(colors->GetColor3d("rightBkg").GetData());

  leftRenderer->AddActor(source1Actor);
  centerRenderer->AddActor(source2Actor);
  rightRenderer->AddActor(summedActor);

  leftRenderer->ResetCamera();
  centerRenderer->ResetCamera();
  rightRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
