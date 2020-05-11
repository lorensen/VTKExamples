#include "vtkAxisActor.h"
#include "vtkSmartPointer.h"

#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSphereSource.h"
#include "vtkStringArray.h"
#include "vtkTextProperty.h"
#include <vtkNamedColors.h>

//----------------------------------------------------------------------------
int main(int, char*[])
{
  vtkSmartPointer<vtkNamedColors> colors =
      vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkSphereSource> source =
      vtkSmartPointer<vtkSphereSource>::New();
  source->SetPhiResolution(31);
  source->SetThetaResolution(31);
  source->Update();
  double bounds[6];
  source->GetOutput()->GetBounds(bounds);
  std::cout << "bounds: " << bounds[0] << ", " << bounds[2] << ", " << bounds[3]
            << ", " << bounds[1] << ", " << bounds[3] << ", " << bounds[5]
            << std::endl;
  double center[3];
  source->GetOutput()->GetCenter(center);
  std::cout << "center: " << center[0] << ", " << center[1] << ", " << center[2]
            << std::endl;

  // Create the axis actor
  vtkSmartPointer<vtkAxisActor> axis = vtkSmartPointer<vtkAxisActor>::New();
  axis->SetPoint1(-1.1, 0.0, 0.0);
  axis->SetPoint2(1.1, 0.0, 0.0);
  axis->SetTickLocationToBoth();
  axis->SetAxisTypeToX();
  axis->SetTitle("A Sphere");
  axis->SetTitleScale(0.2);
  axis->TitleVisibilityOn();

  axis->SetMajorTickSize(0.05);
  axis->SetMinorTickSize(1);
  axis->DrawGridlinesOff();
  axis->GetTitleTextProperty()->SetColor(
      colors->GetColor3d("banana").GetData());
  axis->GetLabelTextProperty()->SetColor(
      colors->GetColor3d("orange").GetData());

  vtkSmartPointer<vtkStringArray> labels =
      vtkSmartPointer<vtkStringArray>::New();
  labels->SetNumberOfTuples(1);
  labels->SetValue(0, "x Axis");

  axis->SetLabels(labels);
  axis->SetLabelScale(.1);
  axis->MinorTicksVisibleOn();
  axis->SetDeltaMajor(0, .1);
  axis->SetCalculateTitleOffset(0);
  axis->SetCalculateLabelOffset(0);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(source->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuseColor(colors->GetColor4d("tomato").GetData());

  // Create the RenderWindow, Renderer and both Actors
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  axis->SetCamera(renderer->GetActiveCamera());

  renderer->AddActor(actor);
  renderer->AddActor(axis);

  renderer->SetBackground(colors->GetColor4d("SlateGray").GetData());
  renderWindow->SetSize(640, 480);
  renderer->ResetCamera();
  renderer->ResetCameraClippingRange();

  // render the image
  renderWindow->Render();

  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}
