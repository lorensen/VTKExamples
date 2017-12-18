#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkSimpleMotionBlurPass.h>
#include <vtkNew.h>
#include <vtkOpenGLRenderer.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderStepsPass.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTextureObject.h>

//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  vtkNew<vtkRenderer> renderer;
  renderer->SetBackground(0.3, 0.4, 0.6);
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
    actor->GetProperty()->SetAmbientColor(1.0, 0.0, 0.0);
    actor->GetProperty()->SetDiffuseColor(1.0, 0.8, 0.3);
    actor->GetProperty()->SetSpecular(0.0);
    actor->GetProperty()->SetDiffuse(0.5);
    actor->GetProperty()->SetAmbient(0.3);
    actor->SetPosition(-0.1, 0.0, -0.1);
    renderer->AddActor(actor);
  }

  {
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetAmbientColor(0.2, 0.2, 1.0);
    actor->GetProperty()->SetDiffuseColor(0.2, 1.0, 0.8);
    actor->GetProperty()->SetSpecularColor(1.0, 1.0, 1.0);
    actor->GetProperty()->SetSpecular(0.2);
    actor->GetProperty()->SetDiffuse(0.9);
    actor->GetProperty()->SetAmbient(0.1);
    actor->GetProperty()->SetSpecularPower(10.0);
    renderer->AddActor(actor);
  }

  {
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetDiffuseColor(0.5, 0.65, 1.0);
    actor->GetProperty()->SetSpecularColor(1.0, 1.0, 1.0);
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
