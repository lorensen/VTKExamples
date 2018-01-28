#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkOpenGLRenderer.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderStepsPass.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSimpleMotionBlurPass.h>
#include <vtkTextureObject.h>

#include <algorithm>
#include <array>

//----------------------------------------------------------------------------
int main(int, char *argv[])
{
  vtkNew<vtkNamedColors> colors;

  // Set the colors.
  auto SetColor = [&colors](std::array<double, 3>& v,
                            std::string const& colorName) {
    auto const scaleFactor = 255.0;
    std::transform(std::begin(v), std::end(v), std::begin(v),
                   [=](double const& n) { return n / scaleFactor; });
    colors->SetColor(colorName, v.data());
    return;
  };
  std::array<double, 3> bkg1{{77, 102, 153}};
  SetColor(bkg1, "Bkg");
  std::array<double, 3> a1Diff{{255, 204, 77}};
  SetColor(a1Diff, "A1Diff");
  std::array<double, 3> a2Amb{{51, 51, 255}};
  SetColor(a1Diff, "A2Amb");
  std::array<double, 3> a2Diff{{51, 255, 204}};
  SetColor(a1Diff, "A2Diff");
  std::array<double, 3> a3Amb{{128, 166, 255}};
  SetColor(a1Diff, "A3Amb");

  vtkNew<vtkRenderer> renderer;
  renderer->SetBackground(colors->GetColor3d("Bkg").GetData());
  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->SetSize(500, 500);
  renderWindow->AddRenderer(renderer);
  vtkNew<vtkRenderWindowInteractor>  iren;
  iren->SetRenderWindow(renderWindow);

  vtkNew<vtkPLYReader> reader;
  reader->SetFileName(argv[1]);
  reader->Update();

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(reader->GetOutputPort());

  // create three models
  {
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetAmbientColor(colors->GetColor3d("Red").GetData());
    actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("A1Diff").GetData());
    actor->GetProperty()->SetSpecular(0.0);
    actor->GetProperty()->SetDiffuse(0.5);
    actor->GetProperty()->SetAmbient(0.3);
    actor->SetPosition(-0.1, 0.0, -0.1);
    renderer->AddActor(actor);
  }

  {
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetAmbientColor(colors->GetColor3d("A2Amb").GetData());
    actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("A2Diff").GetData());
    actor->GetProperty()->SetSpecularColor(colors->GetColor3d("Black").GetData());
    actor->GetProperty()->SetSpecular(0.2);
    actor->GetProperty()->SetDiffuse(0.9);
    actor->GetProperty()->SetAmbient(0.1);
    actor->GetProperty()->SetSpecularPower(10.0);
    renderer->AddActor(actor);
  }

  {
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("A3Amb").GetData());
    actor->GetProperty()->SetSpecularColor(colors->GetColor3d("White").GetData());
    actor->GetProperty()->SetSpecular(0.7);
    actor->GetProperty()->SetDiffuse(0.4);
    actor->GetProperty()->SetSpecularPower(60.0);
    actor->SetPosition(0.1, 0.0, 0.1);
    renderer->AddActor(actor);
  }

  renderWindow->SetMultiSamples(0);

  // create the basic VTK render steps
  vtkNew<vtkRenderStepsPass> basicPasses;

  vtkNew<vtkSimpleMotionBlurPass> motion;
  motion->SetDelegatePass(basicPasses);

  // tell the renderer to use our render pass pipeline
  vtkOpenGLRenderer *glrenderer =
    vtkOpenGLRenderer::SafeDownCast(renderer);
  glrenderer->SetPass(motion);

  int numRenders = 30;

  renderer->GetActiveCamera()->SetPosition(0,0,-1);
  renderer->GetActiveCamera()->SetFocalPoint(0,0,0);
  renderer->GetActiveCamera()->SetViewUp(0,1,0);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(15.0);
  renderer->GetActiveCamera()->Zoom(1.2);

  renderWindow->Render();

  for (int i = 0; i < numRenders; ++i)
  {
    renderer->GetActiveCamera()->Azimuth(10.0/numRenders);
    renderer->GetActiveCamera()->Elevation(10.0/numRenders);
    renderWindow->Render();
  }
  iren->Start();

  return EXIT_SUCCESS;
}

