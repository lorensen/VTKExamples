#include <vtkImageActor.h>
#include <vtkImageCast.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageDilateErode3D.h>
#include <vtkImageThreshold.h>

int main(int argc, char *argv[])
{
  // Handle the arguments
  if( argc < 2 )
  {
    std::cout << "Required arguments: filename.png" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkPNGReader> reader =
    vtkSmartPointer<vtkPNGReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  vtkSmartPointer<vtkImageDilateErode3D> dilateErode =
    vtkSmartPointer<vtkImageDilateErode3D>::New();
  dilateErode->SetInputConnection(reader->GetOutputPort());
  dilateErode->SetDilateValue(0);
  dilateErode->SetErodeValue(255);
  dilateErode->SetKernelSize(5, 5, 3);
  dilateErode->ReleaseDataFlagOff();

  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> openCloseActor =
    vtkSmartPointer<vtkImageActor>::New();
  openCloseActor->GetMapper()->SetInputConnection(dilateErode->GetOutputPort());

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

  vtkSmartPointer<vtkRenderer> dilateErodeRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  dilateErodeRenderer->SetViewport(openCloseViewport);
  dilateErodeRenderer->AddActor(openCloseActor);
  dilateErodeRenderer->ResetCamera();
  dilateErodeRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(dilateErodeRenderer);

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
