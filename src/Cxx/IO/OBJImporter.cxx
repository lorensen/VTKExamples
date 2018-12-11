#include <vtkSmartPointer.h>

#include <vtkOBJImporter.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyData.h>
#include <vtkTexture.h>
#include <vtkNamedColors.h>

int main (int argc, char *argv[])
{
  if (argc < 4)
  {
    std::cout << "Usage: " << argv[0]
              << " objfile mtlfile texturepath"
              << std::endl;
    return EXIT_FAILURE;
  }
  vtkSmartPointer<vtkOBJImporter> importer =
    vtkSmartPointer<vtkOBJImporter>::New();
  importer->SetFileName(argv[1]);
  importer->SetFileNameMTL(argv[2]);
  importer->SetTexturePath(argv[3]);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  renWin->AddRenderer(renderer);
  renderer->SetBackground2 (colors->GetColor3d("Silver").GetData());
  renderer->SetBackground (colors->GetColor3d("Gold").GetData());
  renderer->GradientBackgroundOn();

  iren->SetRenderWindow(renWin);
  importer->SetRenderWindow(renWin);
  importer->Update();

  vtkSmartPointer<vtkActorCollection> actors =
    vtkSmartPointer<vtkActorCollection>::New();
  actors = renderer->GetActors();
  actors->InitTraversal();
  std::cout << "There are " << actors->GetNumberOfItems() << " actors" << std::endl;

  for (vtkIdType a = 0; a < actors->GetNumberOfItems(); ++a)
  {
    std::cout << importer->GetOutputDescription(a) << std::endl;

    vtkActor * actor = actors->GetNextActor();

    // OBJImporter turns texture interpolation off
    if (actor->GetTexture())
    {
      std::cout << "Hastexture\n";
      actor->GetTexture()->InterpolateOn();
    }

    vtkPolyData *pd = vtkPolyData::SafeDownCast(actor->GetMapper()->GetInput());
    vtkSmartPointer<vtkCleanPolyData> clean =
      vtkSmartPointer<vtkCleanPolyData>::New();
    clean->SetInputData(pd);
    clean->Update();

    vtkSmartPointer<vtkPolyDataNormals> normals =
      vtkSmartPointer<vtkPolyDataNormals>::New();
    normals->SetInputData(pd);
    normals->SplittingOff();
    normals->ConsistencyOn();
    normals->Update();
    vtkPolyDataMapper *mapper = vtkPolyDataMapper::SafeDownCast(actor->GetMapper());
    mapper->SetInputData(normals->GetOutput());
    mapper->SetInputData(pd);
  }
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
