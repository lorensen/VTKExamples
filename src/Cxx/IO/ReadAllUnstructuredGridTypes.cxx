#include <vtkSmartPointer.h>

#include <vtkUnstructuredGridReader.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSphereSource.h>
#include <vtkAppendFilter.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtkNamedColors.h>

#include <string>
#include <algorithm>
#include <array>

namespace
{
vtkSmartPointer<vtkUnstructuredGrid> ReadUnstructuredGrid(std::string const& fileName);
}

int main (int argc, char *argv[])
{
  // Vis Pipeline
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto renderer = vtkSmartPointer<vtkRenderer>::New();

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->SetBackground(colors->GetColor3d("Wheat").GetData());
  renderer->UseHiddenLineRemovalOn();

  std::cout << "Loading: " << argv[1] << std::endl;
  auto unstructuredGrid = ReadUnstructuredGrid(std::string(argv[1]));

  // Visualize
  auto mapper = vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputData(unstructuredGrid);
  mapper->ScalarVisibilityOff();

  auto backProp = vtkSmartPointer<vtkProperty>::New();
  backProp->SetDiffuseColor(colors->GetColor3d("Banana").GetData());
  backProp->SetSpecular(.6);
  backProp->SetSpecularPower(30);

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->SetBackfaceProperty(backProp);
  actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Tomato").GetData());
  actor->GetProperty()->SetSpecular(.3);
  actor->GetProperty()->SetSpecularPower(30);
  actor->GetProperty()->EdgeVisibilityOn();
  renderer->AddActor(actor);
  renderer->GetActiveCamera()->Azimuth(45);
  renderer->GetActiveCamera()->Elevation(45);
  renderer->ResetCamera();
  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}

namespace
{
vtkSmartPointer<vtkUnstructuredGrid> ReadUnstructuredGrid(std::string const& fileName)
{
  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid;
  std::string extension = "";
  if (fileName.find_last_of(".") != std::string::npos)
  {
    extension = fileName.substr(fileName.find_last_of("."));
  }

  // Drop the case of the extension
  std::transform(extension.begin(), extension.end(),
                 extension.begin(), ::tolower);

  if (extension == ".vtu")
  {
    auto reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
    reader->SetFileName (fileName.c_str());
    reader->Update();
    unstructuredGrid = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    auto reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
    reader->SetFileName (fileName.c_str());
    reader->Update();
    unstructuredGrid = reader->GetOutput();
  }
  else
  {
    auto source = vtkSmartPointer<vtkSphereSource>::New();
    source->Update();
    auto appendFilter =
      vtkSmartPointer<vtkAppendFilter>::New();
    appendFilter->AddInputData(source->GetOutput());
    appendFilter->Update();
    unstructuredGrid = appendFilter->GetOutput();
  }
  return unstructuredGrid;
}
}
