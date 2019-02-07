#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCast.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageOpenClose3D.h>
#include <vtkImageThreshold.h>

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
  reader->Update();

  vtkSmartPointer<vtkImageOpenClose3D> openClose =
    vtkSmartPointer<vtkImageOpenClose3D>::New();
  openClose->SetInputConnection(reader->GetOutputPort());
  openClose->SetOpenValue(0);
  openClose->SetCloseValue(255);
  openClose->SetKernelSize(5, 5, 3);
  openClose->ReleaseDataFlagOff();
  openClose->GetOutput();
  openClose->GetCloseValue();
  openClose->GetOpenValue();

  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> openCloseActor =
    vtkSmartPointer<vtkImageActor>::New();
  openCloseActor->GetMapper()->SetInputConnection(
    openClose->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double openCloseViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> openCloseRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  openCloseRenderer->SetViewport(openCloseViewport);
  openCloseRenderer->AddActor(openCloseActor);
  openCloseRenderer->ResetCamera();
  openCloseRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(openCloseRenderer);

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
