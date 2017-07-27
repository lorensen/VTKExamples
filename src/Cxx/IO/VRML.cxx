#include <vtkSmartPointer.h>
#include <vtkVRMLImporter.h>

#include <vtkActorCollection.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkNamedColors.h>

int main ( int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cout << "Required arguments: Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];
  std::cout << "Reading " << filename << std::endl;

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // VRML Import
  vtkSmartPointer<vtkVRMLImporter> importer =
    vtkSmartPointer<vtkVRMLImporter>::New();
  importer->SetFileName ( filename.c_str() );
  importer->SetRenderWindow(renderWindow);
  importer->Update();

  vtkSmartPointer<vtkActorCollection> actors =
    vtkSmartPointer<vtkActorCollection>::New();
  actors = renderer->GetActors();
  std::cout << "There are " << actors->GetNumberOfItems() << " actors" << std::endl;

  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());
  renderWindow->SetSize(512, 512);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
