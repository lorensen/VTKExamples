// test baking shadow maps

#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCameraPass.h>
#include <vtkCellArray.h>
#include <vtkLight.h>
#include <vtkOpenGLRenderer.h>
#include <vtkOpenGLTexture.h>
#include <vtkPlaneSource.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderPassCollection.h>
#include <vtkRenderStepsPass.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSequencePass.h>
#include <vtkShadowMapBakerPass.h>
#include <vtkShadowMapPass.h>
#include <vtkNamedColors.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>

#include <vtksys/SystemTools.hxx>
#include <array>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  // Read the polyData
  auto polyData =
    ReadPolyData(argc > 1 ? argv[1] : "");;

  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(0.3, 0.4, 0.6);

  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);

  auto interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  auto light1 =
    vtkSmartPointer<vtkLight>::New();
  light1->SetFocalPoint(0,0,0);
  light1->SetPosition(0,1,0.2);
  light1->SetColor(0.95,0.97,1.0);
  light1->SetIntensity(0.8);
  renderer->AddLight(light1);

  auto light2 =
    vtkSmartPointer<vtkLight>::New();
  light2->SetFocalPoint(0,0,0);
  light2->SetPosition(1.0,1.0,1.0);
  light2->SetColor(1.0,0.8,0.7);
  light2->SetIntensity(0.3);
  renderer->AddLight(light2);

  auto mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polyData);

  auto actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetAmbientColor(0.135, 0.2225, 0.3);
  actor->GetProperty()->SetDiffuseColor(0.54, 0.89, 0.63);
  actor->GetProperty()->SetSpecularColor(1.0, 1.0, 1.0);
  actor->GetProperty()->SetSpecular(0.51);
  actor->GetProperty()->SetDiffuse(0.7);
  actor->GetProperty()->SetAmbient(0.7);
  actor->GetProperty()->SetSpecularPower(30.0);
  actor->GetProperty()->SetOpacity(1.0);
  renderer->AddActor(actor);

  // add a plane
  std::array<double, 6> bounds;
  polyData->GetBounds(bounds.data());

  std::array<double, 3> range;
  range[0] = bounds[1] - bounds[0];
  range[1] = bounds[3] - bounds[2];
  range[2] = bounds[5] - bounds[4];
  std::cout << "range: "
            << range[0] << "," 
            << range[1] << "," 
            << range[2] << std::endl;
  double expand = 1.0;
#define THICKNESS (range[2] * .1)
  auto plane =
    vtkSmartPointer<vtkCubeSource>::New();
  plane->SetCenter((bounds[1] + bounds[0]) / 2.0,
                   bounds[2] + THICKNESS / 2.0,
                   (bounds[5] + bounds[4]) / 2.0);
  plane->SetXLength(bounds[1] - bounds[0] + (range[0] * expand));
  plane->SetYLength(THICKNESS);
  plane->SetZLength(bounds[5] - bounds[4] + (range[2] * expand));

  auto planeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  planeMapper->SetInputConnection(plane->GetOutputPort());

  auto planeActor =
    vtkSmartPointer<vtkActor>::New();
  planeActor->SetMapper(planeMapper);
  renderer->AddActor(planeActor);

  renderWindow->SetMultiSamples(0);

  auto shadows =
    vtkSmartPointer<vtkShadowMapPass>::New();

  auto seq =
    vtkSmartPointer<vtkSequencePass>::New();

  auto passes =
    vtkSmartPointer<vtkRenderPassCollection>::New();
  passes->AddItem(shadows->GetShadowMapBakerPass());
  passes->AddItem(shadows);
  seq->SetPasses(passes);

  auto cameraP =
    vtkSmartPointer<vtkCameraPass>::New();
  cameraP->SetDelegatePass(seq);

  // tell the renderer to use our render pass pipeline
  vtkOpenGLRenderer *glrenderer =
    vtkOpenGLRenderer::SafeDownCast(renderer);
  glrenderer->SetPass(cameraP);

  renderWindow->Render();

  int numRenders = 8;
  for (int i = 0; i < numRenders; ++i)
  {
    glrenderer->GetActiveCamera()->Azimuth(80.0/numRenders);
    glrenderer->GetActiveCamera()->Elevation(80.0/numRenders);
    renderWindow->Render();
  }

  renderer->GetActiveCamera()->SetPosition(-0.2,0.2,1);
  renderer->GetActiveCamera()->SetFocalPoint(0,0,0);
  renderer->GetActiveCamera()->SetViewUp(0,1,0);
  renderer->GetActiveCamera()->OrthogonalizeViewUp();
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Dolly(2.25);
  renderer->ResetCameraClippingRange();
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = vtksys::SystemTools::GetFilenameLastExtension(std::string(fileName));
  if (extension == ".ply")
  {
    auto reader =
      vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    auto reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    auto reader =
      vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    auto reader =
      vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    auto reader =
      vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    auto reader =
      vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    auto source =
      vtkSmartPointer<vtkSphereSource>::New();
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
}
