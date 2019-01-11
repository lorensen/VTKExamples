#include <vtkNew.h>
#include <vtkNamedColors.h>
#include <vtkExodusIIReader.h>
#include <vtkCompositeDataGeometryFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCompositeDataGeometryFilter.h>

int main (int argc, char *argv[])
{
  vtkNew<vtkNamedColors>  colors;

  if (argc < 3)
  {
    std::cout << "Ysage: " << argv[0] << " exodus_file.e nodal_variable";
    return EXIT_FAILURE;
  }

  // Read Exodus Data
  vtkNew<vtkExodusIIReader> reader;
  reader->SetFileName(argv[1]);
  reader->UpdateInformation();
  reader->SetTimeStep(10);
  reader->SetAllArrayStatus(vtkExodusIIReader::NODAL, 1);  // enables all NODAL variables

  // Create Geometry
  vtkNew<vtkCompositeDataGeometryFilter> geometry;
  geometry->SetInputConnection(0, reader->GetOutputPort(0));

  // Mapper
  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(geometry->GetOutputPort());
  mapper->SelectColorArray(argv[2]);
  mapper->SetScalarModeToUsePointFieldData();
  mapper->InterpolateScalarsBeforeMappingOn();

  // Actor
  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);

  // Renderer
  vtkNew<vtkRenderer> renderer;
  renderer->AddViewProp(actor);
  renderer->SetBackground(colors->GetColor3d("DimGray").GetData());

  renderer->GetActiveCamera()->SetPosition(9.0, 9.0, 7.0);
  renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  renderer->GetActiveCamera()->SetViewUp(0.2, -0.7, 0.7);
  renderer->GetActiveCamera()->SetDistance(14.5);

  // Window and Interactor
  vtkNew<vtkRenderWindow>  window;
  window->AddRenderer(renderer);
  window->SetSize(600, 600);

  vtkNew<vtkRenderWindowInteractor> interactor;
  interactor->SetRenderWindow(window);
  interactor->Initialize();

  // Show the result
  window->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
