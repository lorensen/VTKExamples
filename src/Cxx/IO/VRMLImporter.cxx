#include <vtkNamedColors.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkVRMLImporter.h>

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Required arguments: Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];
  std::cout << "Reading " << filename << std::endl;

  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // VRML Import
  auto importer = vtkSmartPointer<vtkVRMLImporter>::New();
  importer->SetFileName(filename.c_str());
  importer->SetRenderWindow(renderWindow);
  importer->Update();

  auto actors = renderer->GetActors();
  std::cout << "There are " << actors->GetNumberOfItems() << " actors"
            << std::endl;

  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());
  renderWindow->SetSize(512, 512);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
