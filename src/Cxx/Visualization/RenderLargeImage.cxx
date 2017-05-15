#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkImageViewer.h>
#include <vtkPNGWriter.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderLargeImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkXMLPolyDataReader.h>

int main (int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage: " << argv[0]
              << " Input(.vtp) Output(.png) [Magnification]"
              << std::endl;
    return EXIT_FAILURE;
  }
  int magnification = 4;
  if (argc == 4)
  {
    magnification = atoi(argv[3]);
  }

  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<  vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderWindow->AddRenderer(renderer);

  renderer->AddActor(actor);

  // Let the renderer compute good position and focal point
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Dolly(1.4);
  renderer->ResetCameraClippingRange();
  renderer->SetBackground(.3, .4, .5);

  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  std::cout << "Interact with image to get desired view and then press 'e'"
            << std::endl;
  interactor->Start();
  std::cout << "Generating large image size: "
            << renderWindow->GetSize()[0] * magnification << " by "
            << renderWindow->GetSize()[1] * magnification
            << std::endl;


  vtkSmartPointer<vtkRenderLargeImage> renderLarge =
    vtkSmartPointer<vtkRenderLargeImage>::New();
  renderLarge->SetInput(renderer);
  renderLarge->SetMagnification(magnification);

  std::cout << "Saving image in " << argv[2] << std::endl;
  vtkSmartPointer<vtkPNGWriter> writer =
    vtkSmartPointer<vtkPNGWriter>::New();
  writer->SetFileName(argv[2]);
  writer->SetInputConnection(renderLarge->GetOutputPort());
  writer->Write();

  return EXIT_SUCCESS;
}
