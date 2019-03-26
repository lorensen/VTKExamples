#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>
#include <vtkOpenGLPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkShaderProgram.h>
#include <vtkSmartPointer.h>
#include <vtkVersion.h>

#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
#include <vtkShaderProperty.h>
#endif

#include <vtkRenderWindowInteractor.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTriangleFilter.h>
#include <vtkTriangleMeshPointNormals.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>
#include <vtksys/SystemTools.hxx>

#include <vtkSliderRepresentation2D.h>
#include <vtkSliderWidget.h>

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
  float veinlevels;
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
      std::cout << "------------" << std::endl;
      Print(std::cout);
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

// These callbacks do the actual work.
// Callbacks for the interactions
class SliderCallbackVeinFreq : public vtkCommand
{
public:
  static SliderCallbackVeinFreq* New()
  {
    return new SliderCallbackVeinFreq;
  }
  virtual void Execute(vtkObject* caller, unsigned long, void*)
  {
    vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);

    float value = static_cast<vtkSliderRepresentation2D*>(
      sliderWidget->GetRepresentation())
      ->GetValue();
    this->Shader->veinfreq = value;
  }
  SliderCallbackVeinFreq() : Shader(0)
  {
  }
  ShaderCallback* Shader;
};

// These callbacks do the actual work.
// Callbacks for the interactions
class SliderCallbackVeinLevels : public vtkCommand
{
public:
  static SliderCallbackVeinLevels* New()
  {
    return new SliderCallbackVeinLevels;
  }
  virtual void Execute(vtkObject* caller, unsigned long, void*)
  {
    vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);

    int value = static_cast<vtkSliderRepresentation2D*>(
      sliderWidget->GetRepresentation())
      ->GetValue();
    static_cast<vtkSliderRepresentation2D*>(sliderWidget->GetRepresentation())
      ->SetValue(value);
    this->Shader->veinlevels = value;
  }
  SliderCallbackVeinLevels() : Shader(0)
  {
  }
  ShaderCallback* Shader;
};

class SliderCallbackWarpFreq : public vtkCommand
{
public:
  static SliderCallbackWarpFreq* New()
  {
    return new SliderCallbackWarpFreq;
  }
  virtual void Execute(vtkObject* caller, unsigned long, void*)
  {
    vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);

    float value = static_cast<vtkSliderRepresentation2D*>(
      sliderWidget->GetRepresentation())
      ->GetValue();
    this->Shader->warpfreq = value;
  }
  SliderCallbackWarpFreq() : Shader(0)
  {
  }
  ShaderCallback* Shader;
};

class SliderCallbackWarping : public vtkCommand
{
public:
  static SliderCallbackWarping* New()
  {
    return new SliderCallbackWarping;
  }
  virtual void Execute(vtkObject* caller, unsigned long, void*)
  {
    vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);

    float value = static_cast<vtkSliderRepresentation2D*>(
      sliderWidget->GetRepresentation())
      ->GetValue();
    this->Shader->warping = value;
  }
  SliderCallbackWarping() : Shader(0)
  {
  }
  ShaderCallback* Shader;
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

  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(argc > 2 ? argv[2] : "");

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

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkOpenGLPolyDataMapper> mapper =
    vtkSmartPointer<vtkOpenGLPolyDataMapper>::New();
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Rescale polydata to [-1,1]
  vtkSmartPointer<vtkTransform> userTransform =
    vtkSmartPointer<vtkTransform>::New();
  userTransform->Translate(-center[0], -center[1], -center[2]);
  userTransform->Scale(1.0 / maxBound, 1.0 / maxBound, 1.0 / maxBound);
  vtkSmartPointer<vtkTransformPolyDataFilter> transform =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transform->SetTransform(userTransform);
  transform->SetInputData(polyData);

  vtkSmartPointer<vtkTriangleFilter> triangles =
    vtkSmartPointer<vtkTriangleFilter>::New();
  triangles->SetInputConnection(transform->GetOutputPort());

  vtkSmartPointer<vtkTriangleMeshPointNormals> norms =
    vtkSmartPointer<vtkTriangleMeshPointNormals>::New();
  norms->SetInputConnection(triangles->GetOutputPort());

  mapper->SetInputConnection(norms->GetOutputPort());
  mapper->ScalarVisibilityOff();

  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuse(1.0);
  actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("wheat").GetData());
  actor->GetProperty()->SetSpecular(.5);
  actor->GetProperty()->SetSpecularPower(50);

  // Modify the vertex shader to pass the position of the vertex
#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
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
#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
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
#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
  sp->AddFragmentShaderReplacement(
    "//VTK::System::Dec",
    false, // before the standard replacements
    shaderCode.str(),
    false // only do it once
    );
#else
  mapper->AddShaderReplacement(
    vtkShader::Fragment, // in the fragment shader
    "//VTK::System::Dec",
    false, // before the standard replacements
    shaderCode.str(),
    false // only do it once
    );
#endif
// Define varying and uniforms for the fragment shader here
#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
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
    vtkShader::Fragment, // in the fragment shader
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
#if VTK_MAJOR_VERSION > 8 || VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION >= 90
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
    vtkShader::Fragment, // in the fragment shader
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

  vtkSmartPointer<ShaderCallback> myCallback =
    vtkSmartPointer<ShaderCallback>::New();
  myCallback->Renderer = renderer;

  std::cout << "Input: " << (argc > 2 ? argv[2] : "Generated Sphere")
            << std::endl;
  myCallback->Print(std::cout);
  mapper->AddObserver(vtkCommand::UpdateShaderEvent, myCallback);

  // Setup a slider widget for each varying parameter
  double tubeWidth(.015);
  double sliderLength(.008);
  double titleHeight(.02);
  double labelHeight(.02);

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRepVeinFreq =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepVeinFreq->SetMinimumValue(1.0);
  sliderRepVeinFreq->SetMaximumValue(15.0);
  sliderRepVeinFreq->SetValue(7.5);
  sliderRepVeinFreq->SetTitleText("Vein Frequency");

  sliderRepVeinFreq->GetPoint1Coordinate()
    ->SetCoordinateSystemToNormalizedDisplay();
  sliderRepVeinFreq->GetPoint1Coordinate()->SetValue(.1, .1);
  sliderRepVeinFreq->GetPoint2Coordinate()
    ->SetCoordinateSystemToNormalizedDisplay();
  sliderRepVeinFreq->GetPoint2Coordinate()->SetValue(.9, .1);

  sliderRepVeinFreq->SetTubeWidth(tubeWidth);
  sliderRepVeinFreq->SetSliderLength(sliderLength);
  sliderRepVeinFreq->SetTitleHeight(titleHeight);
  sliderRepVeinFreq->SetLabelHeight(labelHeight);

  vtkSmartPointer<vtkSliderWidget> sliderWidgetVeinFreq =
    vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidgetVeinFreq->SetInteractor(interactor);
  sliderWidgetVeinFreq->SetRepresentation(sliderRepVeinFreq);
  sliderWidgetVeinFreq->SetAnimationModeToJump();
  sliderWidgetVeinFreq->EnabledOn();

  vtkSmartPointer<SliderCallbackVeinFreq> callbackVeinFreq =
    vtkSmartPointer<SliderCallbackVeinFreq>::New();
  callbackVeinFreq->Shader = myCallback;

  sliderWidgetVeinFreq->AddObserver(vtkCommand::InteractionEvent,
                                    callbackVeinFreq);

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRepVeinLevels =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepVeinLevels->SetMinimumValue(1);
  sliderRepVeinLevels->SetMaximumValue(5);
  sliderRepVeinLevels->SetValue(3);
  sliderRepVeinLevels->SetTitleText("Vein Levels");

  sliderRepVeinLevels->GetPoint1Coordinate()
    ->SetCoordinateSystemToNormalizedDisplay();
  sliderRepVeinLevels->GetPoint1Coordinate()->SetValue(.1, .9);
  sliderRepVeinLevels->GetPoint2Coordinate()
    ->SetCoordinateSystemToNormalizedDisplay();
  sliderRepVeinLevels->GetPoint2Coordinate()->SetValue(.9, .9);

  sliderRepVeinLevels->SetTubeWidth(tubeWidth);
  sliderRepVeinLevels->SetSliderLength(sliderLength);
  sliderRepVeinLevels->SetTitleHeight(titleHeight);
  sliderRepVeinLevels->SetLabelHeight(labelHeight);

  vtkSmartPointer<vtkSliderWidget> sliderWidgetVeinLevels =
    vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidgetVeinLevels->SetInteractor(interactor);
  sliderWidgetVeinLevels->SetRepresentation(sliderRepVeinLevels);
  sliderWidgetVeinLevels->SetAnimationModeToJump();
  sliderWidgetVeinLevels->EnabledOn();

  vtkSmartPointer<SliderCallbackVeinLevels> callbackVeinLevels =
    vtkSmartPointer<SliderCallbackVeinLevels>::New();
  callbackVeinLevels->Shader = myCallback;
  myCallback->veincolor[0] = colors->GetColor3d("Green").GetData()[0];
  myCallback->veincolor[1] = colors->GetColor3d("Green").GetData()[1];
  myCallback->veincolor[2] = colors->GetColor3d("Green").GetData()[2];
  sliderWidgetVeinLevels->AddObserver(vtkCommand::InteractionEvent,
                                      callbackVeinLevels);

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRepWarpFreq =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepWarpFreq->SetMinimumValue(1.0);
  sliderRepWarpFreq->SetMaximumValue(2.0);
  sliderRepWarpFreq->SetValue(1.5);
  sliderRepWarpFreq->SetTitleText("Warp Frequency");

  sliderRepWarpFreq->GetPoint1Coordinate()
    ->SetCoordinateSystemToNormalizedDisplay();
  sliderRepWarpFreq->GetPoint1Coordinate()->SetValue(.1, .1);
  sliderRepWarpFreq->GetPoint2Coordinate()
    ->SetCoordinateSystemToNormalizedDisplay();
  sliderRepWarpFreq->GetPoint2Coordinate()->SetValue(.1, .9);

  sliderRepWarpFreq->SetTubeWidth(tubeWidth);
  sliderRepWarpFreq->SetSliderLength(sliderLength);
  sliderRepWarpFreq->SetTitleHeight(titleHeight);
  sliderRepWarpFreq->SetLabelHeight(labelHeight);

  vtkSmartPointer<vtkSliderWidget> sliderWidgetWarpFreq =
    vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidgetWarpFreq->SetInteractor(interactor);
  sliderWidgetWarpFreq->SetRepresentation(sliderRepWarpFreq);
  sliderWidgetWarpFreq->SetAnimationModeToJump();
  sliderWidgetWarpFreq->EnabledOn();

  vtkSmartPointer<SliderCallbackWarpFreq> callbackWarpFreq =
    vtkSmartPointer<SliderCallbackWarpFreq>::New();
  callbackWarpFreq->Shader = myCallback;

  sliderWidgetWarpFreq->AddObserver(vtkCommand::InteractionEvent,
                                    callbackWarpFreq);

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRepWarping =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepWarping->SetMinimumValue(0.0);
  sliderRepWarping->SetMaximumValue(1.0);
  sliderRepWarping->SetValue(.5);
  sliderRepWarping->SetTitleText("Warping");

  sliderRepWarping->GetPoint1Coordinate()
    ->SetCoordinateSystemToNormalizedDisplay();
  sliderRepWarping->GetPoint1Coordinate()->SetValue(.9, .1);
  sliderRepWarping->GetPoint2Coordinate()
    ->SetCoordinateSystemToNormalizedDisplay();
  sliderRepWarping->GetPoint2Coordinate()->SetValue(.9, .9);

  sliderRepWarping->SetTubeWidth(tubeWidth);
  sliderRepWarping->SetSliderLength(sliderLength);
  sliderRepWarping->SetTitleHeight(titleHeight);
  sliderRepWarping->SetLabelHeight(labelHeight);

  vtkSmartPointer<vtkSliderWidget> sliderWidgetWarping =
    vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidgetWarping->SetInteractor(interactor);
  sliderWidgetWarping->SetRepresentation(sliderRepWarping);
  sliderWidgetWarping->SetAnimationModeToJump();
  sliderWidgetWarping->EnabledOn();

  vtkSmartPointer<SliderCallbackWarping> callbackWarping =
    vtkSmartPointer<SliderCallbackWarping>::New();
  callbackWarping->Shader = myCallback;

  sliderWidgetWarping->AddObserver(vtkCommand::InteractionEvent,
                                   callbackWarping);

  renderWindow->Render();
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(1.5);
  renderWindow->Render();
  renderWindow->SetWindowName("MarbleShaderDemo");
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
    vtkSmartPointer<vtkPLYReader> reader =
      vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    vtkSmartPointer<vtkOBJReader> reader =
      vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    vtkSmartPointer<vtkSTLReader> reader =
      vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    vtkSmartPointer<vtkPolyDataReader> reader =
      vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    vtkSmartPointer<vtkBYUReader> reader =
      vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> source =
      vtkSmartPointer<vtkSphereSource>::New();
    source->SetPhiResolution(25);
    source->SetThetaResolution(25);
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
} // namespace
