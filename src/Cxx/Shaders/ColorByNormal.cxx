#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>
#include <vtkOpenGLPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTriangleMeshPointNormals.h>
#include <vtkVersion.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>
#include <vtksys/SystemTools.hxx>

#if VTK_VERSION_NUMBER >= 89000000000ULL
#define USE_SHADER_PROPERTIES 1
#include <vtkShaderProperty.h>
#endif

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(const char* fileName);
}

//----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  auto polyData = ReadPolyData(argc > 1 ? argv[1] : "");

  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto actor = vtkSmartPointer<vtkActor>::New();
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto mapper = vtkSmartPointer<vtkOpenGLPolyDataMapper>::New();
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);
  renderer->AddActor(actor);

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  auto norms = vtkSmartPointer<vtkTriangleMeshPointNormals>::New();
  norms->SetInputData(polyData);

  mapper->SetInputConnection(norms->GetOutputPort());
  actor->SetMapper(mapper);
  actor->GetProperty()->SetAmbientColor(0.2, 0.2, 1.0);
  actor->GetProperty()->SetDiffuseColor(1.0, 0.65, 0.7);
  actor->GetProperty()->SetSpecularColor(1.0, 1.0, 1.0);
  actor->GetProperty()->SetSpecular(0.5);
  actor->GetProperty()->SetDiffuse(0.7);
  actor->GetProperty()->SetAmbient(0.5);
  actor->GetProperty()->SetSpecularPower(20.0);
  actor->GetProperty()->SetOpacity(1.0);

  // Modify the shader to color based on model normal
  // To do this we have to modify the vertex shader
  // to pass the normal in model coordinates
  // through to the fragment shader. By default the normal
  // is converted to View coordinates and then passed on.
  // We keep that, but add a varying for the original normal.
  // Then we modify the fragment shader to set the diffuse color
  // based on that normal. First lets modify the vertex
  // shader
#if USE_SHADER_PROPERTIES
  vtkShaderProperty* sp = actor->GetShaderProperty();
  sp->AddVertexShaderReplacement(
      "//VTK::Normal::Dec",  // replace the normal block
      true,                  // before the standard replacements
      "//VTK::Normal::Dec\n" // we still want the default
      "  varying vec3 myNormalMCVSOutput;\n", // but we add this
      false                                   // only do it once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Vertex,
      "//VTK::Normal::Dec",  // replace the normal block
      true,                  // before the standard replacements
      "//VTK::Normal::Dec\n" // we still want the default
      "  varying vec3 myNormalMCVSOutput;\n", // but we add this
      false                                   // only do it once
  );
#endif
#if USE_SHADER_PROPERTIES
  sp->AddVertexShaderReplacement(
      "//VTK::Normal::Impl",                // replace the normal block
      true,                                 // before the standard replacements
      "//VTK::Normal::Impl\n"               // we still want the default
      "  myNormalMCVSOutput = normalMC;\n", // but we add this
      false                                 // only do it once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Vertex,
      "//VTK::Normal::Impl",                // replace the normal block
      true,                                 // before the standard replacements
      "//VTK::Normal::Impl\n"               // we still want the default
      "  myNormalMCVSOutput = normalMC;\n", // but we add this
      false                                 // only do it once
  );
#endif
#if USE_SHADER_PROPERTIES
  sp->AddVertexShaderReplacement(
      "//VTK::Color::Impl", // dummy replacement for testing clear method
      true, "VTK::Color::Impl\n", false);
#else
  mapper->AddShaderReplacement(
      vtkShader::Vertex,
      "//VTK::Color::Impl", // dummy replacement for testing clear method
      true, "VTK::Color::Impl\n", false);
#endif
#if USE_SHADER_PROPERTIES
  sp->ClearVertexShaderReplacement("//VTK::Color::Impl", true);
#else
  mapper->ClearShaderReplacement(
      vtkShader::Vertex, // clear our dummy replacement
      "//VTK::Color::Impl", true);
#endif

  // now modify the fragment shader
#if USE_SHADER_PROPERTIES
  sp->AddFragmentShaderReplacement(
      "//VTK::Normal::Dec",  // replace the normal block
      true,                  // before the standard replacements
      "//VTK::Normal::Dec\n" // we still want the default
      "  varying vec3 myNormalMCVSOutput;\n", // but we add this
      false                                   // only do it once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Fragment,   // in the fragment shader
      "//VTK::Normal::Dec",  // replace the normal block
      true,                  // before the standard replacements
      "//VTK::Normal::Dec\n" // we still want the default
      "  varying vec3 myNormalMCVSOutput;\n", // but we add this
      false                                   // only do it once
  );
#endif
#if USE_SHADER_PROPERTIES
  sp->AddFragmentShaderReplacement(
      "//VTK::Normal::Impl",  // replace the normal block
      true,                   // before the standard replacements
      "//VTK::Normal::Impl\n" // we still want the default calc
      "  diffuseColor = abs(myNormalMCVSOutput);\n", // but we add this
      false                                          // only do it once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Fragment,    // in the fragment shader
      "//VTK::Normal::Impl",  // replace the normal block
      true,                   // before the standard replacements
      "//VTK::Normal::Impl\n" // we still want the default calc
      "  diffuseColor = abs(myNormalMCVSOutput);\n", // but we add this
      false                                          // only do it once
  );
#endif

  renderWindow->Render();
  renderer->GetActiveCamera()->SetPosition(1.0, 1.0, -1.0);
  renderer->GetActiveCamera()->SetFocalPoint(0, 1, 0);
  renderer->GetActiveCamera()->SetViewUp(0, 1, 0);
  renderer->GetActiveCamera()->Elevation(30.0);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(1.3);
  renderWindow->Render();
  renderWindow->SetWindowName("ColorByNormal");
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(const char* fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension =
      vtksys::SystemTools::GetFilenameExtension(std::string(fileName));
  if (extension == ".ply")
  {
    auto reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    auto reader = vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    auto reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    auto reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    auto reader = vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    auto source = vtkSmartPointer<vtkSphereSource>::New();
    source->SetPhiResolution(25);
    source->SetThetaResolution(25);
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
} // namespace
