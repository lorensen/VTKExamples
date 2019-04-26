/*=========================================================================

  Program:   Visualization Toolkit

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkImageData.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkJPEGReader.h>
#include <vtkLight.h>
#include <vtkNamedColors.h>
#include <vtkOpenGLPolyDataMapper.h>
#include <vtkOpenGLRenderWindow.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkShaderProgram.h>
#include <vtkSkybox.h>
#include <vtkSmartPointer.h>
#include <vtkTexture.h>
#include <vtkVersion.h>
#include <vtkXMLPolyDataReader.h>

#if VTK_VERSION_NUMBER >= 89000000000ULL
#define USE_SHADER_PROPERTIES 1
#include <vtkShaderProperty.h>
#endif

//----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " file.vtp wintersun.jpg" << std::endl;
    return EXIT_SUCCESS;
  }

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(0.0, 0.0, 0.0);
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  auto light = vtkSmartPointer<vtkLight>::New();
  light->SetLightTypeToSceneLight();
  light->SetPosition(1.0, 7.0, 1.0);
  renderer->AddLight(light);

  auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);

  auto norms = vtkSmartPointer<vtkPolyDataNormals>::New();
  norms->SetInputConnection(reader->GetOutputPort());

  auto texture = vtkSmartPointer<vtkTexture>::New();
  texture->InterpolateOn();

  // mipmapping works on many systems but is not
  // core 3.2 for cube maps. VTK will silently
  // ignore it if it is not supported. We commented it
  // out here to make valid images easier
  // texture->MipmapOn();

  auto imgReader = vtkSmartPointer<vtkJPEGReader>::New();
  imgReader->SetFileName(argv[2]);
  texture->SetInputConnection(imgReader->GetOutputPort());

  auto mapper = vtkSmartPointer<vtkOpenGLPolyDataMapper>::New();
  mapper->SetInputConnection(norms->GetOutputPort());

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetPosition(0, 0, 0);
  actor->SetScale(6.0, 6.0, 6.0);
  actor->GetProperty()->SetSpecular(0.8);
  actor->GetProperty()->SetSpecularPower(20);
  actor->GetProperty()->SetDiffuse(0.1);
  actor->GetProperty()->SetAmbient(0.1);
  actor->GetProperty()->SetDiffuseColor(1.0, 0.0, 0.4);
  actor->GetProperty()->SetAmbientColor(0.4, 0.0, 1.0);
  renderer->AddActor(actor);
  actor->SetTexture(texture);
  actor->SetMapper(mapper);

#if USE_SHADER_PROPERTIES
  vtkShaderProperty* sp = actor->GetShaderProperty();
  sp->AddVertexShaderReplacement(
      "//VTK::PositionVC::Dec",  // replace
      true,                      // before the standard replacements
      "//VTK::PositionVC::Dec\n" // we still want the default
      "out vec3 TexCoords;\n",
      false // only do it once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Vertex,
      "//VTK::PositionVC::Dec",  // replace
      true,                      // before the standard replacements
      "//VTK::PositionVC::Dec\n" // we still want the default
      "out vec3 TexCoords;\n",
      false // only do it once
  );
#endif
#if USE_SHADER_PROPERTIES
  sp->AddVertexShaderReplacement(
      "//VTK::PositionVC::Impl",  // replace
      true,                       // before the standard replacements
      "//VTK::PositionVC::Impl\n" // we still want the default
      "vec3 camPos = -MCVCMatrix[3].xyz * mat3(MCVCMatrix);\n"
      "TexCoords.xyz = reflect(vertexMC.xyz - camPos, normalize(normalMC));\n",
      false // only do it once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Vertex,
      "//VTK::PositionVC::Impl",  // replace
      true,                       // before the standard replacements
      "//VTK::PositionVC::Impl\n" // we still want the default
      "vec3 camPos = -MCVCMatrix[3].xyz * mat3(MCVCMatrix);\n"
      "TexCoords.xyz = reflect(vertexMC.xyz - camPos, normalize(normalMC));\n",
      false // only do it once
  );
#endif
#if USE_SHADER_PROPERTIES
  sp->AddFragmentShaderReplacement(
      "//VTK::Light::Dec",  // replace
      true,                 // before the standard replacements
      "//VTK::Light::Dec\n" // we still want the default
      "in vec3 TexCoords;\n",
      false // only do it once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Fragment,
      "//VTK::Light::Dec",  // replace
      true,                 // before the standard replacements
      "//VTK::Light::Dec\n" // we still want the default
      "in vec3 TexCoords;\n",
      false // only do it once
  );
#endif

#if USE_SHADER_PROPERTIES
  sp->AddFragmentShaderReplacement(
      "//VTK::Light::Impl", // replace
      true,                 // before the standard replacements
      "//VTK::Light::Impl\n"
      "  float phix = length(vec2(TexCoords.x, TexCoords.z));\n"
      "  vec3 skyColor = texture(actortexture, vec2(0.5*atan(TexCoords.z, "
      "TexCoords.x)/3.1415927 + 0.5, atan(TexCoords.y,phix)/3.1415927 + "
      "0.5)).xyz;\n"
      "  gl_FragData[0] = vec4(ambientColor + diffuse + specular + "
      "specularColor*skyColor, opacity);\n", // we still want the default
      false                                  // only do it once
  );
#else
  mapper->AddShaderReplacement(
      vtkShader::Fragment,
      "//VTK::Light::Impl", // replace
      true,                 // before the standard replacements
      "//VTK::Light::Impl\n"
      "  float phix = length(vec2(TexCoords.x, TexCoords.z));\n"
      "  vec3 skyColor = texture(actortexture, vec2(0.5*atan(TexCoords.z, "
      "TexCoords.x)/3.1415927 + 0.5, atan(TexCoords.y,phix)/3.1415927 + "
      "0.5)).xyz;\n"
      "  gl_FragData[0] = vec4(ambientColor + diffuse + specular + "
      "specularColor*skyColor, opacity);\n", // we still want the default
      false                                  // only do it once
  );
#endif

  auto world = vtkSmartPointer<vtkSkybox>::New();
  world->SetProjectionToSphere();
  world->SetTexture(texture);
  renderer->AddActor(world);

  renderer->GetActiveCamera()->SetPosition(0.0, 0.55, 2.0);
  renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.55, 0.0);
  renderer->GetActiveCamera()->SetViewAngle(60.0);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(1.1);
  renderer->GetActiveCamera()->Azimuth(0);
  renderer->GetActiveCamera()->Elevation(5);
  renderer->ResetCameraClippingRange();

  renderWindow->Render();
  renderWindow->SetWindowName("SphereMap");
  renderWindow->Render();

  auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  renderWindow->GetInteractor()->SetInteractorStyle(style);

  interactor->Start();

  return EXIT_SUCCESS;
}
