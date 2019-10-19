
#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkCubeSource.h>
#include <vtkImageFlip.h>
#include <vtkImageReader2Factory.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkJPEGReader.h>
#include <vtkNamedColors.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkParametricBoy.h>
#include <vtkParametricFunctionSource.h>
#include <vtkParametricMobius.h>
#include <vtkParametricTorus.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSkybox.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkSliderWidget.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTexture.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTriangleFilter.h>
#include <vtkVersion.h>

#include <array>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace {
/**
 * Show the command lime parameters.
 *
 * @param fn: The program name.
 *
 * @return A string describing the usage.
 */
std::string ShowUsage(std::string fn);

/**
 * Check the VTK version.
 *
 * @param major: Major version.
 * @param major: Minor version.
 * @param major: Build version.
 *
 * @return True if the requested VTK version is greater or equal to the actual
 * VTK version.
 */
bool VTKVersionOk(unsigned long long const& major,
                  unsigned long long const& minor,
                  unsigned long long const& build);

/**
 * Read the cube map.
 *
 * @param folderRoot: The folder where the cube maps are stored.
 * @param fileRoot: The root of the individual cube map file names.
 * @param ext: The extension of the cube map files.
 * @param key: The key to data used to build the full file name.
 *
 * @return The cubemap texture.
 */
vtkSmartPointer<vtkTexture> ReadCubeMap(std::string const& folderRoot,
                                        std::string const& fileRoot,
                                        std::string const& ext, int const& key);

// Some sample surfaces to try.
vtkSmartPointer<vtkPolyData> GetBoy();
vtkSmartPointer<vtkPolyData> GetMobius();
vtkSmartPointer<vtkPolyData> GetSphere();
vtkSmartPointer<vtkPolyData> GetTorus();
vtkSmartPointer<vtkPolyData> GetCube();

class SliderCallbackMetallic : public vtkCommand
{
public:
  static SliderCallbackMetallic* New()
  {
    return new SliderCallbackMetallic;
  }
  virtual void Execute(vtkObject* caller, unsigned long, void*)
  {
    vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D*>(
                       sliderWidget->GetRepresentation())
                       ->GetValue();
    this->property->SetMetallic(value);
  }
  SliderCallbackMetallic() : property(nullptr)
  {
  }
  vtkProperty* property;
};

class SliderCallbackRoughness : public vtkCommand
{
public:
  static SliderCallbackRoughness* New()
  {
    return new SliderCallbackRoughness;
  }
  virtual void Execute(vtkObject* caller, unsigned long, void*)
  {
    vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D*>(
                       sliderWidget->GetRepresentation())
                       ->GetValue();
    this->property->SetRoughness(value);
  }
  SliderCallbackRoughness() : property(nullptr)
  {
  }
  vtkProperty* property;
};

struct SliderProperties
{
  // Set up the sliders
  double tubeWidth{0.008};
  double sliderLength{0.008};
  double titleHeight{0.02};
  double labelHeight{0.02};

  double minimumValue{0.0};
  double maximumValue{1.0};
  double initialValue{0.0};

  std::array<double, 2> p1{0.1, 0.1};
  std::array<double, 2> p2{0.9, 0.1};

  std::string title{""};
};

vtkSmartPointer<vtkSliderWidget>
MakeSliderWidget(SliderProperties const& properties);

} // namespace

int main(int argc, char* argv[])
{
  if (!VTKVersionOk(8, 90, 0))
  {
    std::cerr << "You need VTK version 8.90 or greater to run this program."
              << std::endl;
    return EXIT_FAILURE;
  }
  if (argc < 2)
  {
    std::cout << ShowUsage(argv[0]) << std::endl;
    return EXIT_FAILURE;
  }

  std::string desiredSurface = "boy";
  if (argc > 2)
  {
    desiredSurface = argv[2];
  }
  std::transform(desiredSurface.begin(), desiredSurface.end(),
                 desiredSurface.begin(),
                 [](char c) { return std::tolower(c); });
  std::map<std::string, int> availableSurfaces = {
      {"boy", 0}, {"mobius", 1}, {"torus", 2}, {"sphere", 3}, {"cube", 4}};
  if (availableSurfaces.find(desiredSurface) == availableSurfaces.end())
  {
    desiredSurface = "boy";
  }
  auto source = vtkSmartPointer<vtkPolyData>::New();
  switch (availableSurfaces[desiredSurface])
  {
  case 1:
    source = GetMobius();
    break;
  case 2:
    source = GetTorus();
    break;
  case 3:
    source = GetSphere();
    break;
  case 4:
    source = GetCube();
    break;
  case 0:
  default:
    source = GetBoy();
  };

  // Load the cube map
  // auto cubemap = ReadCubeMap(argv[1], "/", ".jpg", 0);
  auto cubemap = ReadCubeMap(argv[1], "/", ".jpg", 1);
  // auto cubemap = ReadCubeMap(argv[1], "/skybox", ".jpg", 2);

  // Load the skybox
  // Read it again as there is no deep copy for vtkTexture
  // auto skybox = ReadCubeMap(argv[1], "/", ".jpg", 0);
  auto skybox = ReadCubeMap(argv[1], "/", ".jpg", 1);
  // auto skybox = ReadCubeMap(argv[1], "/skybox", ".jpg", 2);
  skybox->InterpolateOn();
  skybox->RepeatOff();
  skybox->EdgeClampOn();

  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  std::array<unsigned char, 4> bkg{{26, 51, 102, 255}};
  colors->SetColor("BkgColor", bkg.data());

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Lets use a smooth metallic surface
  auto metallicCoefficient = 1.0;
  auto roughnessCoefficient = 0.05;

  auto slwP = SliderProperties();
  slwP.initialValue = metallicCoefficient;
  slwP.title = "Metallicity";

  auto sliderWidgetMetallic = MakeSliderWidget(slwP);
  sliderWidgetMetallic->SetInteractor(interactor);
  sliderWidgetMetallic->SetAnimationModeToAnimate();
  sliderWidgetMetallic->EnabledOn();

  slwP.initialValue = roughnessCoefficient;
  slwP.title = "Roughness";
  slwP.p1[0] = 0.1;
  slwP.p1[1] = 0.9;
  slwP.p2[0] = 0.9;
  slwP.p2[1] = 0.9;

  auto sliderWidgetRoughness = MakeSliderWidget(slwP);
  sliderWidgetRoughness->SetInteractor(interactor);
  sliderWidgetRoughness->SetAnimationModeToAnimate();
  sliderWidgetRoughness->EnabledOn();

  // Build the pipeline
  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(source);

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  renderer->UseImageBasedLightingOn();
  renderer->SetEnvironmentCubeMap(cubemap);
  actor->GetProperty()->SetInterpolationToPBR();

  // configure the basic properties
  actor->GetProperty()->SetColor(colors->GetColor4d("White").GetData());
  actor->GetProperty()->SetMetallic(metallicCoefficient);
  actor->GetProperty()->SetRoughness(roughnessCoefficient);

  // Create the slider callbacks to manipulate metallicity and roughness
  auto callbackMetallic = vtkSmartPointer<SliderCallbackMetallic>::New();
  callbackMetallic->property = actor->GetProperty();
  auto callbackRoughness = vtkSmartPointer<SliderCallbackRoughness>::New();
  callbackRoughness->property = actor->GetProperty();

  sliderWidgetMetallic->AddObserver(vtkCommand::InteractionEvent,
                                    callbackMetallic);
  sliderWidgetRoughness->AddObserver(vtkCommand::InteractionEvent,
                                     callbackRoughness);

  renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
  renderer->AddActor(actor);

  auto skyboxActor = vtkSmartPointer<vtkSkybox>::New();
  skyboxActor->SetTexture(skybox);
  renderer->AddActor(skyboxActor);

  renderWindow->SetSize(640, 480);
  renderWindow->Render();
  renderWindow->SetWindowName("Skybox-PBR");

  auto axes = vtkSmartPointer<vtkAxesActor>::New();

  auto widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  double rgba[4]{0.0, 0.0, 0.0, 0.0};
  colors->GetColor("Carrot", rgba);
  widget->SetOutlineColor(rgba[0], rgba[1], rgba[2]);
  widget->SetOrientationMarker(axes);
  widget->SetInteractor(interactor);
  widget->SetViewport(0.0, 0.2, 0.2, 0.4);
  widget->SetEnabled(1);
  widget->InteractiveOn();

  interactor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  interactor->Start();
  return EXIT_SUCCESS;
}

namespace {
std::string ShowUsage(std::string fn)
{
  // Remove the folder (if present) then remove the extension in this order
  // since the folder name may contain periods.
  auto last_slash_idx = fn.find_last_of("\\/");
  if (std::string::npos != last_slash_idx)
  {
    fn.erase(0, last_slash_idx + 1);
  }
  auto period_idx = fn.rfind('.');
  if (std::string::npos != period_idx)
  {
    fn.erase(period_idx);
  }
  std::ostringstream os;
  os << "\nusage: " << fn << " path [surface]\n\n"
     << "Demonstrates physically based rendering, image based lighting and a "
        "skybox.\n\n"
     << "positional arguments:\n"
     << "  path        The path to the cubemap files.\n"
     << "  surface     The surface to use. Boy's surface is the default.\n\n"
     << "Physically based rendering sets color, metallicity and roughness of "
        "the object.\n"
     << "Image based lighting uses a cubemap texture to specify the "
        "environment.\n"
     << "A Skybox is used to create the illusion of distant three-dimensional "
        "surroundings.\n"
     << "\n"
     << std::endl;
  return os.str();
}

bool VTKVersionOk(unsigned long long const& major,
                  unsigned long long const& minor,
                  unsigned long long const& build)
{
  unsigned long long neededVersion =
      10000000000ULL * major + 100000000ULL * minor + build;
#ifndef VTK_VERSION_NUMBER
  auto ver = vtkSmartPointer<vtkVersion>();
  unsigned long long vtk_version_number =
      10000000000ULL * ver->GetVTKMajorVersion() +
      100000000ULL * ver->GetVTKMinorVersion() + ver->GetVTKBuildVersion();
  if (vtk_version_number <= neededVersion)
  {
    return true;
  }
#else
  if (VTK_VERSION_NUMBER <= neededVersion)
  {
    return true;
  }
#endif
  return false;
}

vtkSmartPointer<vtkTexture> ReadCubeMap(std::string const& folderRoot,
                                        std::string const& fileRoot,
                                        std::string const& ext, int const& key)
{
  // A map of cube map naming conventions and the corresponding file name
  // components.
  std::map<int, std::vector<std::string>> fileNames{
      {0, {"right", "left", "top", "bottom", "front", "back"}},
      {1, {"posx", "negx", "posy", "negy", "posz", "negz"}},
      {2, {"-px", "-nx", "-py", "-ny", "-pz", "-nz"}},
      {3, {"0", "1", "2", "3", "4", "5"}}};
  std::vector<std::string> fns;
  if (fileNames.count(key))
  {
    fns = fileNames.at(key);
  }
  else
  {
    std::cerr << "ReadCubeMap(): invalid key, unable to continue." << std::endl;
    std::exit(EXIT_FAILURE);
  }
  auto texture = vtkSmartPointer<vtkTexture>::New();
  texture->CubeMapOn();
  // Build the file names.
  std::for_each(fns.begin(), fns.end(),
                [&folderRoot, &fileRoot, &ext](std::string& f) {
                  f = folderRoot + fileRoot + f + ext;
                });
  auto i = 0;
  for (auto const& fn : fns)
  {
    auto imgReader = vtkSmartPointer<vtkJPEGReader>::New();
    imgReader->SetFileName(fn.c_str());

    auto flip = vtkSmartPointer<vtkImageFlip>::New();
    flip->SetInputConnection(imgReader->GetOutputPort());
    flip->SetFilteredAxis(1); // flip y axis
    texture->SetInputConnection(i, flip->GetOutputPort(0));
    ++i;
  }
  return texture;
}

vtkSmartPointer<vtkPolyData> GetBoy()
{
  // The parametric surfaces make interesting sources.
  // Note: The normals are already defined for these surfaces.
  auto surface = vtkSmartPointer<vtkParametricBoy>::New();

  auto source = vtkSmartPointer<vtkParametricFunctionSource>::New();
  source->SetUResolution(51);
  source->SetVResolution(51);
  source->SetWResolution(51);
  source->SetParametricFunction(surface);

  source->Update();
  return source->GetOutput();
}

vtkSmartPointer<vtkPolyData> GetMobius()
{
  // The parametric surfaces make interesting sources.
  // Note: The normals are already defined for these surfaces.
  auto surface = vtkSmartPointer<vtkParametricMobius>::New();
  surface->SetMinimumV(-0.25);
  surface->SetMaximumV(0.25);

  auto source = vtkSmartPointer<vtkParametricFunctionSource>::New();
  source->SetUResolution(51);
  source->SetVResolution(51);
  source->SetWResolution(51);
  source->SetParametricFunction(surface);

  source->Update();

  auto transform = vtkSmartPointer<vtkTransform>::New();
  transform->RotateX(90.0);

  auto transformFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformFilter->SetInputConnection(source->GetOutputPort());
  transformFilter->SetTransform(transform);
  transformFilter->Update();

  return transformFilter->GetOutput();
}

vtkSmartPointer<vtkPolyData> GetTorus()
{
  // The parametric surfaces make interesting sources.
  // Note: The normals are already defined for these surfaces.
  auto surface = vtkSmartPointer<vtkParametricTorus>::New();

  auto source = vtkSmartPointer<vtkParametricFunctionSource>::New();
  source->SetUResolution(51);
  source->SetVResolution(51);
  source->SetWResolution(51);
  source->SetParametricFunction(surface);

  source->Update();

  auto transform = vtkSmartPointer<vtkTransform>::New();
  transform->RotateX(90.0);

  auto transformFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformFilter->SetInputConnection(source->GetOutputPort());
  transformFilter->SetTransform(transform);
  transformFilter->Update();

  return transformFilter->GetOutput();
}

vtkSmartPointer<vtkPolyData> GetSphere()
{
  // Use a sphere as the input object
  auto surface = vtkSmartPointer<vtkSphereSource>::New();
  surface->SetThetaResolution(32);
  surface->SetPhiResolution(32);

  auto source = vtkSmartPointer<vtkPolyDataNormals>::New();
  source->SetInputConnection(surface->GetOutputPort());
  source->Update();
  return source->GetOutput();
}

vtkSmartPointer<vtkPolyData> GetCube()
{
  // Use a cube as the input object
  auto surface = vtkSmartPointer<vtkCubeSource>::New();

  auto source = vtkSmartPointer<vtkPolyDataNormals>::New();
  source->SetInputConnection(surface->GetOutputPort());
  source->Update();
  return source->GetOutput();
}

vtkSmartPointer<vtkSliderWidget>
MakeSliderWidget(SliderProperties const& properties)
{
  auto slider = vtkSmartPointer<vtkSliderRepresentation2D>::New();

  slider->SetMinimumValue(properties.minimumValue);
  slider->SetMaximumValue(properties.maximumValue);
  slider->SetValue(properties.initialValue);
  slider->SetTitleText(properties.title.c_str());

  slider->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  slider->GetPoint1Coordinate()->SetValue(properties.p1[0], properties.p1[1]);
  slider->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  slider->GetPoint2Coordinate()->SetValue(properties.p2[0], properties.p2[1]);

  slider->SetTubeWidth(properties.tubeWidth);
  slider->SetSliderLength(properties.sliderLength);
  slider->SetTitleHeight(properties.titleHeight);
  slider->SetLabelHeight(properties.labelHeight);

  auto sliderWidget = vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidget->SetRepresentation(slider);

  return sliderWidget;
}

} // namespace
