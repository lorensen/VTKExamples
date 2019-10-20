// Inspired by the VTK test Rendering/OpenGL2/Testing/Cxx/TesCubeMap.cxx

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkImageFlip.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkJPEGReader.h>
#include <vtkNamedColors.h>
#include <vtkOpenGLPolyDataMapper.h>
#include <vtkOpenGLRenderWindow.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkShaderProgram.h>
#include <vtkSmartPointer.h>
#include <vtkTexture.h>
#include <vtkVersion.h>

#if VTK_VERSION_NUMBER >= 89000000000ULL
#define USE_SHADER_PROPERTIES 1
#include <vtkShaderProperty.h>
#endif

namespace {
/**
 * Read the cube map.
 *
 * @param folderPath: The folder where the cube maps are stored.
 * @param fileRoot: The root of the individual cube map file names.
 * @param ext: The extension of the cube map files.
 * @param key: The key to data used to build the full file name.
 *
 * @return The cubemap texture.
 */
vtkSmartPointer<vtkTexture> ReadCubeMap(std::string const& folderPath,
                                        std::string const& fileRoot,
                                        std::string const& ext, int const& key);

} // namespace

//----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0]
              << " horse.ply path_to_cubemap_files"
              << std::endl;
    return EXIT_FAILURE;
  }
  auto colors = vtkSmartPointer<vtkNamedColors>::New();
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  auto reader = vtkSmartPointer<vtkPLYReader>::New();
  reader->SetFileName(argv[1]);

  auto norms = vtkSmartPointer<vtkPolyDataNormals>::New();
  norms->SetInputConnection(reader->GetOutputPort());

  auto texture = ReadCubeMap(argv[2], "/skybox", ".jpg", 2);

  auto mapper = vtkSmartPointer<vtkOpenGLPolyDataMapper>::New();
  mapper->SetInputConnection(norms->GetOutputPort());

  auto actor = vtkSmartPointer<vtkActor>::New();
  renderer->AddActor(actor);
  actor->SetTexture(texture);
  actor->SetMapper(mapper);

  // Add new code in default VTK vertex shader
#if USE_SHADER_PROPERTIES
  vtkShaderProperty* sp = actor->GetShaderProperty();
  sp->AddVertexShaderReplacement(
#else
  mapper->AddShaderReplacement(
      vtkShader::Vertex,
#endif
      "//VTK::PositionVC::Dec",  // replace the normal block
      true,                      // before the standard replacements
      "//VTK::PositionVC::Dec\n" // we still want the default
      "out vec3 TexCoords;\n",
      false // only do it once
  );
#if USE_SHADER_PROPERTIES
  sp->AddVertexShaderReplacement(
#else
  mapper->AddShaderReplacement(
      vtkShader::Vertex,
#endif
      "//VTK::PositionVC::Impl",  // replace the normal block
      true,                       // before the standard replacements
      "//VTK::PositionVC::Impl\n" // we still want the default
      "vec3 camPos = -MCVCMatrix[3].xyz * mat3(MCVCMatrix);\n"
      "TexCoords.xyz = reflect(vertexMC.xyz - camPos, normalize(normalMC));\n",
      false // only do it once
  );

  // Replace VTK fragment shader
#if USE_SHADER_PROPERTIES
  sp->SetFragmentShaderCode(
#else
  mapper->SetFragmentShaderCode(
#endif
      "//VTK::System::Dec\n" // always start with this line
      "//VTK::Output::Dec\n" // always have this line in your FS
      "in vec3 TexCoords;\n"
      "uniform samplerCube texture_0;\n"
      "void main () {\n"
      "  gl_FragData[0] = texture(texture_0, TexCoords);\n"
      "}\n");

  renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  renderer->GetActiveCamera()->SetPosition(-.4, .2, .15);
  renderer->GetActiveCamera()->SetViewUp(.3, -.1, .9);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(1.4);
  renderWindow->Render();
  renderWindow->SetWindowName("CubeMap");
  renderWindow->Render();

  auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  renderWindow->GetInteractor()->SetInteractorStyle(style);

  interactor->Start();

  return EXIT_SUCCESS;
}

namespace {

vtkSmartPointer<vtkTexture> ReadCubeMap(std::string const& folderPath,
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
                [&folderPath, &fileRoot, &ext](std::string& f) {
                  f = folderPath + fileRoot + f + ext;
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

} // namespace
