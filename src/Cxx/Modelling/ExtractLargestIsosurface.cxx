#include <vtkSmartPointer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkNamedColors.h>
int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage: " << argv[0]
              << " InputFile(.vtk) Threshold" << std::endl;
    return EXIT_FAILURE;
  }
  const char* fileName = argv[1];
  float threshold = atof(argv[2]);
  int extractLargest = 1;
  if (argc == 4)
  {
    extractLargest = atoi(argv[3]);
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Load data
  vtkSmartPointer<vtkStructuredPointsReader> reader =
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(fileName);

  // Create a 3D model using marching cubes
  vtkSmartPointer<vtkMarchingCubes> mc =
    vtkSmartPointer<vtkMarchingCubes>::New();
  mc->SetInputConnection(reader->GetOutputPort());
  mc->ComputeNormalsOn();
  mc->ComputeGradientsOn();
  mc->SetValue(0, threshold);  // second value acts as threshold

  // To remain largest region
  vtkSmartPointer<vtkPolyDataConnectivityFilter> confilter =
    vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
  confilter->SetInputConnection(mc->GetOutputPort());
  confilter->SetExtractionModeToLargestRegion();

  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  if (extractLargest)
  {
    mapper->SetInputConnection(confilter->GetOutputPort());
  }
  else
  {
    mapper->SetInputConnection(mc->GetOutputPort());
  }

  mapper->ScalarVisibilityOff();    // utilize actor's property I set

  // Visualize
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->GetProperty()->SetColor(colors->GetColor3d("Flesh").GetData());
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());
  renderer->GetActiveCamera()->SetViewUp(0.0, 0.0, 1.0);
  renderer->GetActiveCamera()->SetPosition(0.0, 1.0, 0.0);
  renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30.0);
  renderer->GetActiveCamera()->Elevation(30.0);
  vtkSmartPointer<vtkRenderWindow> renwin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renwin->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renwin);
  renwin->Render();
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
