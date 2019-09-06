#include <vtkSmartPointer.h>

// Importers
#include <vtk3DSImporter.h>
#include <vtkGLTFImporter.h>
#include <vtkOBJImporter.h>
#include <vtkVRMLImporter.h>

// Rendering
#include <vtkNamedColors.h>
#include <vtkActorCollection.h>

#include <vtkDataSet.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>

#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

// Pipeline
#include <vtkAppendPolyData.h>
#include <vtkTransform.h>
#include <vtkMatrix4x4.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkCellData.h>
#include <vtkUnsignedCharArray.h>

#include <algorithm> // For transform()
#include <string> // For find_last_of()
#include <cctype> // For to_lower

int main (int argc, char *argv[])
{
  auto importRenderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  auto importRenderer =
    vtkSmartPointer<vtkRenderer>::New();

  std::string fileName = argv[1];
  std::string extension = "";
  int filePrefixArgOffset = 0; // depends on importer

  // Make the extension lowercase
  std::transform(extension.begin(), extension.end(), extension.begin(),
                 ::tolower);
  if (fileName.find_last_of(".") != std::string::npos)
  {
    extension = fileName.substr(fileName.find_last_of(".") + 1);
  }
  if (extension == "wrl")
  {
    auto importer =
      vtkSmartPointer<vtkVRMLImporter>::New();
    importer->SetFileName(argv[1]);
    importer->SetRenderWindow(importRenderWindow);
    importRenderWindow = importer->GetRenderWindow();
    importer->Read();
    importRenderer = importer->GetRenderer();
    filePrefixArgOffset = 2;
  }
  else if (extension == "3ds")
  {
    auto importer =
      vtkSmartPointer<vtk3DSImporter>::New();
    importer->SetFileName(argv[1]);
    importer->SetRenderWindow(importRenderWindow);
    importRenderWindow = importer->GetRenderWindow();
    importer->Read();
    importRenderer = importer->GetRenderer();
    filePrefixArgOffset = 2;
   }
  else if (extension == "gltf" || extension == "glb")
  {
    auto importer =
      vtkSmartPointer<vtkGLTFImporter>::New();
    importer->SetFileName(argv[1]);
    importer->SetRenderWindow(importRenderWindow);
    importRenderWindow = importer->GetRenderWindow();
    importer->Read();
    importRenderer = importer->GetRenderer();
    filePrefixArgOffset = 2;
   }
  else if (extension == "obj")
  {
    auto importer =
      vtkSmartPointer<vtkOBJImporter>::New();
    importer->SetFileName(argv[1]);
    importer->SetFileNameMTL(argv[2]);
    importer->SetTexturePath(argv[3]);
    importer->SetRenderWindow(importRenderWindow);
    importRenderWindow = importer->GetRenderWindow();
    importer->Read();
    importRenderer = importer->GetRenderer();
    filePrefixArgOffset = 4;
   }
  auto append =
    vtkSmartPointer<vtkAppendPolyData>::New();
  vtkActorCollection *allActors = importRenderer->GetActors();
  vtkCollectionSimpleIterator actorsIt;
  vtkActor *anActor = nullptr;;
  allActors->InitTraversal(actorsIt);
  while((anActor = allActors->GetNextActor(actorsIt)))
  {
    auto appendPD =
      vtkSmartPointer<vtkPolyData>::New();
    vtkPolyData *pd;
    anActor->GetMapper()->Update();
    if (anActor->GetUserMatrix() != nullptr)
    {
      auto transform =
        vtkSmartPointer<vtkTransform>::New();
      transform->SetMatrix(anActor->GetUserMatrix());
      auto transformPD =
        vtkSmartPointer<vtkTransformPolyDataFilter>::New();
      transformPD->SetTransform(transform);
      transformPD->SetInputData(dynamic_cast<vtkPolyData *>(anActor->GetMapper()->GetInput()));
      transformPD->Update();
      appendPD->DeepCopy(transformPD->GetOutput());
    }
    else
    {
      pd = dynamic_cast<vtkPolyData *>(anActor->GetMapper()->GetInput());
      appendPD->DeepCopy(pd);
    }
    auto cellData =
      vtkSmartPointer<vtkUnsignedCharArray>::New();
    cellData->SetNumberOfComponents(3);
    cellData->SetNumberOfTuples(appendPD->GetNumberOfCells());
    for (int i = 0; i < appendPD->GetNumberOfCells(); i++)
    {
      double rgb[4];
      anActor->GetProperty()->GetDiffuseColor(rgb);
      for (int j = 0; j < 4; ++j)
      {
        rgb[j] *= 255.0;
      }
      cellData->InsertTuple(i, rgb);
    }
    appendPD->GetCellData()->SetScalars(cellData);

    append->AddInputData(appendPD);
  }
  append->Update();

  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();

  auto mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(append->GetOutput());
  mapper->SetScalarModeToUseCellData();

  auto actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Banana").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->UseHiddenLineRemovalOn();
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
//  renderer->SetActiveCamera(importRenderer->GetActiveCamera());
  renderWindow->AddRenderer(renderer);
  renderer->AddActor(actor);
//  renderer->ResetCamera();
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
