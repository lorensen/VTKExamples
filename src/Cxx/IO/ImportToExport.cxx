#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

#include <vtkOBJImporter.h>
#include <vtkVRMLImporter.h>
#include <vtk3DSImporter.h>

#include <vtkOBJExporter.h>

#include <algorithm> // For transform()
#include <string> // For find_last_of()
#include <cctype> // For to_lower

int main(int argc, char *argv[])
{
  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  std::string fileName = argv[1];
  std::string extension = "";
  // Make the extension lowercase
  std::transform(extension.begin(), extension.end(), extension.begin(),
                 ::tolower);
  if (fileName.find_last_of(".") != std::string::npos)
  {
    extension = fileName.substr(fileName.find_last_of("."));
  }
  if (extension == ".wrl")
  {
    auto importer =
      vtkSmartPointer<vtkVRMLImporter>::New();
    importer->SetFileName(argv[1]);
    importer->SetRenderWindow(renderWindow);
    renderWindow = importer->GetRenderWindow();
    renderer = importer->GetRenderer();
    importer->Read();
  }
  else if (extension == ".3ds")
  {
    auto importer =
      vtkSmartPointer<vtk3DSImporter>::New();
    importer->SetFileName(argv[1]);
    importer->SetRenderWindow(renderWindow);
    renderWindow = importer->GetRenderWindow();
    renderer = importer->GetRenderer();
    importer->Read();
  }
  else if (extension == ".obj")
  {
    auto importer =
      vtkSmartPointer<vtkOBJImporter>::New();
    importer->SetFileName(argv[1]);
    importer->SetFileNameMTL(argv[2]);
    importer->SetTexturePath(argv[3]);
    importer->SetRenderWindow(renderWindow);
    renderWindow = importer->GetRenderWindow();
    renderer = importer->GetRenderer();
    importer->Read();
  }
  auto exporter =
    vtkSmartPointer<vtkOBJExporter>::New();
  exporter->SetFilePrefix(argv[2]);
  exporter->SetActiveRenderer(renderer);
  exporter->SetRenderWindow(renderWindow);
  exporter->Write();
  return EXIT_SUCCESS;
}
