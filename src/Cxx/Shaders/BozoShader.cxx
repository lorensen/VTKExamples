#include <vtkSmartPointer.h>

#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkShaderProgram.h>
#include <vtkActor.h>
#include <vtkOpenGLPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkPolyDataNormals.h>
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

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData =
    ReadPolyData(argc > 1 ? argv[1] : "");

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

  vtkSmartPointer<vtkTriangleFilter> triangles =
    vtkSmartPointer<vtkTriangleFilter>::New();
  triangles->SetInputData(polyData);

  vtkSmartPointer<vtkTriangleMeshPointNormals> norms =
    vtkSmartPointer<vtkTriangleMeshPointNormals>::New();
  norms->SetInputConnection(triangles->GetOutputPort());

  mapper->SetInputConnection(norms->GetOutputPort());
  actor->SetMapper(mapper);
  actor->GetProperty()->SetAmbientColor(0.2, 0.2, 1.0);
  actor->GetProperty()->SetDiffuseColor(1.0, 1.0, 1.0);
  actor->GetProperty()->SetSpecularColor(1.0, 1.0, 1.0);
  actor->GetProperty()->SetSpecular(0.5);
  actor->GetProperty()->SetDiffuse(0.7);
  actor->GetProperty()->SetAmbient(0.1);
  actor->GetProperty()->SetSpecularPower(100.0);
  actor->GetProperty()->SetOpacity(1.0);

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
    "//VTK::System::Dec\n" // we still want the default
    "//Classic Perlin 3D Noise \n" // add functions for noise calculation
    "//by Stefan Gustavson\n"
    "//\n"
    "    vec4 permute(vec4 x){return mod(((x*34.0)+1.0)*x, 289.0);}\n"
    "    vec4 taylorInvSqrt(vec4 r){return 1.79284291400159 - 0.85373472095314 * r;}\n"
    "    vec4 fade(vec4 t) {return t*t*t*(t*(t*6.0-15.0)+10.0);}\n"
    "\n"
    "    float cnoise(vec4 P){\n"
    "      vec4 Pi0 = floor(P); // Integer part for indexing\n"
    "      vec4 Pi1 = Pi0 + 1.0; // Integer part + 1\n"
    "      Pi0 = mod(Pi0, 289.0);\n"
    "      Pi1 = mod(Pi1, 289.0);\n"
    "      vec4 Pf0 = fract(P); // Fractional part for interpolation\n"
    "      vec4 Pf1 = Pf0 - 1.0; // Fractional part - 1.0\n"
    "      vec4 ix = vec4(Pi0.x, Pi1.x, Pi0.x, Pi1.x);\n"
    "      vec4 iy = vec4(Pi0.yy, Pi1.yy);\n"
    "      vec4 iz0 = vec4(Pi0.zzzz);\n"
    "      vec4 iz1 = vec4(Pi1.zzzz);\n"
    "      vec4 iw0 = vec4(Pi0.wwww);\n"
    "      vec4 iw1 = vec4(Pi1.wwww);\n"
    "\n"
    "      vec4 ixy = permute(permute(ix) + iy);\n"
    "      vec4 ixy0 = permute(ixy + iz0);\n"
    "      vec4 ixy1 = permute(ixy + iz1);\n"
    "      vec4 ixy00 = permute(ixy0 + iw0);\n"
    "      vec4 ixy01 = permute(ixy0 + iw1);\n"
    "      vec4 ixy10 = permute(ixy1 + iw0);\n"
    "      vec4 ixy11 = permute(ixy1 + iw1);\n"
    "\n"
    "      vec4 gx00 = ixy00 / 7.0;\n"
    "      vec4 gy00 = floor(gx00) / 7.0;\n"
    "      vec4 gz00 = floor(gy00) / 6.0;\n"
    "      gx00 = fract(gx00) - 0.5;\n"
    "      gy00 = fract(gy00) - 0.5;\n"
    "      gz00 = fract(gz00) - 0.5;\n"
    "      vec4 gw00 = vec4(0.75) - abs(gx00) - abs(gy00) - abs(gz00);\n"
    "      vec4 sw00 = step(gw00, vec4(0.0));\n"
    "      gx00 -= sw00 * (step(0.0, gx00) - 0.5);\n"
    "      gy00 -= sw00 * (step(0.0, gy00) - 0.5);\n"
    "\n"
    "      vec4 gx01 = ixy01 / 7.0;\n"
    "      vec4 gy01 = floor(gx01) / 7.0;\n"
    "      vec4 gz01 = floor(gy01) / 6.0;\n"
    "      gx01 = fract(gx01) - 0.5;\n"
    "      gy01 = fract(gy01) - 0.5;\n"
    "      gz01 = fract(gz01) - 0.5;\n"
    "      vec4 gw01 = vec4(0.75) - abs(gx01) - abs(gy01) - abs(gz01);\n"
    "      vec4 sw01 = step(gw01, vec4(0.0));\n"
    "      gx01 -= sw01 * (step(0.0, gx01) - 0.5);\n"
    "      gy01 -= sw01 * (step(0.0, gy01) - 0.5);\n"
    "\n"
    "      vec4 gx10 = ixy10 / 7.0;\n"
    "      vec4 gy10 = floor(gx10) / 7.0;\n"
    "      vec4 gz10 = floor(gy10) / 6.0;\n"
    "      gx10 = fract(gx10) - 0.5;\n"
    "      gy10 = fract(gy10) - 0.5;\n"
    "      gz10 = fract(gz10) - 0.5;\n"
    "      vec4 gw10 = vec4(0.75) - abs(gx10) - abs(gy10) - abs(gz10);\n"
    "      vec4 sw10 = step(gw10, vec4(0.0));\n"
    "      gx10 -= sw10 * (step(0.0, gx10) - 0.5);\n"
    "      gy10 -= sw10 * (step(0.0, gy10) - 0.5);\n"
    "\n"
    "      vec4 gx11 = ixy11 / 7.0;\n"
    "      vec4 gy11 = floor(gx11) / 7.0;\n"
    "      vec4 gz11 = floor(gy11) / 6.0;\n"
    "      gx11 = fract(gx11) - 0.5;\n"
    "      gy11 = fract(gy11) - 0.5;\n"
    "      gz11 = fract(gz11) - 0.5;\n"
    "      vec4 gw11 = vec4(0.75) - abs(gx11) - abs(gy11) - abs(gz11);\n"
    "      vec4 sw11 = step(gw11, vec4(0.0));\n"
    "      gx11 -= sw11 * (step(0.0, gx11) - 0.5);\n"
    "      gy11 -= sw11 * (step(0.0, gy11) - 0.5);\n"
    "\n"
    "      vec4 g0000 = vec4(gx00.x,gy00.x,gz00.x,gw00.x);\n"
    "      vec4 g1000 = vec4(gx00.y,gy00.y,gz00.y,gw00.y);\n"
    "      vec4 g0100 = vec4(gx00.z,gy00.z,gz00.z,gw00.z);\n"
    "      vec4 g1100 = vec4(gx00.w,gy00.w,gz00.w,gw00.w);\n"
    "      vec4 g0010 = vec4(gx10.x,gy10.x,gz10.x,gw10.x);\n"
    "      vec4 g1010 = vec4(gx10.y,gy10.y,gz10.y,gw10.y);\n"
    "      vec4 g0110 = vec4(gx10.z,gy10.z,gz10.z,gw10.z);\n"
    "      vec4 g1110 = vec4(gx10.w,gy10.w,gz10.w,gw10.w);\n"
    "      vec4 g0001 = vec4(gx01.x,gy01.x,gz01.x,gw01.x);\n"
    "      vec4 g1001 = vec4(gx01.y,gy01.y,gz01.y,gw01.y);\n"
    "      vec4 g0101 = vec4(gx01.z,gy01.z,gz01.z,gw01.z);\n"
    "      vec4 g1101 = vec4(gx01.w,gy01.w,gz01.w,gw01.w);\n"
    "      vec4 g0011 = vec4(gx11.x,gy11.x,gz11.x,gw11.x);\n"
    "      vec4 g1011 = vec4(gx11.y,gy11.y,gz11.y,gw11.y);\n"
    "      vec4 g0111 = vec4(gx11.z,gy11.z,gz11.z,gw11.z);\n"
    "      vec4 g1111 = vec4(gx11.w,gy11.w,gz11.w,gw11.w);\n"
    "\n"
    "      vec4 norm00 = taylorInvSqrt(vec4(dot(g0000, g0000), dot(g0100, g0100), dot(g1000, g1000), dot(g1100, g1100)));\n"
    "      g0000 *= norm00.x;\n"
    "      g0100 *= norm00.y;\n"
    "      g1000 *= norm00.z;\n"
    "      g1100 *= norm00.w;\n"
    "\n"
    "      vec4 norm01 = taylorInvSqrt(vec4(dot(g0001, g0001), dot(g0101, g0101), dot(g1001, g1001), dot(g1101, g1101)));\n"
    "      g0001 *= norm01.x;\n"
    "      g0101 *= norm01.y;\n"
    "      g1001 *= norm01.z;\n"
    "      g1101 *= norm01.w;\n"
    "\n"
    "      vec4 norm10 = taylorInvSqrt(vec4(dot(g0010, g0010), dot(g0110, g0110), dot(g1010, g1010), dot(g1110, g1110)));\n"
    "      g0010 *= norm10.x;\n"
    "      g0110 *= norm10.y;\n"
    "      g1010 *= norm10.z;\n"
    "      g1110 *= norm10.w;\n"
    "\n"
    "      vec4 norm11 = taylorInvSqrt(vec4(dot(g0011, g0011), dot(g0111, g0111), dot(g1011, g1011), dot(g1111, g1111)));\n"
    "      g0011 *= norm11.x;\n"
    "      g0111 *= norm11.y;\n"
    "      g1011 *= norm11.z;\n"
    "      g1111 *= norm11.w;\n"
    "\n"
    "      float n0000 = dot(g0000, Pf0);\n"
    "      float n1000 = dot(g1000, vec4(Pf1.x, Pf0.yzw));\n"
    "      float n0100 = dot(g0100, vec4(Pf0.x, Pf1.y, Pf0.zw));\n"
    "      float n1100 = dot(g1100, vec4(Pf1.xy, Pf0.zw));\n"
    "      float n0010 = dot(g0010, vec4(Pf0.xy, Pf1.z, Pf0.w));\n"
    "      float n1010 = dot(g1010, vec4(Pf1.x, Pf0.y, Pf1.z, Pf0.w));\n"
    "      float n0110 = dot(g0110, vec4(Pf0.x, Pf1.yz, Pf0.w));\n"
    "      float n1110 = dot(g1110, vec4(Pf1.xyz, Pf0.w));\n"
    "      float n0001 = dot(g0001, vec4(Pf0.xyz, Pf1.w));\n"
    "      float n1001 = dot(g1001, vec4(Pf1.x, Pf0.yz, Pf1.w));\n"
    "      float n0101 = dot(g0101, vec4(Pf0.x, Pf1.y, Pf0.z, Pf1.w));\n"
    "      float n1101 = dot(g1101, vec4(Pf1.xy, Pf0.z, Pf1.w));\n"
    "      float n0011 = dot(g0011, vec4(Pf0.xy, Pf1.zw));\n"
    "      float n1011 = dot(g1011, vec4(Pf1.x, Pf0.y, Pf1.zw));\n"
    "      float n0111 = dot(g0111, vec4(Pf0.x, Pf1.yzw));\n"
    "      float n1111 = dot(g1111, Pf1);\n"
    "\n"
    "      vec4 fade_xyzw = fade(Pf0);\n"
    "      vec4 n_0w = mix(vec4(n0000, n1000, n0100, n1100), vec4(n0001, n1001, n0101, n1101), fade_xyzw.w);\n"
    "      vec4 n_1w = mix(vec4(n0010, n1010, n0110, n1110), vec4(n0011, n1011, n0111, n1111), fade_xyzw.w);\n"
    "      vec4 n_zw = mix(n_0w, n_1w, fade_xyzw.z);\n"
    "      vec2 n_yzw = mix(n_zw.xy, n_zw.zw, fade_xyzw.y);\n"
    "      float n_xyzw = mix(n_yzw.x, n_yzw.y, fade_xyzw.x);\n"
    "      return 2.2 * n_xyzw;\n"
    "    }\n"
    ,
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
    "  float k = 5.0;\n"
    "  vec3 noisyColor;\n"
    "  noisyColor.r = cnoise(k * 10.0 * myVertexMC);\n"
    "  noisyColor.g = cnoise(k * 11.0 * myVertexMC);\n"
    "  noisyColor.b = cnoise(k * 12.0 * myVertexMC);\n"
    "  /* map ranges of noise values into different colors */\n"
    "  int i;\n"
    "  float lowerValue = .3;\n"
    "  float upperValue = .6;\n"
    "  for ( i=0; i<3; i+=1)\n"
    "  {\n"
    "    noisyColor[i] = (noisyColor[i] + 1.0) / 2.0;\n"
    "    if (noisyColor[i] < lowerValue) \n"
    "    {\n"
    "      noisyColor[i] = lowerValue;\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "      if (noisyColor[i] < upperValue)\n"
    "      {\n"
    "        noisyColor[i] = upperValue;\n"
    "      }\n"
    "      else\n"
    "      {\n"
    "        noisyColor[i] = 1.0;\n"
    "      }\n"
    "    }\n"
    "  }\n"
    "  fragOutput0.rgb = opacity * vec3(ambientColor + (noisyColor * diffuse + specular));\n"
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

  double bounds[6];
  polyData->GetBounds(bounds);
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
