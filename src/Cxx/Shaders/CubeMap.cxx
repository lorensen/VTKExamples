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

//----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  if (argc < 8)
  {
    std::cout << "Usage: " << argv[0]
              << " horse.ply skybox-px.jpg skybox-nx.jpg skybox-py.jpg "
                 "skybox-ny.jpg skybox-pz.jpg skybox-nz.jpg"
              << std::endl;
    return EXIT_FAILURE;
  }
  vtkSmartPointer<vtkNamedColors> colors =
      vtkSmartPointer<vtkNamedColors>::New();
  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  vtkSmartPointer<vtkTexture> texture =
      vtkSmartPointer<vtkTexture>::New();
  texture->CubeMapOn();

  vtkSmartPointer<vtkPLYReader> reader =
      vtkSmartPointer<vtkPLYReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkPolyDataNormals> norms =
      vtkSmartPointer<vtkPolyDataNormals>::New();
  norms->SetInputConnection(reader->GetOutputPort());

  for (int i = 0; i < 6; i++)
  {
    vtkSmartPointer<vtkJPEGReader> imgReader =
        vtkSmartPointer<vtkJPEGReader>::New();
    imgReader->SetFileName(argv[i + 2]);

    vtkSmartPointer<vtkImageFlip> flip =
        vtkSmartPointer<vtkImageFlip>::New();
    flip->SetInputConnection(imgReader->GetOutputPort());
    flip->SetFilteredAxis(1); // flip y axis
    texture->SetInputConnection(i, flip->GetOutputPort(0));
  }

  vtkSmartPointer<vtkOpenGLPolyDataMapper> mapper =
      vtkSmartPointer<vtkOpenGLPolyDataMapper>::New();
  mapper->SetInputConnection(norms->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
  renderer->AddActor(actor);
  actor->SetTexture(texture);
  actor->SetMapper(mapper);

  // Add new code in default VTK vertex shader
  mapper->AddShaderReplacement(
      vtkShader::Vertex,
      "//VTK::PositionVC::Dec",  // replace the normal block
      true,                      // before the standard replacements
      "//VTK::PositionVC::Dec\n" // we still want the default
      "out vec3 TexCoords;\n",
      false // only do it once
  );
  mapper->AddShaderReplacement(
      vtkShader::Vertex,
      "//VTK::PositionVC::Impl",  // replace the normal block
      true,                       // before the standard replacements
      "//VTK::PositionVC::Impl\n" // we still want the default
      "vec3 camPos = -MCVCMatrix[3].xyz * mat3(MCVCMatrix);\n"
      "TexCoords.xyz = reflect(vertexMC.xyz - camPos, normalize(normalMC));\n",
      false // only do it once
  );

  // Replace VTK fragment shader
  mapper->SetFragmentShaderCode(
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

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
      vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  renderWindow->GetInteractor()->SetInteractorStyle(style);

  interactor->Start();

  return EXIT_SUCCESS;
}
