#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkPlane.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>

#include <vtkCutter.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0]
              << " inputFilename(.vtp) [numberOfCuts]" << std::endl;
    std::cout << "where: inputFilename is Torso.vtp and";
    std::cout << " numberOfCuts is 10." << std::endl;
    return EXIT_FAILURE;
  }
  std::string inputFilename = argv[1];

  int numberOfCuts = 10;
  if (argc > 2)
  {
    numberOfCuts = atoi(argv[2]);
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  double bounds[6];
  reader->GetOutput()->GetBounds(bounds);
  std::cout << "Bounds: "
            << bounds[0] << ", " << bounds[1] << " "
            << bounds[2] << ", " << bounds[3] << " "
            << bounds[4] << ", " << bounds[5] << std::endl;

  vtkSmartPointer<vtkPlane> plane =
    vtkSmartPointer<vtkPlane>::New();
  plane->SetOrigin((bounds[1] + bounds[0]) / 2.0,
                   (bounds[3] + bounds[2]) / 2.0,
                   bounds[4]);
  plane->SetNormal(0,0,1);

  // Create cutter
  double high = plane->EvaluateFunction((bounds[1] + bounds[0]) / 2.0,
                                        (bounds[3] + bounds[2]) / 2.0,
                                        bounds[5]);

  vtkSmartPointer<vtkCutter> cutter =
    vtkSmartPointer<vtkCutter>::New();
  cutter->SetInputConnection(reader->GetOutputPort());
  cutter->SetCutFunction(plane);
  cutter->GenerateValues(
    numberOfCuts,
    .99,
    .99 * high);

  vtkSmartPointer<vtkPolyDataMapper> cutterMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cutterMapper->SetInputConnection( cutter->GetOutputPort());
  cutterMapper->ScalarVisibilityOff();

  // Create cut actor
  vtkSmartPointer<vtkActor> cutterActor =
    vtkSmartPointer<vtkActor>::New();
  cutterActor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
  cutterActor->GetProperty()->SetLineWidth(2);
  cutterActor->SetMapper(cutterMapper);

  // Create model actor
  vtkSmartPointer<vtkPolyDataMapper> modelMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  modelMapper->SetInputConnection( reader->GetOutputPort());
  modelMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> modelActor =
    vtkSmartPointer<vtkActor>::New();
  modelActor->GetProperty()->SetColor(colors->GetColor3d("Flesh").GetData());
  modelActor->SetMapper(modelMapper);

  // Create renderers and add actors of plane and model
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(cutterActor);
  renderer->AddActor(modelActor);

  // Add renderer to renderwindow and render
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(600, 600);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());
  renderer->GetActiveCamera()->SetPosition(0, -1, 0);
  renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  renderer->GetActiveCamera()->SetViewUp(0, 0, 1);
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);

  renderer->ResetCamera();
  renderWindow->Render();
  renderWindow->SetWindowName("CutWithCutFunction");


  interactor->Start();

  return EXIT_SUCCESS;
}
