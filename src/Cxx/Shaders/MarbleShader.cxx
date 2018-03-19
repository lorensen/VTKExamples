#include <vtkSmartPointer.h>

#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkShaderProgram.h>
#include <vtkActor.h>
#include <vtkOpenGLPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTriangleMeshPointNormals.h>
#include <vtkTriangleFilter.h>
#include <vtkNamedColors.h>
#include <vtkRenderWindowInteractor.h>
#include <vtksys/SystemTools.hxx>
#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>

#include <fstream>
#include <sstream>
namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " PerlnNoise.glsl " << "[polydataFile]" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkPolyData> polyData =
    ReadPolyData(argc > 2 ? argv[2] : "");

  std::ifstream shaderFile(argv[1]);
  std::ostringstream shaderCode;
  shaderCode << shaderFile.rdbuf();

// Create a transform to rescale model
  double center[3];
  polyData->GetCenter(center);
  double bounds[6];
  polyData->GetBounds(bounds);
  double maxBound = std::max(std::max(bounds[1] - bounds[0],  bounds[3] - bounds[2]), bounds[5] - bounds[4]);

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

  vtkSmartPointer<vtkRenderWindowInteractor>  interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Rescale polydata to [-1,1]
  vtkSmartPointer<vtkTransform> userTransform =
    vtkSmartPointer<vtkTransform>::New();
  userTransform->Translate(-center[0], -center[1], -center[2]);
  userTransform->Scale(1.0/maxBound, 1.0/maxBound, 1.0/maxBound);
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
  actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("ivoryblack").GetData());
  actor->GetProperty()->SetSpecular(.5);
  actor->GetProperty()->SetSpecularPower(5);

  // Modify the vertex shader to pass the position of the vertex
  mapper->AddShaderReplacement(
    vtkShader::Vertex,
    "//VTK::Normal::Dec", // replace the normal block
    true, // before the standard replacements
    "//VTK::Normal::Dec\n" // we still want the default
    "  out vec4 myVertexMC;\n"
    ,
    false // only do it once
    );
  mapper->AddShaderReplacement(
    vtkShader::Vertex,
    "//VTK::Normal::Impl", // replace the normal block
    true, // before the standard replacements
    "//VTK::Normal::Impl\n" // we still want the default
    "  myVertexMC = vertexMC;\n"
    ,
    false // only do it once
    );

  // Add the code to generate noise
  // These functions need to be defined outside of main. Use the System::Dec
  // to declare and implement
  mapper->AddShaderReplacement(
    vtkShader::Fragment,
    "//VTK::System::Dec", 
    false, // before the standard replacements
    shaderCode.str(),
    false // only do it once
    );
  mapper->AddShaderReplacement(
    vtkShader::Fragment,  // in the fragment shader
    "//VTK::Normal::Dec", // replace the normal block
    true, // before the standard replacements
    "//VTK::Normal::Dec\n" // we still want the default
    "  varying vec4 myVertexMC;\n"
    ,
    false // only do it once
    );

  mapper->AddShaderReplacement(
    vtkShader::Fragment,  // in the fragment shader
    "//VTK::Light::Impl", // replace the light block
    false, // after the standard replacements
    "//VTK::Light::Impl\n" // we still want the default calc
    "  float veinfreq = 10.0;\n"
    "  float veinlevels = 2.0;\n"
    "  float warpFreq = 1;\n"
    "  float warping = .5;\n"
    "  float sharpness = 8.0;\n"
    "  vec3 veincolor = vec3(1.0, 1.0, 1.0);\n"
    "\n"
    "#define pnoise(x) ((noise(x) + 1.0) / 2.0)\n"
    "#define snoise(x) (2.0 * pnoise(x) - 1.0)\n"
    "  vec3 Ct;\n"
    "  float i, j;\n"
    "  float turb, freq;\n"
    "  float turbsum;\n"
    "  /* perturb the lookup */\n"
    "  freq = 1.0;\n"
    "  vec4 offset = vec4(0.0,0.0,0.0,0.0);\n"
    "  vec4 noisyPoint;\n"
    "  vec4 myLocalVertexMC = myVertexMC;\n"
    "\n"
    "    for (i = 0.0;  i < 6.0;  i += 1.0) {\n"
    "      noisyPoint[0] = pnoise(warpFreq * freq * myLocalVertexMC);\n"
    "      noisyPoint[1] = pnoise(warpFreq * freq * myLocalVertexMC);\n"
    "      noisyPoint[2] = pnoise(warpFreq * freq * myLocalVertexMC);\n"
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
"    for (i = 0.0;  i < veinlevels;  i += 1.0) {\n"
"      turb = abs (snoise (myLocalVertexMC));\n"
"      turb = pow (smoothstep (0.8, 1.0, 1.0 - turb), sharpness) / freq;\n"
"      turbsum += (1.0-turbsum) * turb;\n"
"      freq *= 3.0;\n"
"      myLocalVertexMC *= 3.0;\n"
"    }\n"
"\n"
"    Ct = mix (diffuseColor, veincolor, turbsum);\n"
"\n"
    "  fragOutput0.rgb = opacity * (ambientColor + Ct + specular);\n"
    "  fragOutput0.a = opacity;\n"    
    ,
    false // only do it once
    );
  renderWindow->Render();
  renderer->GetActiveCamera()->SetPosition(-.3, 0, .08);
  renderer->GetActiveCamera()->SetFocalPoint(0,0,0);
  renderer->GetActiveCamera()->SetViewUp(.26, 0.0, .96);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(1.5);
  renderWindow->Render();
  interactor->Start();

  transform->GetOutput()->GetBounds(bounds);
  std::cout << "Range: "
            << " x " << bounds[1] - bounds[0]
            << " y " << bounds[3] - bounds[2]
            << " y " << bounds[5] - bounds[4]
            << std::endl;
  return EXIT_SUCCESS;
}

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = vtksys::SystemTools::GetFilenameExtension(std::string(fileName));
  if (extension == ".ply")
  {
    vtkSmartPointer<vtkPLYReader> reader =
      vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    vtkSmartPointer<vtkOBJReader> reader =
      vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    vtkSmartPointer<vtkSTLReader> reader =
      vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    vtkSmartPointer<vtkPolyDataReader> reader =
      vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    vtkSmartPointer<vtkBYUReader> reader =
      vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName (fileName);
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
}
