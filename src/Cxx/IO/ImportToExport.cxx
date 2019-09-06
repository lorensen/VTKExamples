#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

// Importers
#include <vtk3DSImporter.h>
#include <vtkGLTFImporter.h>
#include <vtkOBJImporter.h>
#include <vtkVRMLImporter.h>

// Exporters
#include <vtkGLTFExporter.h>
#include <vtkIVExporter.h>
#include <vtkOBJExporter.h>
#include <vtkOOGLExporter.h>
#include <vtkRIBExporter.h>
#include <vtkSVGExporter.h>
#include <vtkVRMLExporter.h>
#include <vtkX3DExporter.h>

#include <algorithm> // For transform()
#include <string> // For find_last_of()
#include <cctype> // For to_lower
#include <sstream> // For stringstream
int main(int argc, char *argv[])
{
  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  auto renderer =
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
    importer->SetRenderWindow(renderWindow);
    renderWindow = importer->GetRenderWindow();
    renderer = importer->GetRenderer();
    importer->Read();
    filePrefixArgOffset = 2;
  }
  else if (extension == "3ds")
  {
    auto importer =
      vtkSmartPointer<vtk3DSImporter>::New();
    importer->SetFileName(argv[1]);
    importer->SetRenderWindow(renderWindow);
    importer->ComputeNormalsOn();
    renderWindow = importer->GetRenderWindow();
    renderer = importer->GetRenderer();
    importer->Read();
    filePrefixArgOffset = 2;
  }
  else if (extension == "gltf" || extension == "glb")
  {
    auto importer =
      vtkSmartPointer<vtkGLTFImporter>::New();
    importer->SetFileName(argv[1]);
    importer->SetRenderWindow(renderWindow);
    renderWindow = importer->GetRenderWindow();
    renderer = importer->GetRenderer();
    importer->Read();
    filePrefixArgOffset = 2;
  }
  else if (extension == "obj")
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
    filePrefixArgOffset = 4;
  }
  std::string outputExtension = argv[filePrefixArgOffset + 1];

  if (outputExtension == "obj")
  {
    auto exporter =
      vtkSmartPointer<vtkOBJExporter>::New();
    std::stringstream comment;
    comment << "Converted by ImportExport from " << fileName;
    exporter->SetOBJFileComment(comment.str().c_str());
    exporter->SetMTLFileComment(comment.str().c_str());
    exporter->SetActiveRenderer(renderer);
    exporter->SetRenderWindow(renderWindow);
    exporter->SetFilePrefix(argv[filePrefixArgOffset]);
    exporter->Write();
  }
  else if (outputExtension == "wrl")
  {
    std::string exportFileName;
    exportFileName = std::string(argv[filePrefixArgOffset]) + "." + "wrl";
    auto exporter =
      vtkSmartPointer<vtkVRMLExporter>::New();
    exporter->SetFileName(exportFileName.c_str());
    exporter->SetActiveRenderer(renderer);
    exporter->SetRenderWindow(renderWindow);
    std::cout << "Writing " << exportFileName << std::endl;
    exporter->Write();
  }
  else if (outputExtension == "gltf" || outputExtension == "glb")
  {
    std::string exportFileName;
    exportFileName = std::string(argv[filePrefixArgOffset]) + "." + "gltf";
    auto exporter =
      vtkSmartPointer<vtkGLTFExporter>::New();
    exporter->SetFileName(exportFileName.c_str());
    exporter->SetActiveRenderer(renderer);
    exporter->SetRenderWindow(renderWindow);
    std::cout << "Writing " << exportFileName << std::endl;
    exporter->Write();
  }
  else if (outputExtension == "x3d")
  {
    std::string exportFileName;
    exportFileName = std::string(argv[filePrefixArgOffset]) + "." + "x3d";
    auto exporter =
      vtkSmartPointer<vtkX3DExporter>::New();
    exporter->SetFileName(exportFileName.c_str());
    exporter->SetActiveRenderer(renderer);
    exporter->SetRenderWindow(renderWindow);
    std::cout << "Writing " << exportFileName << std::endl;
    exporter->Write();
  }
  return EXIT_SUCCESS;
}
