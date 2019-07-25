#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProgrammableSource.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkReverseSense.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkSurfaceReconstructionFilter.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char* argv[])
{

  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyData> input;
  if (argc > 1)
  {
    auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    input = reader->GetOutput();
  }
  else
  {
    auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->Update();
    input = sphereSource->GetOutput();
  }

  auto polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(input->GetPoints());

  // Construct the surface and create isosurface.
  auto surf = vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();
  surf->SetInputData(polydata);

  auto cf = vtkSmartPointer<vtkContourFilter>::New();
  cf->SetInputConnection(surf->GetOutputPort());
  cf->SetValue(0, 0.0);

  // Sometimes the contouring algorithm can create a volume whose gradient
  // vector and ordering of polygon (using the right hand rule) are
  // inconsistent. vtkReverseSense cures this problem.
  auto reverse = vtkSmartPointer<vtkReverseSense>::New();
  reverse->SetInputConnection(cf->GetOutputPort());
  reverse->ReverseCellsOn();
  reverse->ReverseNormalsOn();

  auto map = vtkSmartPointer<vtkPolyDataMapper>::New();
  map->SetInputConnection(reverse->GetOutputPort());
  map->ScalarVisibilityOff();

  auto surfaceActor = vtkSmartPointer<vtkActor>::New();
  surfaceActor->SetMapper(map);
  surfaceActor->GetProperty()->SetDiffuseColor(
      colors->GetColor3d("Tomato").GetData());
  surfaceActor->GetProperty()->SetSpecularColor(
      colors->GetColor3d("Seashell").GetData());
  surfaceActor->GetProperty()->SetSpecular(.4);
  surfaceActor->GetProperty()->SetSpecularPower(50);

  // Create the RenderWindow, Renderer and both Actors
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Add the actors to the renderer, set the background and size
  renderer->AddActor(surfaceActor);
  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
