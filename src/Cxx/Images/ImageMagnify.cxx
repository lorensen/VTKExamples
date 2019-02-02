#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageMagnify.h>
#include <vtkImageChangeInformation.h>

int main(int argc, char *argv[])
{
  // Handle the arguments
  if(argc < 2)
  {
    std::cout << "Required arguments: filename.png" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkPNGReader> reader =
    vtkSmartPointer<vtkPNGReader>::New();
  reader->SetFileName(argv[1]);

  // Increase the dimensions of the image
  vtkSmartPointer<vtkImageMagnify> magnifyFilter =
    vtkSmartPointer<vtkImageMagnify>::New();
  magnifyFilter->SetInputConnection(reader->GetOutputPort());
  magnifyFilter->SetMagnificationFactors(2,1,1);
  magnifyFilter->Update();

  // Adjust the spacing of the magnified image. This will stretch the
  // image
  vtkSmartPointer<vtkImageChangeInformation> changeFilter =
    vtkSmartPointer<vtkImageChangeInformation>::New();
  changeFilter->SetInputConnection(magnifyFilter->GetOutputPort());
  changeFilter->SetSpacingScale(
    magnifyFilter->GetMagnificationFactors()[0],
    magnifyFilter->GetMagnificationFactors()[1],
    magnifyFilter->GetMagnificationFactors()[2]);

  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> magnifiedActor =
    vtkSmartPointer<vtkImageActor>::New();
  magnifiedActor->GetMapper()->SetInputConnection(
    changeFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double magnifiedViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> magnifiedRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  magnifiedRenderer->SetViewport(magnifiedViewport);
  magnifiedRenderer->AddActor(magnifiedActor);
  magnifiedRenderer->ResetCamera();
  magnifiedRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(magnifiedRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return  EXIT_SUCCESS;
}
