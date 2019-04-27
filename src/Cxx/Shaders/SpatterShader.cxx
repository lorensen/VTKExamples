#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCleanPolyData.h>
#include <vtkNamedColors.h>
#include <vtkOpenGLPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkShaderProgram.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTriangleFilter.h>
#include <vtkVersion.h>
#include <vtksys/SystemTools.hxx>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>

#if VTK_VERSION_NUMBER >= 89000000000ULL
#define USE_SHADER_PROPERTIES 1
#include <vtkShaderProperty.h>
#endif

#include <fstream>
#include <sstream>

namespace {
// -----------------------------------------------------------------------
// Update uniform variables in the shader for each render. We do this with a
// callback for the UpdateShaderEvent
class ShaderCallback : public vtkCommand
{
public:
  static ShaderCallback* New()
  {
    return new ShaderCallback;
  }
  vtkRenderer* Renderer;
  float specksize;
  int sizes;
  float basecolor[3];
  float spattercolor[3];

  void Execute(vtkObject*, unsigned long, void* calldata) override
  {
    vtkShaderProgram* program = reinterpret_cast<vtkShaderProgram*>(calldata);
    if (program)
    {
      program->SetUniformf("specksize", specksize);
      program->SetUniformi("sizes", sizes);
      program->SetUniform3f("basecolor", basecolor);
      program->SetUniform3f("spattercolor", spattercolor);
    }
  }

  void Print(std::ostream& os)
  {
    os << "specksize: " << specksize << std::endl;
    os << "sizes: " << sizes << std::endl;
    os << "basecolor: " << basecolor[0] << ", " << basecolor[1] << ", "
       << basecolor[2] << std::endl;
    os << "spattercolor: " << spattercolor[0] << ", " << spattercolor[1] << ", "
       << spattercolor[2] << std::endl;
  }

  ShaderCallback()
  {
    this->Renderer = nullptr;
    // size of the smallest paint specks
    this->specksize = .05;
    // number of different sizes of paint specks (each doubles the previous
    // size)
    this->sizes = 3;
    // the background color on which to spatter paint
    this->basecolor[0] = this->basecolor[1] = this->basecolor[2] = .7;
    //  the color of the paint spatters
    this->spattercolor[0] = this->spattercolor[1] = this->spattercolor[2] = 0.0;
  }
};
} // namespace
namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(const char* fileName);
}

//----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " PerlnNoise.glsl "
              << "[polydataFile] "
              << "[specksize(.05)] "
              << "[sizes(3)] "
              << "[basecolor{.7,.7,.7)] "
              << "[spattercolor(0.0,0.0,0.0)] " << std::endl;
    return EXIT_FAILURE;
  }

  auto polyData = ReadPolyData(argc > 2 ? argv[2] : "");

  std::ifstream shaderFile(argv[1]);
  std::ostringstream shaderCode;
  shaderCode << shaderFile.rdbuf();

  // Create a transform to rescale model
  double center[3];
  polyData->GetCenter(center);
  double bounds[6];
  polyData->GetBounds(bounds);
  double maxBound =
      std::max(std::max(bounds[1] - bounds[0], bounds[3] - bounds[2]),
               bounds[5] - bounds[4]);

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

  // Clean
  auto clean = vtkSmartPointer<vtkCleanPolyData>::New();
  clean->SetInputData(polyData);

  // Rescale polydata to [-1,1]
  auto userTransform = vtkSmartPointer<vtkTransform>::New();
  userTransform->Translate(-center[0], -center[1], -center[2]);
  userTransform->Scale(1.0 / maxBound, 1.0 / maxBound, 1.0 / maxBound);
  auto transform = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transform->SetTransform(userTransform);
  transform->SetInputConnection(clean->GetOutputPort());

  auto triangles = vtkSmartPointer<vtkTriangleFilter>::New();
  triangles->SetInputConnection(transform->GetOutputPort());

  auto norms = vtkSmartPointer<vtkPolyDataNormals>::New();
  norms->SetInputConnection(triangles->GetOutputPort());

  mapper->SetInputConnection(norms->GetOutputPort());
  mapper->ScalarVisibilityOff();

  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuse(1.0);
  actor->GetProperty()->SetDiffuseColor(
      colors->GetColor3d("ivoryblack").GetData());
  actor->GetProperty()->SetSpecular(.5);
  actor->GetProperty()->SetSpecularPower(2);

  // Modify the vertex shader to pass the position of the vertex
#if USE_SHADER_PROPERTIES
  vtkShaderProperty* sp = actor->GetShaderProperty();
  sp->AddVertexShaderReplacement(
      "//VTK::Normal::Dec",  // replace the normal block
      true,                  // before the standard replacements
      "//VTK::Normal::Dec\n" // we still want the default
      "  out vec4 myVertexMC;\n",
      false // only do it once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Vertex,
      "//VTK::Normal::Dec",  // replace the normal block
      true,                  // before the standard replacements
      "//VTK::Normal::Dec\n" // we still want the default
      "  out vec4 myVertexMC;\n",
      false // only do it once
  );
#endif
#if USE_SHADER_PROPERTIES
  sp->AddVertexShaderReplacement(
      "//VTK::Normal::Impl",  // replace the normal block
      true,                   // before the standard replacements
      "//VTK::Normal::Impl\n" // we still want the default
      "  myVertexMC = vertexMC;\n",
      false // only do it once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Vertex,
      "//VTK::Normal::Impl",  // replace the normal block
      true,                   // before the standard replacements
      "//VTK::Normal::Impl\n" // we still want the default
      "  myVertexMC = vertexMC;\n",
      false // only do it once
  );
#endif

  // Add the code to generate noise
  // These functions need to be defined outside of main. Use the System::Dec
  // to declare and implement
#if USE_SHADER_PROPERTIES
  sp->AddFragmentShaderReplacement("//VTK::System::Dec",
                                   false, // before the standard replacements
                                   shaderCode.str(),
                                   false // only do it once
  );
#else
  mapper->AddShaderReplacement(vtkShader::Fragment, "//VTK::System::Dec",
                               false, // before the standard replacements
                               shaderCode.str(),
                               false // only do it once
  );
#endif
  // Define varying and uniforms for the fragment shader here
#if USE_SHADER_PROPERTIES
  sp->AddFragmentShaderReplacement(
      "//VTK::Normal::Dec",  // replace the normal block
      true,                  // before the standard replacements
      "//VTK::Normal::Dec\n" // we still want the default
      "  varying vec4 myVertexMC;\n"
      "uniform float specksize = .05;\n"
      "uniform int sizes = 3;\n"
      "uniform vec3 basecolor = vec3(.7,.7,.7);\n"
      "uniform vec3 spattercolor = vec3(0.0, 0.0, 0.0);\n",
      false // only do it once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Fragment,   // in the fragment shader
      "//VTK::Normal::Dec",  // replace the normal block
      true,                  // before the standard replacements
      "//VTK::Normal::Dec\n" // we still want the default
      "  varying vec4 myVertexMC;\n"
      "uniform float specksize = .05;\n"
      "uniform int sizes = 3;\n"
      "uniform vec3 basecolor = vec3(.7,.7,.7);\n"
      "uniform vec3 spattercolor = vec3(0.0, 0.0, 0.0);\n",
      false // only do it once
  );
#endif

#if USE_SHADER_PROPERTIES
  sp->AddFragmentShaderReplacement(
      "//VTK::Light::Impl",  // replace the light block
      false,                 // after the standard replacements
      "//VTK::Light::Impl\n" // we still want the default calc
      "#define pnoise(x) ((noise(x) + 1.0) / 2.0)\n"
      "\n"
      "float speckle, size, threshold = 0.7;\n"
      "vec3 paint;\n"
      "float scalefac;\n"
      "vec4 myLocalVertexMC = myVertexMC;\n"
      "scalefac = 1.0/specksize;\n"
      "paint = basecolor;\n"
      "for (size=1; size<=sizes; size +=1) {\n"
      "  speckle = pnoise(myLocalVertexMC * scalefac);\n"
      "  if (speckle > threshold) {\n"
      "    paint = spattercolor;\n"
      "    break;\n"
      "  }\n"
      "  scalefac /= 2.0;\n"
      "}\n"
      "/* get final color */\n"
      "fragOutput0.rgb = opacity * vec3(ambientColor + paint + specular);\n"
      "fragOutput0.a = opacity;\n",
      false // only do once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Fragment,   // in the fragment shader
      "//VTK::Light::Impl",  // replace the light block
      false,                 // after the standard replacements
      "//VTK::Light::Impl\n" // we still want the default calc
      "#define pnoise(x) ((noise(x) + 1.0) / 2.0)\n"
      "\n"
      "float speckle, size, threshold = 0.7;\n"
      "vec3 paint;\n"
      "float scalefac;\n"
      "vec4 myLocalVertexMC = myVertexMC;\n"
      "scalefac = 1.0/specksize;\n"
      "paint = basecolor;\n"
      "for (size=1; size<=sizes; size +=1) {\n"
      "  speckle = pnoise(myLocalVertexMC * scalefac);\n"
      "  if (speckle > threshold) {\n"
      "    paint = spattercolor;\n"
      "    break;\n"
      "  }\n"
      "  scalefac /= 2.0;\n"
      "}\n"
      "/* get final color */\n"
      "fragOutput0.rgb = opacity * vec3(ambientColor + paint + specular);\n"
      "fragOutput0.a = opacity;\n",
      false // only do once
  );
#endif

  auto myCallback = vtkSmartPointer<ShaderCallback>::New();
  myCallback->Renderer = renderer;
  if (argc == 4)
  {
    myCallback->specksize = atof(argv[3]);
  }
  if (argc == 5)
  {
    myCallback->specksize = atof(argv[3]);
    myCallback->sizes = atoi(argv[4]);
  }
  if (argc == 8)
  {
    myCallback->specksize = atof(argv[3]);
    myCallback->sizes = atoi(argv[4]);
    myCallback->basecolor[0] = atof(argv[5]);
    myCallback->basecolor[1] = atof(argv[6]);
    myCallback->basecolor[2] = atof(argv[7]);
  }
  if (argc == 11)
  {
    myCallback->specksize = atof(argv[3]);
    myCallback->sizes = atoi(argv[4]);
    myCallback->basecolor[0] = atof(argv[5]);
    myCallback->basecolor[1] = atof(argv[6]);
    myCallback->basecolor[2] = atof(argv[7]);
    myCallback->spattercolor[0] = atof(argv[8]);
    myCallback->spattercolor[1] = atof(argv[9]);
    myCallback->spattercolor[2] = atof(argv[10]);
  }
  std::cout << "Input: " << (argc > 2 ? argv[2] : "Generated Sphere")
            << std::endl;
  myCallback->Print(std::cout);
  mapper->AddObserver(vtkCommand::UpdateShaderEvent, myCallback);

  renderWindow->Render();
  renderer->GetActiveCamera()->SetPosition(-.3, 0, .08);
  renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  renderer->GetActiveCamera()->SetViewUp(.26, 0.0, .96);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(1.5);
  renderWindow->Render();
  renderWindow->SetWindowName("SpatterShader");
  renderWindow->Render();
  interactor->Start();

  transform->GetOutput()->GetBounds(bounds);
  std::cout << "Range: "
            << " x " << bounds[1] - bounds[0] << " y " << bounds[3] - bounds[2]
            << " y " << bounds[5] - bounds[4] << std::endl;
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
