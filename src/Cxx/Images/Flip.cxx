#include <vtkImageData.h>
#include <vtkImageCast.h>
#include <vtkSmartPointer.h>
#include <vtkImageMapper3D.h>
#include <vtkImageFlip.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkImageActor.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageMandelbrotSource> source =
    vtkSmartPointer<vtkImageMandelbrotSource>::New();
  source->Update();

  vtkSmartPointer<vtkImageCast> castSource =
    vtkSmartPointer<vtkImageCast>::New();
  castSource->SetOutputScalarTypeToUnsignedChar();
  castSource->SetInputConnection(source->GetOutputPort());
  castSource->Update();
  
  vtkSmartPointer<vtkImageFlip> flipXFilter =
    vtkSmartPointer<vtkImageFlip>::New();
  flipXFilter->SetFilteredAxis(0); // flip x axis
  flipXFilter->SetInputConnection(source->GetOutputPort());
  flipXFilter->Update();

  vtkSmartPointer<vtkImageCast> castXFilter =
    vtkSmartPointer<vtkImageCast>::New();
  castXFilter->SetOutputScalarTypeToUnsignedChar();
  castXFilter->SetInputConnection(flipXFilter->GetOutputPort());
  castXFilter->Update();

  vtkSmartPointer<vtkImageFlip> flipYFilter =
    vtkSmartPointer<vtkImageFlip>::New();
  flipYFilter->SetFilteredAxis(1); // flip y axis
  flipYFilter->SetInputConnection(source->GetOutputPort());
  flipYFilter->Update();

  vtkSmartPointer<vtkImageCast> castYFilter =
    vtkSmartPointer<vtkImageCast>::New();
  castYFilter->SetOutputScalarTypeToUnsignedChar();
  castYFilter->SetInputConnection(flipYFilter->GetOutputPort());
  castYFilter->Update();

  vtkSmartPointer<vtkImageFlip> flipZFilter =
    vtkSmartPointer<vtkImageFlip>::New();
  flipZFilter->SetFilteredAxis(2); // flip z axis
  flipZFilter->SetInputConnection(source->GetOutputPort());
  flipZFilter->Update();

  vtkSmartPointer<vtkImageCast> castZFilter =
    vtkSmartPointer<vtkImageCast>::New();
  castZFilter->SetOutputScalarTypeToUnsignedChar();
  castZFilter->SetInputConnection(flipZFilter->GetOutputPort());
  castZFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> inputActor =
    vtkSmartPointer<vtkImageActor>::New();
  inputActor->GetMapper()->SetInputConnection(castSource->GetOutputPort());

  vtkSmartPointer<vtkImageActor> xActor =
    vtkSmartPointer<vtkImageActor>::New();
  xActor->GetMapper()->SetInputConnection(castXFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> yActor =
    vtkSmartPointer<vtkImageActor>::New();
  yActor->GetMapper()->SetInputConnection(castYFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> zActor =
    vtkSmartPointer<vtkImageActor>::New();
  zActor->GetMapper()->SetInputConnection(castZFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double inputViewport[4] = {0.0, 0.0, 0.25, 1.0};
  double xViewport[4] = {0.25, 0.0, 0.5, 1.0};
  double yViewport[4] = {0.5, 0.0, 0.75, 1.0};
  double zViewport[4] = {0.75, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> inputRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  inputRenderer->SetViewport(inputViewport);
  inputRenderer->AddActor(inputActor);
  inputRenderer->ResetCamera();
  inputRenderer->SetBackground(.4, .5, .9);

  vtkSmartPointer<vtkRenderer> xRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  xRenderer->SetViewport(xViewport);
  xRenderer->AddActor(xActor);
  xRenderer->ResetCamera();
  xRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> yRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  yRenderer->SetViewport(yViewport);
  yRenderer->AddActor(yActor);
  yRenderer->ResetCamera();
  yRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderer> zRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  zRenderer->SetViewport(zViewport);
  zRenderer->AddActor(zActor);
  zRenderer->ResetCamera();
  zRenderer->SetBackground(.4, .5, .8);

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(1000, 250);
  renderWindow->AddRenderer(inputRenderer);
  renderWindow->AddRenderer(xRenderer);
  renderWindow->AddRenderer(yRenderer);
  renderWindow->AddRenderer(zRenderer);

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
