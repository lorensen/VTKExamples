#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkShrinkFilter.h>
#include <vtkSmartPointer.h>
#include <vtkTessellatedBoxSource.h>

int main (int /* argc */, char * /* argv */ [])
{
  double bounds[6];
  bounds[0] = -10.0; bounds[1] = 10.0;
  bounds[2] = 10.0; bounds[3] = 20.0;
  bounds[4] = -5.0; bounds[5] = 5.0;

  vtkSmartPointer<vtkTessellatedBoxSource> boxSource =
    vtkSmartPointer<vtkTessellatedBoxSource>::New();
  boxSource->SetLevel(3);
  boxSource->QuadsOn();
  boxSource->SetBounds(bounds);
  boxSource->SetOutputPointsPrecision(vtkAlgorithm::SINGLE_PRECISION);

  vtkSmartPointer<vtkShrinkFilter> shrink =
    vtkSmartPointer<vtkShrinkFilter>::New();
  shrink->SetInputConnection(boxSource->GetOutputPort());
  shrink->SetShrinkFactor(.8);

  //Create a mapper and actor
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(shrink->GetOutputPort());

  vtkSmartPointer<vtkProperty> back =
    vtkSmartPointer<vtkProperty>::New();
  back->SetColor(colors->GetColor3d("Tomato").GetData());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->EdgeVisibilityOn();
  actor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
  actor->SetBackfaceProperty(back);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCameraClippingRange();

  //Render and interact
  renderWindow->SetSize(640, 480);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
