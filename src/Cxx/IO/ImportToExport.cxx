#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

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
#include <cctype>    // For to_lower
#include <iterator>  // For prev
#include <set>       // For valid extensions
#include <sstream>   // For stringstream
#include <string>    // For find_last_of()

int main(int argc, char* argv[])
{
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  auto renderer = vtkSmartPointer<vtkRenderer>::New();

  if (argc < 3)
  {
    std::cerr << "Expects input file name(s) and an output filename."
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string fileName = argv[1];
  std::string extension = "";
  int outputFileArgOffset = 0; // depends on importer

  std::set<std::string> inputExtensions{{
      "3ds",
      "glb",
      "gltf",
      "obj",
      "wrl",
  }};
  std::set<std::string> outputExtensions{{
      "glb",
      "gltf",
      "obj",
      "wrl",
      "x3d",
  }};

  // Make the extension lowercase
  std::transform(extension.begin(), extension.end(), extension.begin(),
                 ::tolower);
  if (fileName.find_last_of(".") != std::string::npos)
  {
    extension = fileName.substr(fileName.find_last_of(".") + 1);
  }
  if (inputExtensions.find(extension) == inputExtensions.end())
  {
    std::cout << "Invalid input extension.\nValid extensions are: "
              << std::endl;
    for (auto it = inputExtensions.begin(); it != inputExtensions.end(); ++it)
    {
      if (it != std::prev(inputExtensions.end()))
      {
        std::cout << *it << ", ";
      }
      else
      {
        std::cout << *it << std::endl;
      }
    }
    return EXIT_FAILURE;
  }

  if (extension == "wrl")
  {
    auto importer = vtkSmartPointer<vtkVRMLImporter>::New();
    importer->SetFileName(argv[1]);
    importer->SetRenderWindow(renderWindow);
    renderWindow = importer->GetRenderWindow();
    renderer = importer->GetRenderer();
    importer->Read();
    outputFileArgOffset = 2;
  }
  else if (extension == "3ds")
  {
    auto importer = vtkSmartPointer<vtk3DSImporter>::New();
    importer->SetFileName(argv[1]);
    importer->SetRenderWindow(renderWindow);
    importer->ComputeNormalsOn();
    renderWindow = importer->GetRenderWindow();
    renderer = importer->GetRenderer();
    importer->Read();
    outputFileArgOffset = 2;
  }
  else if (extension == "gltf" || extension == "glb")
  {
    auto importer = vtkSmartPointer<vtkGLTFImporter>::New();
    importer->SetFileName(argv[1]);
    importer->SetRenderWindow(renderWindow);
    renderWindow = importer->GetRenderWindow();
    renderer = importer->GetRenderer();
    importer->Read();
    outputFileArgOffset = 2;
  }
  else if (extension == "obj")
  {
    auto importer = vtkSmartPointer<vtkOBJImporter>::New();
    importer->SetFileName(argv[1]);
    importer->SetFileNameMTL(argv[2]);
    importer->SetTexturePath(argv[3]);
    importer->SetRenderWindow(renderWindow);
    renderWindow = importer->GetRenderWindow();
    renderer = importer->GetRenderer();
    importer->Read();
    outputFileArgOffset = 4;
  }

  std::string outputFileName = argv[outputFileArgOffset];
  std::string outputExtension{""};
  // Split the file path and extension
  if (outputFileName.find_last_of(".") != std::string::npos)
  {
    outputExtension =
        outputFileName.substr(outputFileName.find_last_of(".") + 1);
    auto pos = outputFileName.rfind(".", outputFileName.length());
    if (pos != std::string::npos)
    {
      outputFileName = outputFileName.substr(0, pos);
    }
  }
  std::transform(outputExtension.begin(), outputExtension.end(),
                 outputExtension.begin(), ::tolower);

  if (outputExtensions.find(outputExtension) == outputExtensions.end())
  {
    std::cout << "Invalid output extension.\nValid extensions are: "
              << std::endl;
    for (auto it = outputExtensions.begin(); it != outputExtensions.end(); ++it)
    {
      if (it != std::prev(outputExtensions.end()))
      {
        std::cout << *it << ", ";
      }
      else
      {
        std::cout << *it << std::endl;
      }
    }
    return EXIT_FAILURE;
  }

  if (outputExtension == "obj")
  {
    std::string exportFileName;
    exportFileName = outputFileName + "." + outputExtension;
    auto exporter = vtkSmartPointer<vtkOBJExporter>::New();
    std::stringstream comment;
    comment << "Converted by ImportExport from " << fileName;
    exporter->SetOBJFileComment(comment.str().c_str());
    exporter->SetMTLFileComment(comment.str().c_str());
    exporter->SetActiveRenderer(renderer);
    exporter->SetRenderWindow(renderWindow);
    exporter->SetFilePrefix(outputFileName.c_str());
    std::cout << "Writing " << exportFileName << std::endl;
    exporter->Write();
  }
  else if (outputExtension == "wrl")
  {
    std::string exportFileName;
    exportFileName = outputFileName + "." + outputExtension;
    auto exporter = vtkSmartPointer<vtkVRMLExporter>::New();
    exporter->SetFileName(exportFileName.c_str());
    exporter->SetActiveRenderer(renderer);
    exporter->SetRenderWindow(renderWindow);
    std::cout << "Writing " << exportFileName << std::endl;
    exporter->Write();
  }
  else if (outputExtension == "gltf" || outputExtension == "glb")
  {
    std::string exportFileName;
    exportFileName = outputFileName + "." + "gltf";
    auto exporter = vtkSmartPointer<vtkGLTFExporter>::New();
    exporter->SetFileName(exportFileName.c_str());
    exporter->SetActiveRenderer(renderer);
    exporter->SetRenderWindow(renderWindow);
    std::cout << "Writing " << exportFileName << std::endl;
    exporter->Write();
  }
  else if (outputExtension == "x3d")
  {
    std::string exportFileName;
    exportFileName = outputFileName + "." + outputExtension;
    auto exporter = vtkSmartPointer<vtkX3DExporter>::New();
    exporter->SetFileName(exportFileName.c_str());
    exporter->SetActiveRenderer(renderer);
    exporter->SetRenderWindow(renderWindow);
    std::cout << "Writing " << exportFileName << std::endl;
    exporter->Write();
  }
  return EXIT_SUCCESS;
}
