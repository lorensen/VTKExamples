
#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkBMPReader.h>
#include <vtkCubeSource.h>
#include <vtkDataSet.h>
#include <vtkFloatArray.h>
#include <vtkImageFlip.h>
#include <vtkImageReader2Factory.h>
#include <vtkJPEGReader.h>
#include <vtkLinearSubdivisionFilter.h>
#include <vtkNamedColors.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkPNGReader.h>
#include <vtkPNMReader.h>
#include <vtkParametricBoy.h>
#include <vtkParametricFunctionSource.h>
#include <vtkParametricMobius.h>
#include <vtkParametricTorus.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataTangents.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSkybox.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkSliderWidget.h>
#include <vtkSmartPointer.h>
#include <vtkTIFFReader.h>
#include <vtkTexture.h>
#include <vtkTexturedSphereSource.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTriangleFilter.h>
#include <vtkVersion.h>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

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

vtkSmartPointer<vtkPolyData> GetBoy();
vtkSmartPointer<vtkPolyData> GetMobius();
vtkSmartPointer<vtkPolyData> GetSphere();
vtkSmartPointer<vtkPolyData> GetTorus();
vtkSmartPointer<vtkPolyData> GetCube();

/**
 * Generate u, v texture coordinates on a parametric surface.
 *
 * @param uResolution: u resolution
 * @param vResolution: v resolution
 * @param pd: The polydata representing the surface.
 *
 * @return The polydata with the texture coordinates added.
 */
vtkSmartPointer<vtkPolyData> UVTcoords(const float& uResolution,
                                       const float& vResolution,
                                       vtkSmartPointer<vtkPolyData> pd);

/**
 * Read six images forming a cubemap.
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

/**
 * Read an image and convert it to a texture.
 *
 * @param path: The image path.
 *
 * @return The texture.
 */
vtkSmartPointer<vtkTexture> GetTexture(std::string path);

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

class SliderCallbackOcclusionStrength : public vtkCommand
{
public:
  static SliderCallbackOcclusionStrength* New()
  {
    return new SliderCallbackOcclusionStrength;
  }
  virtual void Execute(vtkObject* caller, unsigned long, void*)
  {
    vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D*>(
                       sliderWidget->GetRepresentation())
                       ->GetValue();
    this->property->SetOcclusionStrength(value);
  }
  SliderCallbackOcclusionStrength() : property(nullptr)
  {
  }
  vtkProperty* property;
};

class SliderCallbackNormalScale : public vtkCommand
{
public:
  static SliderCallbackNormalScale* New()
  {
    return new SliderCallbackNormalScale;
  }
  virtual void Execute(vtkObject* caller, unsigned long, void*)
  {
    vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D*>(
                       sliderWidget->GetRepresentation())
                       ->GetValue();
    this->property->SetNormalScale(value);
  }
  SliderCallbackNormalScale() : property(nullptr)
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

  std::array<double, 2> p1{0.2, 0.1};
  std::array<double, 2> p2{0.8, 0.1};

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

  std::string filePath{""};
  if (argc < 6)
  {
    std::cout << ShowUsage(argv[0]) << std::endl;
    return EXIT_FAILURE;
  }

  // Get the cube map
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

  // Get the textures
  auto material = GetTexture(argv[2]);
  auto albedo = GetTexture(argv[3]);
  albedo->UseSRGBColorSpaceOn();
  auto normal = GetTexture(argv[4]);
  auto emissive = GetTexture(argv[5]);
  emissive->UseSRGBColorSpaceOn();

  // Get the surface
  std::string desiredSurface = "boy";
  if (argc > 6)
  {
    desiredSurface = argv[6];
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
  // source->Print(std::cout);
  // source->PrintSelf(std::cout, vtkIndent(2));

  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  std::array<unsigned char, 4> col{{26, 51, 102, 255}};
  colors->SetColor("BkgColor", col.data());
  // VTK blue
  std::array<unsigned char, 4> col1{{6, 79, 141, 255}};
  colors->SetColor("VTKBlue", col1.data());
  // Let's make a complementary colour to VTKBlue
  std::transform(col1.begin(), std::prev(col1.end()), col1.begin(),
                 [](unsigned char c) { return 255 - c; });
  colors->SetColor("VTKBlueComp", col1.data());

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Lets use a rough metallic surface
  auto metallicCoefficient = 1.0;
  auto roughnessCoefficient = 0.8;
  // Other parameters
  auto occlusionStrength = 10.0;
  auto normalScale = 10.0;
  // Make VTK silvery in appearance
  auto emissiveCol = colors->GetColor3d("VTKBlueComp").GetData();
  std::array<double, 3> emissiveFactor{emissiveCol[0], emissiveCol[1],
                                       emissiveCol[2]};
  // std::array<double, 3> emissiveFactor{1.0, 1.0, 1.0};
  //   std::cout << emissiveFactor[0] << ", " <<  emissiveFactor[1] << ", " <<
  //   emissiveFactor[2] << std::endl;

  auto slwP = SliderProperties();
  slwP.initialValue = metallicCoefficient;
  slwP.title = "Metallicity";

  auto sliderWidgetMetallic = MakeSliderWidget(slwP);
  sliderWidgetMetallic->SetInteractor(interactor);
  sliderWidgetMetallic->SetAnimationModeToAnimate();
  sliderWidgetMetallic->EnabledOn();

  slwP.initialValue = roughnessCoefficient;
  slwP.title = "Roughness";
  slwP.p1[0] = 0.2;
  slwP.p1[1] = 0.9;
  slwP.p2[0] = 0.8;
  slwP.p2[1] = 0.9;

  auto sliderWidgetRoughness = MakeSliderWidget(slwP);
  sliderWidgetRoughness->SetInteractor(interactor);
  sliderWidgetRoughness->SetAnimationModeToAnimate();
  sliderWidgetRoughness->EnabledOn();

  slwP.initialValue = occlusionStrength;
  slwP.title = "Occlusion";
  slwP.p1[0] = 0.1;
  slwP.p1[1] = 0.1;
  slwP.p2[0] = 0.1;
  slwP.p2[1] = 0.9;

  auto sliderWidgetOcclusionStrength = MakeSliderWidget(slwP);
  sliderWidgetOcclusionStrength->SetInteractor(interactor);
  sliderWidgetOcclusionStrength->SetAnimationModeToAnimate();
  sliderWidgetOcclusionStrength->EnabledOn();

  slwP.initialValue = normalScale;
  slwP.title = "Normal";
  slwP.p1[0] = 0.85;
  slwP.p1[1] = 0.1;
  slwP.p2[0] = 0.85;
  slwP.p2[1] = 0.9;

  auto sliderWidgetNormal = MakeSliderWidget(slwP);
  sliderWidgetNormal->SetInteractor(interactor);
  sliderWidgetNormal->SetAnimationModeToAnimate();
  sliderWidgetNormal->EnabledOn();

  // Build the pipeline
  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(source);

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  actor->GetProperty()->SetInterpolationToPBR();

  // configure the basic properties
  actor->GetProperty()->SetColor(colors->GetColor3d("White").GetData());
  actor->GetProperty()->SetMetallic(metallicCoefficient);
  actor->GetProperty()->SetRoughness(roughnessCoefficient);

  // configure textures (needs tcoords on the mesh)
  actor->GetProperty()->SetBaseColorTexture(albedo);
  actor->GetProperty()->SetORMTexture(material);
  actor->GetProperty()->SetOcclusionStrength(occlusionStrength);

  actor->GetProperty()->SetEmissiveTexture(emissive);
  actor->GetProperty()->SetEmissiveFactor(emissiveFactor.data());

  // needs tcoords, normals and tangents on the mesh
  actor->GetProperty()->SetNormalTexture(normal);
  actor->GetProperty()->SetNormalScale(normalScale);

  renderer->UseImageBasedLightingOn();
  renderer->SetEnvironmentCubeMap(cubemap);
  renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
  renderer->AddActor(actor);

  // Comment out if you don't want a skybox
  auto skyboxActor = vtkSmartPointer<vtkSkybox>::New();
  skyboxActor->SetTexture(skybox);
  renderer->AddActor(skyboxActor);

  // Create the slider callbacks to manipulate metallicity, roughness,
  // occlusion strength and normal scaling
  auto callbackMetallic = vtkSmartPointer<SliderCallbackMetallic>::New();
  callbackMetallic->property = actor->GetProperty();
  auto callbackRoughness = vtkSmartPointer<SliderCallbackRoughness>::New();
  callbackRoughness->property = actor->GetProperty();
  auto callbackOcclusionStrength =
      vtkSmartPointer<SliderCallbackOcclusionStrength>::New();
  callbackOcclusionStrength->property = actor->GetProperty();
  auto callbackNormalScale = vtkSmartPointer<SliderCallbackNormalScale>::New();
  callbackNormalScale->property = actor->GetProperty();

  sliderWidgetMetallic->AddObserver(vtkCommand::InteractionEvent,
                                    callbackMetallic);
  sliderWidgetRoughness->AddObserver(vtkCommand::InteractionEvent,
                                     callbackRoughness);
  sliderWidgetOcclusionStrength->AddObserver(vtkCommand::InteractionEvent,
                                             callbackOcclusionStrength);
  sliderWidgetNormal->AddObserver(vtkCommand::InteractionEvent,
                                  callbackNormalScale);

  renderWindow->SetSize(640, 480);
  renderWindow->Render();
  renderWindow->SetWindowName("PhysicallyBasedRendering");

  auto axes = vtkSmartPointer<vtkAxesActor>::New();

  auto widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  double rgba[4]{0.0, 0.0, 0.0, 0.0};
  colors->GetColor("Carrot", rgba);
  widget->SetOutlineColor(rgba[0], rgba[1], rgba[2]);
  widget->SetOrientationMarker(axes);
  widget->SetInteractor(interactor);
  widget->SetViewport(0.0, 0.0, 0.2, 0.2);
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
  os << "\nusage: " << fn
     << " path material_fn albedo_fn normal_fn emissive_fn [surface]\n\n"
     << "Demonstrates physically based rendering, image based lighting, "
        ", texturing and a skybox.\n\n"
     << "positional arguments:\n"
     << "  path         The path to the cubemap files e.g. skyboxes/skybox2/\n"
     << "  material_fn  The path to the material texture file e.g. vtk_Material.png\n"
     << "  albedo_fn    The path to the albedo (base colour) texture file e.g. vtk_Base_Color.png\n"
     << "  normal_fn    The path to the normal texture file e.g. vtk_Normal.png\n"
     << "  emissive_fn  The path to the emissive texture file e.g. vtk_dark_bkg.png\n"
     << "  surface      The surface to use. Boy's surface is the default.\n\n"
     << "Physically based rendering sets color, metallicity and roughness of "
        "the object.\n"
     << "Image based lighting uses a cubemap texture to specify the "
        "environment.\n"
     << "Texturing is used to generate lighting effects.\n"
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

vtkSmartPointer<vtkPolyData> GetBoy()
{
  auto uResolution = 51;
  auto vResolution = 51;
  auto surface = vtkSmartPointer<vtkParametricBoy>::New();

  auto source = vtkSmartPointer<vtkParametricFunctionSource>::New();
  source->SetUResolution(uResolution);
  source->SetVResolution(vResolution);
  source->SetParametricFunction(surface);
  source->Update();
  // Build the tcoords
  auto pd = UVTcoords(uResolution, vResolution, source->GetOutput());
  // Now the tangents
  auto tangents = vtkSmartPointer<vtkPolyDataTangents>::New();
  tangents->SetInputData(pd);
  tangents->Update();
  return tangents->GetOutput();
}

vtkSmartPointer<vtkPolyData> GetMobius()
{
  auto uResolution = 51;
  auto vResolution = 51;
  auto surface = vtkSmartPointer<vtkParametricMobius>::New();
  surface->SetMinimumV(-0.25);
  surface->SetMaximumV(0.25);

  auto source = vtkSmartPointer<vtkParametricFunctionSource>::New();
  source->SetUResolution(uResolution);
  source->SetVResolution(vResolution);
  source->SetParametricFunction(surface);
  source->Update();
  // Build the tcoords
  auto pd = UVTcoords(uResolution, vResolution, source->GetOutput());
  // Now the tangents
  auto tangents = vtkSmartPointer<vtkPolyDataTangents>::New();
  tangents->SetInputData(pd);
  tangents->Update();

  auto transform = vtkSmartPointer<vtkTransform>::New();
  transform->RotateX(90.0);
  auto transformFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformFilter->SetInputConnection(tangents->GetOutputPort());
  transformFilter->SetTransform(transform);
  transformFilter->Update();

  return transformFilter->GetOutput();
}

vtkSmartPointer<vtkPolyData> GetTorus()
{
  auto uResolution = 51;
  auto vResolution = 51;
  auto surface = vtkSmartPointer<vtkParametricTorus>::New();

  auto source = vtkSmartPointer<vtkParametricFunctionSource>::New();
  source->SetUResolution(uResolution);
  source->SetVResolution(vResolution);
  source->SetParametricFunction(surface);

  source->Update();
  // Build the tcoords
  auto pd = UVTcoords(uResolution, vResolution, source->GetOutput());
  // Now the tangents
  auto tangents = vtkSmartPointer<vtkPolyDataTangents>::New();
  tangents->SetInputData(pd);
  tangents->Update();

  auto transform = vtkSmartPointer<vtkTransform>::New();
  transform->RotateX(90.0);
  auto transformFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformFilter->SetInputConnection(tangents->GetOutputPort());
  transformFilter->SetTransform(transform);
  transformFilter->Update();

  return transformFilter->GetOutput();
}

vtkSmartPointer<vtkPolyData> GetSphere()
{
  auto thetaResolution = 32;
  auto phiResolution = 32;
  auto surface = vtkSmartPointer<vtkTexturedSphereSource>::New();
  surface->SetThetaResolution(thetaResolution);
  surface->SetPhiResolution(phiResolution);

  // Now the tangents
  auto tangents = vtkSmartPointer<vtkPolyDataTangents>::New();
  tangents->SetInputConnection(surface->GetOutputPort());
  tangents->Update();
  return tangents->GetOutput();
}

vtkSmartPointer<vtkPolyData> GetCube()
{
  auto surface = vtkSmartPointer<vtkCubeSource>::New();

  // Triangulate
  auto triangulation = vtkSmartPointer<vtkTriangleFilter>::New();
  triangulation->SetInputConnection(surface->GetOutputPort());
  // Subdivide the triangles
  auto subdivide = vtkSmartPointer<vtkLinearSubdivisionFilter>::New();
  subdivide->SetInputConnection(triangulation->GetOutputPort());
  subdivide->SetNumberOfSubdivisions(3);
  // Now the tangents
  auto tangents = vtkSmartPointer<vtkPolyDataTangents>::New();
  tangents->SetInputConnection(subdivide->GetOutputPort());
  tangents->Update();
  return tangents->GetOutput();
}

vtkSmartPointer<vtkPolyData> UVTcoords(const float& uResolution,
                                       const float& vResolution,
                                       vtkSmartPointer<vtkPolyData> pd)
{
  float u0 = 1.0;
  float v0 = 0.0;
  float du = 1.0 / (uResolution - 1);
  float dv = 1.0 / (vResolution - 1);
  float u = u0;
  float v = v0;
  vtkIdType numPts = pd->GetNumberOfPoints();
  auto tCoords = vtkSmartPointer<vtkFloatArray>::New();
  tCoords->SetNumberOfComponents(2);
  tCoords->SetNumberOfTuples(numPts);
  tCoords->SetName("Texture Coordinates");
  vtkIdType ptId = 0;
  for (auto i = 0; i < uResolution; ++i)
  {
    for (auto j = 0; j < vResolution; ++j)
    {
      float tc[2]{u, v};
      tCoords->SetTuple(ptId, tc);
      v += dv;
      if (v > 1.0)
      {
        v = 0;
      }
      ptId++;
    }
    u -= du;
    if (u < 0.0)
    {
      u = 1;
    }
  }
  pd->GetPointData()->SetTCoords(tCoords);
  return pd;
}

vtkSmartPointer<vtkTexture> GetTexture(std::string path)
{
  // Read the image which will be the texture
  std::string extension;
  if (path.find_last_of(".") != std::string::npos)
  {
    extension = path.substr(path.find_last_of("."));
  }
  // Make the extension lowercase
  std::transform(extension.begin(), extension.end(), extension.begin(),
                 ::tolower);
  std::vector<std::string> validExtensions{".jpg", ".png", ".bmp", ".tiff",
                                           ".pnm", ".pgm", ".ppm"};
  auto texture = vtkSmartPointer<vtkTexture>::New();
  if (std::find(validExtensions.begin(), validExtensions.end(), extension) ==
      validExtensions.end())
  {
    std::cout << "Unable to read the texture file:" << path << std::endl;
    return texture;
  }
  // Read the images
  auto readerFactory = vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> imgReader;
  imgReader.TakeReference(readerFactory->CreateImageReader2(path.c_str()));
  imgReader->SetFileName(path.c_str());

  texture->SetInputConnection(imgReader->GetOutputPort());
  texture->Update();

  return texture;
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
