#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>
#include <vtkOpenGLPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkShaderProgram.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTriangleFilter.h>
#include <vtkTriangleMeshPointNormals.h>
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
  float veincolor[3];
  float veinfreq;
  int veinlevels;
  float warpfreq;
  float warping;
  float sharpness;

  void Execute(vtkObject*, unsigned long, void* calldata) override
  {
    vtkShaderProgram* program = reinterpret_cast<vtkShaderProgram*>(calldata);
    if (program)
    {
      program->SetUniform3f("veincolor", veincolor);
      program->SetUniformf("veinfreq", veinfreq);
      program->SetUniformi("veinlevels", veinlevels);
      program->SetUniformf("warpfreq", warpfreq);
      program->SetUniformf("warping", warping);
      program->SetUniformf("sharpness", sharpness);
    }
  }
  void Print(std::ostream& os)
  {
    os << "veincolor: " << veincolor[0] << ", " << veincolor[1] << ", "
       << veincolor[2] << std::endl;
    os << "veinfreq: " << veinfreq << std::endl;
    os << "veinlevels: " << veinlevels << std::endl;
    os << "warpfreq: " << warpfreq << std::endl;
    os << "warping: " << warping << std::endl;
    os << "sharpness: " << sharpness << std::endl;
  }

  ShaderCallback()
  {
    this->Renderer = nullptr;
    this->veincolor[0] = this->veincolor[1] = this->veincolor[2] = 1.0;
    this->veinfreq = 10.0;
    this->veinlevels = 2;
    this->warpfreq = 1.0;
    this->warping = .5;
    this->sharpness = 8.0;
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
              << "[veincolor(1,1,1)] "
              << "[veinfreq(10)] "
              << "[veinlevels(2)] "
              << "[warpfreq(1)] "
              << "[warping(.5)] "
              << "[sharpness(8)]" << std::endl;
    return EXIT_FAILURE;
  }

  auto polyData = ReadPolyData(2 ? argv[2] : "");

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

  // Rescale polydata to [-1,1]
  auto userTransform = vtkSmartPointer<vtkTransform>::New();
  userTransform->Translate(-center[0], -center[1], -center[2]);
  userTransform->Scale(1.0 / maxBound, 1.0 / maxBound, 1.0 / maxBound);
  auto transform = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transform->SetTransform(userTransform);
  transform->SetInputData(polyData);

  auto triangles = vtkSmartPointer<vtkTriangleFilter>::New();
  triangles->SetInputConnection(transform->GetOutputPort());

  auto norms = vtkSmartPointer<vtkTriangleMeshPointNormals>::New();
  norms->SetInputConnection(triangles->GetOutputPort());

  mapper->SetInputConnection(norms->GetOutputPort());
  mapper->ScalarVisibilityOff();

  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuse(1.0);
  actor->GetProperty()->SetDiffuseColor(
      colors->GetColor3d("ivoryblack").GetData());
  actor->GetProperty()->SetSpecular(.5);
  actor->GetProperty()->SetSpecularPower(5);

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
      "  uniform vec3 veincolor = vec3(1.0, 1.0, 1.0);\n"
      "  uniform float veinfreq = 10.0;\n"
      "  uniform int veinlevels = 2;\n"
      "  uniform float warpfreq = 1;\n"
      "  uniform float warping = .5;\n"
      "  uniform float sharpness = 8.0;\n",
      false // only do it once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Fragment,   // in the fragment shader
      "//VTK::Normal::Dec",  // replace the normal block
      true,                  // before the standard replacements
      "//VTK::Normal::Dec\n" // we still want the default
      "  varying vec4 myVertexMC;\n"
      "  uniform vec3 veincolor = vec3(1.0, 1.0, 1.0);\n"
      "  uniform float veinfreq = 10.0;\n"
      "  uniform int veinlevels = 2;\n"
      "  uniform float warpfreq = 1;\n"
      "  uniform float warping = .5;\n"
      "  uniform float sharpness = 8.0;\n",
      false // only do it once
  );
#endif

#if USE_SHADER_PROPERTIES
  sp->AddFragmentShaderReplacement(
      "//VTK::Light::Impl",  // replace the light block
      false,                 // after the standard replacements
      "//VTK::Light::Impl\n" // we still want the default calc
      "\n"
      "#define pnoise(x) ((noise(x) + 1.0) / 2.0)\n"
      "#define snoise(x) (2.0 * pnoise(x) - 1.0)\n"
      "  vec3 Ct;\n"
      "  int i;\n"
      "  float turb, freq;\n"
      "  float turbsum;\n"
      "  /* perturb the lookup */\n"
      "  freq = 1.0;\n"
      "  vec4 offset = vec4(0.0,0.0,0.0,0.0);\n"
      "  vec4 noisyPoint;\n"
      "  vec4 myLocalVertexMC = myVertexMC;\n"
      "\n"
      "    for (i = 0;  i < 6;  i += 1) {\n"
      "      noisyPoint[0] = snoise(warpfreq * freq * myLocalVertexMC);\n"
      "      noisyPoint[1] = snoise(warpfreq * freq * myLocalVertexMC);\n"
      "      noisyPoint[2] = snoise(warpfreq * freq * myLocalVertexMC);\n"
      "      noisyPoint[3] = 1.0;\n"
      "      offset += 2.0 * warping * (noisyPoint - 0.5)  / freq;\n"
      "      freq *= 2.0;\n"
      "    }\n"
      "    myLocalVertexMC.x += offset.x;\n"
      "    myLocalVertexMC.y += offset.y;\n"
      "    myLocalVertexMC.z += offset.z;\n"
      "\n"
      "    /* Now calculate the veining function for the lookup area */\n"
      "    turbsum = 0.0;  freq = 1.0;\n"
      "    myLocalVertexMC *= veinfreq;\n"
      "    for (i = 0;  i < veinlevels;  i += 1) {\n"
      "      turb = abs (snoise (myLocalVertexMC));\n"
      "      turb = pow (smoothstep (0.8, 1.0, 1.0 - turb), sharpness) / "
      "freq;\n"
      "      turbsum += (1.0-turbsum) * turb;\n"
      "      freq *= 1.5;\n"
      "      myLocalVertexMC *= 1.5;\n"
      "    }\n"
      "\n"
      "    Ct = mix (diffuseColor, veincolor, turbsum);\n"
      "\n"
      "  fragOutput0.rgb = opacity * (ambientColor + Ct + specular);\n"
      "  fragOutput0.a = opacity;\n",
      false // only do it once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Fragment,   // in the fragment shader
      "//VTK::Light::Impl",  // replace the light block
      false,                 // after the standard replacements
      "//VTK::Light::Impl\n" // we still want the default calc
      "\n"
      "#define pnoise(x) ((noise(x) + 1.0) / 2.0)\n"
      "#define snoise(x) (2.0 * pnoise(x) - 1.0)\n"
      "  vec3 Ct;\n"
      "  int i;\n"
      "  float turb, freq;\n"
      "  float turbsum;\n"
      "  /* perturb the lookup */\n"
      "  freq = 1.0;\n"
      "  vec4 offset = vec4(0.0,0.0,0.0,0.0);\n"
      "  vec4 noisyPoint;\n"
      "  vec4 myLocalVertexMC = myVertexMC;\n"
      "\n"
      "    for (i = 0;  i < 6;  i += 1) {\n"
      "      noisyPoint[0] = snoise(warpfreq * freq * myLocalVertexMC);\n"
      "      noisyPoint[1] = snoise(warpfreq * freq * myLocalVertexMC);\n"
      "      noisyPoint[2] = snoise(warpfreq * freq * myLocalVertexMC);\n"
      "      noisyPoint[3] = 1.0;\n"
      "      offset += 2.0 * warping * (noisyPoint - 0.5)  / freq;\n"
      "      freq *= 2.0;\n"
      "    }\n"
      "    myLocalVertexMC.x += offset.x;\n"
      "    myLocalVertexMC.y += offset.y;\n"
      "    myLocalVertexMC.z += offset.z;\n"
      "\n"
      "    /* Now calculate the veining function for the lookup area */\n"
      "    turbsum = 0.0;  freq = 1.0;\n"
      "    myLocalVertexMC *= veinfreq;\n"
      "    for (i = 0;  i < veinlevels;  i += 1) {\n"
      "      turb = abs (snoise (myLocalVertexMC));\n"
      "      turb = pow (smoothstep (0.8, 1.0, 1.0 - turb), sharpness) / "
      "freq;\n"
      "      turbsum += (1.0-turbsum) * turb;\n"
      "      freq *= 1.5;\n"
      "      myLocalVertexMC *= 1.5;\n"
      "    }\n"
      "\n"
      "    Ct = mix (diffuseColor, veincolor, turbsum);\n"
      "\n"
      "  fragOutput0.rgb = opacity * (ambientColor + Ct + specular);\n"
      "  fragOutput0.a = opacity;\n",
      false // only do it once
  );
#endif

  auto myCallback = vtkSmartPointer<ShaderCallback>::New();
  myCallback->Renderer = renderer;
  if (argc == 6)
  {
    myCallback->veincolor[0] = atof(argv[3]);
    myCallback->veincolor[1] = atof(argv[4]);
    myCallback->veincolor[2] = atof(argv[5]);
  }
  if (argc == 7)
  {
    myCallback->veincolor[0] = atof(argv[3]);
    myCallback->veincolor[1] = atof(argv[4]);
    myCallback->veincolor[2] = atof(argv[5]);
    myCallback->veinfreq = atof(argv[6]);
  }
  if (argc == 8)
  {
    myCallback->veincolor[0] = atof(argv[3]);
    myCallback->veincolor[1] = atof(argv[4]);
    myCallback->veincolor[2] = atof(argv[5]);
    myCallback->veinfreq = atof(argv[6]);
    myCallback->veinlevels = atoi(argv[7]);
  }
  if (argc == 9)
  {
    myCallback->veincolor[0] = atof(argv[3]);
    myCallback->veincolor[1] = atof(argv[4]);
    myCallback->veincolor[2] = atof(argv[5]);
    myCallback->veinfreq = atof(argv[6]);
    myCallback->veinlevels = atoi(argv[7]);
    myCallback->warpfreq = atof(argv[8]);
  }
  if (argc == 10)
  {
    myCallback->veincolor[0] = atof(argv[3]);
    myCallback->veincolor[1] = atof(argv[4]);
    myCallback->veincolor[2] = atof(argv[5]);
    myCallback->veinfreq = atof(argv[6]);
    myCallback->veinlevels = atoi(argv[7]);
    myCallback->warpfreq = atof(argv[8]);
    myCallback->warping = atof(argv[9]);
  }
  if (argc == 11)
  {
    myCallback->veincolor[0] = atof(argv[3]);
    myCallback->veincolor[1] = atof(argv[4]);
    myCallback->veincolor[2] = atof(argv[5]);
    myCallback->veinfreq = atof(argv[6]);
    myCallback->veinlevels = atoi(argv[7]);
    myCallback->warpfreq = atof(argv[8]);
    myCallback->warping = atof(argv[9]);
    myCallback->sharpness = atof(argv[10]);
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
  renderWindow->SetWindowName("MarbleShader");
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
