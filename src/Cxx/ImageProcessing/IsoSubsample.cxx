#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageMarchingCubes.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageShrink3D.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

#include <array>

int main (int argc, char *argv[])
{
  // Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  std::array<unsigned char , 4> actorColor{{235, 235, 235, 255}};
    colors->SetColor("ActorColor", actorColor.data());

  // Read the image
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> reader;
  reader.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  reader->SetFileName(argv[1]);
  reader->Update();

  // Smoothed pipeline
  vtkSmartPointer<vtkImageGaussianSmooth> smooth =
    vtkSmartPointer<vtkImageGaussianSmooth>::New();
  smooth->SetDimensionality(3);
  smooth->SetInputConnection(reader->GetOutputPort());
  smooth->SetStandardDeviations(1.75, 1.75, 0.0);
  smooth->SetRadiusFactor(2);

  vtkSmartPointer<vtkImageShrink3D> subsampleSmoothed =
    vtkSmartPointer<vtkImageShrink3D>::New();
  subsampleSmoothed->SetInputConnection(smooth->GetOutputPort());
  subsampleSmoothed->SetShrinkFactors(4, 4, 1);

  vtkSmartPointer<vtkImageMarchingCubes> isoSmoothed =
    vtkSmartPointer<vtkImageMarchingCubes>::New();
  isoSmoothed->SetInputConnection(smooth->GetOutputPort());
  isoSmoothed->SetValue(0, 1150);

  vtkSmartPointer<vtkPolyDataMapper> isoSmoothedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  isoSmoothedMapper->SetInputConnection(isoSmoothed->GetOutputPort());
  isoSmoothedMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> isoSmoothedActor =
    vtkSmartPointer<vtkActor>::New();
  isoSmoothedActor->SetMapper(isoSmoothedMapper);
  isoSmoothedActor->GetProperty()->SetColor(colors->GetColor3d("ActorColor").GetData());

  // Unsmoothed pipeline
  // Sub sample the data
  vtkSmartPointer<vtkImageShrink3D> subsample =
    vtkSmartPointer<vtkImageShrink3D>::New();
  subsample->SetInputConnection(reader->GetOutputPort());
  subsample->SetShrinkFactors(4, 4, 1);

  vtkSmartPointer<vtkImageMarchingCubes> iso =
    vtkSmartPointer<vtkImageMarchingCubes>::New();
  iso->SetInputConnection(subsample->GetOutputPort());
  iso->SetValue(0, 1150);

  vtkSmartPointer<vtkPolyDataMapper> isoMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  isoMapper->SetInputConnection(iso->GetOutputPort());
  isoMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> isoActor =
    vtkSmartPointer<vtkActor>::New();
  isoActor->SetMapper(isoMapper);
  isoActor->GetProperty()->SetColor(colors->GetColor3d("ActorColor").GetData());

  // Rendering Pipeline
  // Setup render window, renderer, and interactor
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  vtkSmartPointer<vtkRenderer> rendererLeft = 
    vtkSmartPointer<vtkRenderer>::New();
  rendererLeft->SetViewport(leftViewport);

  vtkSmartPointer<vtkRenderer> rendererRight = 
    vtkSmartPointer<vtkRenderer>::New();
  rendererRight->SetViewport(rightViewport);

  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(rendererLeft);
  renderWindow->AddRenderer(rendererRight);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  rendererLeft->AddActor(isoActor);
  rendererRight->AddActor(isoSmoothedActor);

  rendererLeft->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
  rendererLeft->GetActiveCamera()->SetPosition(0.0, -1.0, 0.0);
  rendererLeft->GetActiveCamera()->SetViewUp(0.0, 0.0, -1.0);
  rendererLeft->ResetCamera();
  rendererLeft->GetActiveCamera()->Azimuth(-20.0);
  rendererLeft->GetActiveCamera()->Elevation(20.0);
  rendererLeft->ResetCameraClippingRange();

  rendererLeft->SetBackground(colors->GetColor3d("SlateGray").GetData());
  rendererRight->SetBackground(colors->GetColor3d("LightSlateGray").GetData());
  rendererRight->SetActiveCamera(rendererLeft->GetActiveCamera());

  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
