#include <vtkCamera.h>
#include <vtkImageActor.h>
#include <vtkImageConstantPad.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMapToWindowLevelColors.h>
#include <vtkImageMirrorPad.h>
#include <vtkImageProperty.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkInteractorStyleImage.h>
#include <vtkNamedColors.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

 int main (int argc, char *argv[])
{
  // Verify input arguments
  if ( argc < 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> reader;
  reader.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  reader->SetFileName(argv[1]);
  reader->Update();

  // Pipelines
  vtkSmartPointer<vtkImageConstantPad> constantPad =
    vtkSmartPointer<vtkImageConstantPad>::New();
  constantPad->SetInputConnection(reader->GetOutputPort());
  constantPad->SetConstant(800);
  constantPad->SetOutputWholeExtent(-127, 383, -127, 383, 22, 22);

  vtkSmartPointer<vtkImageMirrorPad> mirrorPad =
    vtkSmartPointer<vtkImageMirrorPad>::New();
  mirrorPad->SetInputConnection(reader->GetOutputPort());
  mirrorPad->SetOutputWholeExtent(constantPad->GetOutputWholeExtent());

  // Create actors
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkImageMapToWindowLevelColors> constantPadColor =
    vtkSmartPointer<vtkImageMapToWindowLevelColors>::New();
  constantPadColor->SetWindow(2000);
  constantPadColor->SetLevel(1000);
  constantPadColor->SetInputConnection(constantPad->GetOutputPort());

  vtkSmartPointer<vtkImageActor> constantPadActor =
    vtkSmartPointer<vtkImageActor>::New();
  constantPadActor->GetMapper()->SetInputConnection(
    constantPadColor->GetOutputPort());
  constantPadActor->GetProperty()->SetInterpolationTypeToNearest();

  vtkSmartPointer<vtkImageMapToWindowLevelColors> mirrorPadColor =
    vtkSmartPointer<vtkImageMapToWindowLevelColors>::New();
  mirrorPadColor->SetWindow(2000);
  mirrorPadColor->SetLevel(1000);
  mirrorPadColor->SetInputConnection(mirrorPad->GetOutputPort());

  vtkSmartPointer<vtkImageActor> mirrorPadActor =
    vtkSmartPointer<vtkImageActor>::New();
  mirrorPadActor->GetMapper()->SetInputConnection(
    mirrorPadColor->GetOutputPort());
  mirrorPadActor->GetProperty()->SetInterpolationTypeToNearest();

  // Setup renderers
  vtkSmartPointer<vtkRenderer> constantPadRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  constantPadRenderer->SetViewport(0.0, 0.0, 0.5, 1.0);
  constantPadRenderer->AddActor(constantPadActor);
  constantPadRenderer->ResetCamera();
  constantPadRenderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  vtkSmartPointer<vtkRenderer> mirrorPadRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  mirrorPadRenderer->SetViewport(0.5, 0.0, 1.0, 1.0);
  mirrorPadRenderer->AddActor(mirrorPadActor);
  mirrorPadRenderer->SetActiveCamera(constantPadRenderer->GetActiveCamera());
  mirrorPadRenderer->SetBackground(colors->GetColor3d("LightSlateGray").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(constantPadRenderer);
  renderWindow->AddRenderer(mirrorPadRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  constantPadRenderer->GetActiveCamera()->Dolly(1.2);
  constantPadRenderer->ResetCameraClippingRange();
  renderWindow->Render();
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
