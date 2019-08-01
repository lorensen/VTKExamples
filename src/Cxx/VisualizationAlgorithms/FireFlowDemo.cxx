#include <vtkSmartPointer.h>
#include <vtkVRMLImporter.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkContourFilter.h>
#include <vtkStreamTracer.h>
#include <vtkGenericOutlineFilter.h>
#include <vtkPointSource.h>
#include <vtkTubeFilter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSphereSource.h>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkPolyDataMapper.h>

#include <vtkCommand.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>

#include <vtkNamedColors.h>

#include <array>
#include <chrono>
#include <thread>

namespace
{
void MakeXWidget(vtkSmartPointer<vtkSliderWidget> &,
                 vtkSmartPointer<vtkPointSource> &,
                 vtkSmartPointer<vtkSphereSource> &,
                 vtkSmartPointer<vtkRenderer> &,
                 vtkSmartPointer<vtkRenderWindowInteractor> &);
void MakeYWidget(vtkSmartPointer<vtkSliderWidget> &,
                 vtkSmartPointer<vtkPointSource> &,
                 vtkSmartPointer<vtkSphereSource> &,
                 vtkSmartPointer<vtkRenderer> &,
                 vtkSmartPointer<vtkRenderWindowInteractor> &);
void MakeZWidget(vtkSmartPointer<vtkSliderWidget> &,
                 vtkSmartPointer<vtkPointSource> &,
                 vtkSmartPointer<vtkSphereSource> &,
                 vtkSmartPointer<vtkRenderer> &,
                 vtkSmartPointer<vtkRenderWindowInteractor> &);
}

int main (int argc, char *argv[])
{
  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkColor3d isoSurfaceColor = colors->GetColor3d("WhiteSmoke");
  vtkColor3d sphereColor = colors->GetColor3d("hotpink");
  vtkColor3d backgroundColor = colors->GetColor3d("SlateGray");

  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->UseHiddenLineRemovalOn();

  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  auto renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Import the VRML Files that define the geometry
  auto vrmlImport =
    vtkSmartPointer<vtkVRMLImporter>::New();
  vrmlImport->SetRenderWindow(renderWindow);
  vrmlImport->SetFileName(argv[1]);
  vrmlImport->Update();

  // Read the UnstructuredGrid define the solution
  auto solution =
    vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
  solution->SetFileName(argv[2]);
  solution->Update();

  std::array<double,6> bounds;
  solution->GetOutput()->GetBounds(bounds.data());

  // Create an outline
  auto outline =
    vtkSmartPointer<vtkGenericOutlineFilter>::New();
  outline->SetInputConnection(solution->GetOutputPort());

  // Create Seeds
  auto seeds =
    vtkSmartPointer<vtkPointSource>::New();
  seeds->SetRadius(0.2);
  seeds->SetCenter(3.0, 1.6, 1.25);
  seeds->SetNumberOfPoints(50);

  // Create streamlines  
  auto streamTracer =
    vtkSmartPointer<vtkStreamTracer>::New();
  streamTracer->SetIntegrationDirectionToBoth();
  streamTracer->SetInputConnection(solution->GetOutputPort());
  streamTracer->SetSourceConnection(seeds->GetOutputPort());
  streamTracer->SetMaximumPropagation(50);
  streamTracer->SetInitialIntegrationStep(.2);
  streamTracer->SetMinimumIntegrationStep(.01);
  streamTracer->SetIntegratorType(2);
  streamTracer->SetComputeVorticity(1);
  
  auto tubes =
    vtkSmartPointer<vtkTubeFilter>::New();
  tubes->SetInputConnection(streamTracer->GetOutputPort());
  tubes->SetNumberOfSides(8);
  tubes->SetRadius(.02);
  tubes->SetVaryRadius(0);

  auto mapTubes =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapTubes->SetInputConnection(tubes->GetOutputPort());
  mapTubes->SetScalarRange(solution->GetOutput()->GetScalarRange());

  auto tubesActor =
    vtkSmartPointer<vtkActor>::New();
  tubesActor->SetMapper(mapTubes);

  // Create an Isosurface
  auto isoSurface =
    vtkSmartPointer<vtkContourFilter>::New();
  isoSurface->SetValue(0, 500.0);
  isoSurface->SetInputConnection(solution->GetOutputPort());

  auto isoSurfaceMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  isoSurfaceMapper->SetInputConnection(isoSurface->GetOutputPort());
  isoSurfaceMapper->ScalarVisibilityOff();

  auto isoSurfaceActor =
    vtkSmartPointer<vtkActor>::New();
  isoSurfaceActor->SetMapper(isoSurfaceMapper);
  isoSurfaceActor->GetProperty()->SetOpacity(.5);
  isoSurfaceActor->GetProperty()->SetDiffuseColor(isoSurfaceColor.GetData());

  auto sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetCenter(seeds->GetCenter());
  sphere->SetRadius(seeds->GetRadius());
  sphere->SetThetaResolution(20);
  sphere->SetPhiResolution(11);
  auto sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphere->GetOutputPort());

  auto sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetOpacity(1.0);
  sphereActor->GetProperty()->SetSpecular(.4);
  sphereActor->GetProperty()->SetSpecularPower(80);
  sphereActor->GetProperty()->SetDiffuseColor(sphereColor.GetData());

  renderer->AddActor(tubesActor);
  renderer->AddActor(sphereActor);
  renderer->AddActor(isoSurfaceActor);

  renderer->SetBackground(backgroundColor.GetData());
  renderWindow->SetSize(640, 512);
  renderWindow->Render();
  renderer->GetActiveCamera()->Azimuth(15.0);
  renderer->GetActiveCamera()->Elevation(15.0);
  renderer->GetActiveCamera()->Dolly(1.25);
  renderer->ResetCameraClippingRange();

  // Create widgets to manipuklate point source center
  auto xWidget =
    vtkSmartPointer<vtkSliderWidget>::New();
  MakeXWidget(xWidget, seeds, sphere, renderer, renderWindowInteractor);
  dynamic_cast<vtkSliderRepresentation2D*>(xWidget->GetRepresentation())->SetMinimumValue(bounds[0]);
  dynamic_cast<vtkSliderRepresentation2D*>(xWidget->GetRepresentation())->SetMaximumValue(bounds[1]);
  auto yWidget =
    vtkSmartPointer<vtkSliderWidget>::New();
  MakeYWidget(yWidget, seeds, sphere, renderer, renderWindowInteractor);
  dynamic_cast<vtkSliderRepresentation2D*>(yWidget->GetRepresentation())->SetMinimumValue(bounds[2]);
  dynamic_cast<vtkSliderRepresentation2D*>(yWidget->GetRepresentation())->SetMaximumValue(bounds[3]);
  auto zWidget =
    vtkSmartPointer<vtkSliderWidget>::New();
  MakeZWidget(zWidget, seeds, sphere, renderer, renderWindowInteractor);
  dynamic_cast<vtkSliderRepresentation2D*>(zWidget->GetRepresentation())->SetMinimumValue(bounds[4]);
  dynamic_cast<vtkSliderRepresentation2D*>(zWidget->GetRepresentation())->SetMaximumValue(bounds[5]);

  renderWindow->Render();
  auto style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

namespace
{
#define DELAY 500
// These callbacks do the actual work.
// Callbacks for the interactions
class SliderCallbackX : public vtkCommand
{
public:
  static SliderCallbackX *New()
  {
    return new SliderCallbackX;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D *>(sliderWidget->GetRepresentation())->GetValue();
    double center[3];
    this->PointSource->GetCenter(center);
    center[0] = value;
    this->PointSource->SetCenter(center);
    SphereSource->SetCenter(center);
    PointSource->Modified();
    PointSource->Update();
    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
  }
  SliderCallbackX() = default;
  vtkPointSource *PointSource = nullptr;
  vtkSphereSource *SphereSource = nullptr;
};

void
MakeXWidget(vtkSmartPointer<vtkSliderWidget> &widget,
            vtkSmartPointer<vtkPointSource> &pointSource,
            vtkSmartPointer<vtkSphereSource> &sphereSource,
            vtkSmartPointer<vtkRenderer> &renderer,
            vtkSmartPointer<vtkRenderWindowInteractor> &interactor)
{
  // Setup a slider widget for each varying parameter
  double tubeWidth(.005);
  double sliderLength(.02);
  double titleHeight(.02);
  double labelHeight(.02);

  auto sliderRepX =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepX->SetRenderer(renderer);

  sliderRepX->SetMinimumValue(-1000.0);
  sliderRepX->SetMaximumValue( 1000);
  sliderRepX->SetValue(pointSource->GetCenter()[0]);
  sliderRepX->SetTitleText("X");
  sliderRepX->SetRenderer(renderer);
  sliderRepX->GetPoint1Coordinate()->SetValue(0.1, 0.1);
  sliderRepX->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedViewport();
  sliderRepX->GetPoint2Coordinate()->SetValue(0.3, 0.1);
  sliderRepX->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedViewport();

  sliderRepX->SetTubeWidth(tubeWidth);
  sliderRepX->SetSliderLength(sliderLength);
  sliderRepX->SetTitleHeight(titleHeight);
  sliderRepX->SetLabelHeight(labelHeight);
  sliderRepX->SetEndCapLength(tubeWidth*1.5);
  sliderRepX->SetSliderWidth(tubeWidth*1.5);
  sliderRepX->GetSliderProperty()->SetColor(0.0, 0.0, 0.0);
  sliderRepX->BuildRepresentation();

  widget->SetRepresentation(sliderRepX);
  widget->SetAnimationModeToAnimate();
  widget->SetNumberOfAnimationSteps(10);
  widget->SetInteractor(interactor);
  widget->EnabledOn();

  auto callbackX =
    vtkSmartPointer<SliderCallbackX>::New();
  callbackX->PointSource = pointSource;
  callbackX->SphereSource = sphereSource;
  widget->AddObserver(vtkCommand::InteractionEvent,callbackX);
}

class SliderCallbackY : public vtkCommand
{
public:
  static SliderCallbackY *New()
  {
    return new SliderCallbackY;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D *>(sliderWidget->GetRepresentation())->GetValue();
    double center[3];
    this->PointSource->GetCenter(center);
    center[1] = value;
    this->PointSource->SetCenter(center);
    this->SphereSource->SetCenter(center);
    PointSource->Modified();
    PointSource->Update();
    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
  }
  SliderCallbackY() = default;
  vtkPointSource *PointSource = nullptr;
  vtkSphereSource *SphereSource = nullptr;
};

void
MakeYWidget(vtkSmartPointer<vtkSliderWidget> &widget,
            vtkSmartPointer<vtkPointSource> &pointSource,
            vtkSmartPointer<vtkSphereSource> &sphereSource,
            vtkSmartPointer<vtkRenderer> &renderer,
            vtkSmartPointer<vtkRenderWindowInteractor> &interactor)
{
  // Setup a slider widget for each varying parameter
  double tubeWidth(.005);
  double sliderLength(.02);
  double titleHeight(.02);
  double labelHeight(.02);

  auto sliderRepY =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepY->SetRenderer(renderer);

  sliderRepY->SetMinimumValue(-1000.0);
  sliderRepY->SetMaximumValue( 1000);
  sliderRepY->SetValue(pointSource->GetCenter()[1]);
  sliderRepY->SetTitleText("Y");
  sliderRepY->SetRenderer(renderer);
  sliderRepY->GetPoint1Coordinate()->SetValue(0.4, 0.1);
  sliderRepY->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedViewport();
  sliderRepY->GetPoint2Coordinate()->SetValue(0.6, 0.1);
  sliderRepY->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedViewport();

  sliderRepY->SetTubeWidth(tubeWidth);
  sliderRepY->SetSliderLength(sliderLength);
  sliderRepY->SetTitleHeight(titleHeight);
  sliderRepY->SetLabelHeight(labelHeight);
  sliderRepY->SetEndCapLength(tubeWidth*1.5);
  sliderRepY->SetSliderWidth(tubeWidth*1.5);
  sliderRepY->GetSliderProperty()->SetColor(0.0, 0.0, 0.0);
  sliderRepY->BuildRepresentation();

  widget->SetRepresentation(sliderRepY);
  widget->SetAnimationModeToAnimate();
  widget->SetNumberOfAnimationSteps(10);
  widget->SetInteractor(interactor);
  widget->EnabledOn();

  auto callbackY =
    vtkSmartPointer<SliderCallbackY>::New();
  callbackY->PointSource = pointSource;
  callbackY->SphereSource = sphereSource;

  widget->AddObserver(vtkCommand::InteractionEvent,callbackY);
}

class SliderCallbackZ : public vtkCommand
{
public:
  static SliderCallbackZ *New()
  {
    return new SliderCallbackZ;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D *>(sliderWidget->GetRepresentation())->GetValue();
    double center[3];
    this->PointSource->GetCenter(center);
    center[2] = value;
    this->PointSource->SetCenter(center);
    this->SphereSource->SetCenter(center);
    PointSource->Modified();
    PointSource->Update();
    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
  }
  SliderCallbackZ() = default;
  vtkPointSource* PointSource = nullptr;
  vtkSphereSource* SphereSource = nullptr;
};

void
MakeZWidget(vtkSmartPointer<vtkSliderWidget> &widget,
            vtkSmartPointer<vtkPointSource> &pointSource,
            vtkSmartPointer<vtkSphereSource> &sphereSource,
            vtkSmartPointer<vtkRenderer> &renderer,
            vtkSmartPointer<vtkRenderWindowInteractor> &interactor)
{
  // Setup a slider widget for each varying parameter
  double tubeWidth(.005);
  double sliderLength(.02);
  double titleHeight(.02);
  double labelHeight(.02);

  auto sliderRepZ =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepZ->SetRenderer(renderer);

  sliderRepZ->SetMinimumValue(-1000.0);
  sliderRepZ->SetMaximumValue( 1000);
  sliderRepZ->SetValue(pointSource->GetCenter()[2]);
  sliderRepZ->SetTitleText("Z");
  sliderRepZ->SetRenderer(renderer);
  sliderRepZ->GetPoint1Coordinate()->SetValue(0.7, 0.1);
  sliderRepZ->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedViewport();
  sliderRepZ->GetPoint2Coordinate()->SetValue(0.9, 0.1);
  sliderRepZ->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedViewport();

  sliderRepZ->SetTubeWidth(tubeWidth);
  sliderRepZ->SetSliderLength(sliderLength);
  sliderRepZ->SetTitleHeight(titleHeight);
  sliderRepZ->SetLabelHeight(labelHeight);
  sliderRepZ->SetEndCapLength(tubeWidth*1.5);
  sliderRepZ->SetSliderWidth(tubeWidth*1.5);
  sliderRepZ->GetSliderProperty()->SetColor(0.0, 0.0, 0.0);
  sliderRepZ->BuildRepresentation();

  widget->SetRepresentation(sliderRepZ);
  widget->SetAnimationModeToAnimate();
  widget->SetNumberOfAnimationSteps(10);
  widget->SetInteractor(interactor);
  widget->EnabledOn();

  auto callbackZ =
    vtkSmartPointer<SliderCallbackZ>::New();
  callbackZ->PointSource = pointSource;
  callbackZ->SphereSource = sphereSource;

  widget->AddObserver(vtkCommand::InteractionEvent,callbackZ);
}
}
