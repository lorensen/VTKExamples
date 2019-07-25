#include <vtkCleanPolyData.h>
#include <vtkNamedColors.h>
#include <vtkOBJImporter.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTexture.h>

int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cout << "Usage: " << argv[0] << " objfile mtlfile texturepath"
              << std::endl;
    return EXIT_FAILURE;
  }
  auto importer = vtkSmartPointer<vtkOBJImporter>::New();
  importer->SetFileName(argv[1]);
  importer->SetFileNameMTL(argv[2]);
  importer->SetTexturePath(argv[3]);

  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renWin = vtkSmartPointer<vtkRenderWindow>::New();
  auto iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  renderer->SetBackground2(colors->GetColor3d("Silver").GetData());
  renderer->SetBackground(colors->GetColor3d("Gold").GetData());
  renderer->GradientBackgroundOn();
  renWin->AddRenderer(renderer);
  renderer->UseHiddenLineRemovalOn();
  renWin->AddRenderer(renderer);
  renWin->SetSize(640, 480);

  iren->SetRenderWindow(renWin);
  importer->SetRenderWindow(renWin);
  importer->Update();

  auto actors = renderer->GetActors();
  actors->InitTraversal();
  std::cout << "There are " << actors->GetNumberOfItems() << " actors"
            << std::endl;

  for (vtkIdType a = 0; a < actors->GetNumberOfItems(); ++a)
  {
    std::cout << importer->GetOutputDescription(a) << std::endl;

    vtkActor* actor = actors->GetNextActor();

    // OBJImporter turns texture interpolation off
    if (actor->GetTexture())
    {
      std::cout << "Has texture\n";
      actor->GetTexture()->InterpolateOn();
    }

    vtkPolyData* pd =
        dynamic_cast<vtkPolyData*>(actor->GetMapper()->GetInput());
    auto clean = vtkSmartPointer<vtkCleanPolyData>::New();
    clean->SetInputData(pd);
    clean->Update();

    auto normals = vtkSmartPointer<vtkPolyDataNormals>::New();
    normals->SetInputData(pd);
    normals->SplittingOff();
    normals->ConsistencyOn();
    normals->Update();
    vtkPolyDataMapper* mapper =
        dynamic_cast<vtkPolyDataMapper*>(actor->GetMapper());
    mapper->SetInputData(normals->GetOutput());
    mapper->SetInputData(pd);
  }
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
