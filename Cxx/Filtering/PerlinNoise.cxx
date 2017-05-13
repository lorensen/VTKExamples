#include <vtkSmartPointer.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <vtkProperty.h>
#include <vtkCamera.h>

#include <vtkPerlinNoise.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPerlinNoise> perlinNoise =
    vtkSmartPointer<vtkPerlinNoise>::New();
  perlinNoise->SetFrequency(2, 1.25, 1.5);
  perlinNoise->SetPhase(0, 0, 0);

  vtkSmartPointer<vtkSampleFunction> sample =
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetImplicitFunction(perlinNoise);
  sample->SetSampleDimensions(65, 65, 20);
  sample->ComputeNormalsOff();

  vtkSmartPointer<vtkContourFilter> surface =
    vtkSmartPointer<vtkContourFilter>::New();
  surface->SetInputConnection(sample->GetOutputPort());
  surface->SetValue(0, 0.0);
  
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(surface->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(0.2, 0.4, 0.6);
  
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  
  // Add the actors to the renderer, set the background and size
  
  renderer->AddActor(actor);
  renderer->SetBackground(1, 1, 1);
  renderWindow->SetSize(300, 300);
  renderer->ResetCamera();
  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
