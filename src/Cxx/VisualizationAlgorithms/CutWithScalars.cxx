#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkDoubleArray.h>
#include <vtkNamedColors.h>
#include <vtkPlane.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0]
              << " inputFilename(.vtp) [numberOfCuts]" << std::endl;
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
                   (bounds[5] + bounds[4]) / 2.0);
  plane->SetNormal(0,0,1);

  // Create Scalars
  vtkSmartPointer<vtkDoubleArray> scalars =
    vtkSmartPointer<vtkDoubleArray>::New();
  int numberOfPoints = reader->GetOutput()->GetNumberOfPoints();
  scalars->SetNumberOfTuples(numberOfPoints);
  vtkPoints *pts = reader->GetOutput()->GetPoints();
  for (int i = 0; i < numberOfPoints; ++i)
  {
    double point[3];
    pts->GetPoint(i, point);
    scalars->SetTuple1(i, plane->EvaluateFunction(point));
  }
  reader->GetOutput()->GetPointData()->SetScalars(scalars);
  reader->GetOutput()->GetPointData()->GetScalars()->GetRange();

  // Create cutter
  vtkSmartPointer<vtkContourFilter> cutter =
    vtkSmartPointer<vtkContourFilter>::New();
  cutter->SetInputConnection(reader->GetOutputPort());
  cutter->ComputeScalarsOff();
  cutter->ComputeNormalsOff();
  cutter->GenerateValues(
    numberOfCuts,
    .99 * reader->GetOutput()->GetPointData()->GetScalars()->GetRange()[0],
    .99 * reader->GetOutput()->GetPointData()->GetScalars()->GetRange()[1]);

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

  interactor->Start();

  return EXIT_SUCCESS;
}
