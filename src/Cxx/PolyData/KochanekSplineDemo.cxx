#include <vtkSmartPointer.h>
#include <vtkKochanekSpline.h>
#include <vtkParametricSpline.h>
#include <vtkParametricFunctionSource.h>

#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkActor2D.h>

#include <vtkSliderRepresentation2D.h>
#include <vtkGlyph3DMapper.h>
#include <vtkSphereSource.h>
#include <vtkNamedColors.h>

#include <vtkCommand.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>

namespace
{
void MakeTensionWidget(vtkSmartPointer<vtkSliderWidget> &,
                       vtkSmartPointer<vtkParametricFunctionSource> &,
                       vtkSmartPointer<vtkParametricSpline> &,
                       vtkSmartPointer<vtkRenderer> &,
                       vtkSmartPointer<vtkRenderWindowInteractor> &);
void MakeContinuityWidget(vtkSmartPointer<vtkSliderWidget> &,
                       vtkSmartPointer<vtkParametricFunctionSource> &,
                       vtkSmartPointer<vtkParametricSpline> &,
                       vtkSmartPointer<vtkRenderer> &,
                       vtkSmartPointer<vtkRenderWindowInteractor> &);
void MakeBiasWidget(vtkSmartPointer<vtkSliderWidget> &,
                       vtkSmartPointer<vtkParametricFunctionSource> &,
                       vtkSmartPointer<vtkParametricSpline> &,
                       vtkSmartPointer<vtkRenderer> &,
                       vtkSmartPointer<vtkRenderWindowInteractor> &);
}

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  int numberOfPoints = 7;
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->SetNumberOfPoints(numberOfPoints);
  double radius = 1.0;
  double delta = 2.0 * vtkMath::Pi() / double (numberOfPoints);
    for (int n = 0; n < numberOfPoints; ++n)
    {
      double theta = delta * n;
      double x = radius * std::cos(theta);
      double y = radius * std::sin(theta);
      double z = n * (vtkMath::Pi() / numberOfPoints);
      points->SetPoint(n, x, y, z);
    }
    
  vtkSmartPointer<vtkKochanekSpline> xSpline = 
    vtkSmartPointer<vtkKochanekSpline>::New();
  vtkSmartPointer<vtkKochanekSpline> ySpline = 
    vtkSmartPointer<vtkKochanekSpline>::New();
  vtkSmartPointer<vtkKochanekSpline> zSpline = 
    vtkSmartPointer<vtkKochanekSpline>::New();

  vtkSmartPointer<vtkParametricSpline> spline = 
    vtkSmartPointer<vtkParametricSpline>::New();
  spline->SetXSpline(xSpline);
  spline->SetYSpline(ySpline);
  spline->SetZSpline(zSpline);
  spline->SetPoints(points);
  
  vtkSmartPointer<vtkParametricFunctionSource> functionSource = 
      vtkSmartPointer<vtkParametricFunctionSource>::New();
  functionSource->SetParametricFunction(spline);
  functionSource->SetUResolution(50 * numberOfPoints);
  functionSource->SetVResolution(50 * numberOfPoints);
  functionSource->SetWResolution(50 * numberOfPoints);
  functionSource->Update();

  // Setup actor and mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(functionSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("DarkSlateGrey").GetData());
  actor->GetProperty()->SetLineWidth(3.0);
  
  // Glyph the points
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetPhiResolution(21);
  sphere->SetThetaResolution(21);
  sphere->SetRadius(.1);

  // Create a polydata to store everything in
  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();
  polyData->SetPoints(points);

  vtkSmartPointer<vtkGlyph3DMapper> pointMapper =
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  pointMapper->SetInputData(polyData);
  pointMapper->SetSourceConnection(sphere->GetOutputPort());

  vtkSmartPointer<vtkActor> pointActor =
    vtkSmartPointer<vtkActor>::New();
  pointActor->SetMapper(pointMapper);
  pointActor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());
  pointActor->GetProperty()->SetOpacity(.5);;

  // Setup render window, renderer, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->AddActor(pointActor);;
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());
  renderWindow->Render();

  vtkSmartPointer<vtkSliderWidget> tensionWidget =
    vtkSmartPointer<vtkSliderWidget>::New();
  MakeTensionWidget(tensionWidget, functionSource, spline, renderer, renderWindowInteractor);
  vtkSmartPointer<vtkSliderWidget> continuityWidget =
    vtkSmartPointer<vtkSliderWidget>::New();
  MakeContinuityWidget(continuityWidget, functionSource, spline, renderer, renderWindowInteractor);
  vtkSmartPointer<vtkSliderWidget> biasWidget =
    vtkSmartPointer<vtkSliderWidget>::New();
  MakeBiasWidget(biasWidget, functionSource, spline, renderer, renderWindowInteractor);

  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}

namespace
{
// These callbacks do the actual work.
// Callbacks for the interactions
class SliderCallbackTension : public vtkCommand
{
public:
  static SliderCallbackTension *New()
  {
    return new SliderCallbackTension;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D *>(sliderWidget->GetRepresentation())->GetValue();
    dynamic_cast<vtkKochanekSpline *>(this->ParametricSpline->GetXSpline())->SetDefaultTension(value);
    dynamic_cast<vtkKochanekSpline*>(this->ParametricSpline->GetYSpline())->SetDefaultTension(value);
    dynamic_cast<vtkKochanekSpline*>(this->ParametricSpline->GetZSpline())->SetDefaultTension(value);
    ParametricSource->Modified();
    ParametricSource->Update();
  }
  SliderCallbackTension():ParametricSource(0), ParametricSpline(0) {}
  vtkParametricSpline *ParametricSpline;
  vtkParametricFunctionSource *ParametricSource;
};

void
MakeTensionWidget(vtkSmartPointer<vtkSliderWidget> &widget,
                  vtkSmartPointer<vtkParametricFunctionSource> &parametricSource,
                  vtkSmartPointer<vtkParametricSpline> &parametricSpline,
                  vtkSmartPointer<vtkRenderer> &renderer,
                  vtkSmartPointer<vtkRenderWindowInteractor> &interactor)
{
  // Setup a slider widget for each varying parameter
  double tubeWidth(.005);
  double sliderLength(.02);
  double titleHeight(.02);
  double labelHeight(.02);

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRepTension =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepTension->SetRenderer(renderer);

  sliderRepTension->SetMinimumValue(-1.0);
  sliderRepTension->SetMaximumValue(1.0);
  sliderRepTension->SetValue(dynamic_cast<vtkKochanekSpline*>(parametricSpline->GetXSpline())->GetDefaultTension());
  sliderRepTension->SetTitleText("Tension");
  sliderRepTension->SetRenderer(renderer);
  sliderRepTension->GetPoint1Coordinate()->SetValue(0.1, 0.1);
  sliderRepTension->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedViewport();
  sliderRepTension->GetPoint2Coordinate()->SetValue(0.3, 0.1);
  sliderRepTension->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedViewport();

  sliderRepTension->SetTubeWidth(tubeWidth);
  sliderRepTension->SetSliderLength(sliderLength);
  sliderRepTension->SetTitleHeight(titleHeight);
  sliderRepTension->SetLabelHeight(labelHeight);
  sliderRepTension->SetEndCapLength(tubeWidth*1.5);
  sliderRepTension->SetSliderWidth(tubeWidth*1.5);
  sliderRepTension->GetSliderProperty()->SetColor(0.0, 0.0, 0.0);
  sliderRepTension->BuildRepresentation();

  widget->SetRepresentation(sliderRepTension);
  widget->SetAnimationModeToAnimate();
  widget->SetNumberOfAnimationSteps(10);
  widget->SetInteractor(interactor);
  widget->EnabledOn();

  vtkSmartPointer<SliderCallbackTension> callbackTension =
    vtkSmartPointer<SliderCallbackTension>::New();
  callbackTension->ParametricSpline = parametricSpline;
  callbackTension->ParametricSource = parametricSource;

  widget->AddObserver(vtkCommand::InteractionEvent,callbackTension);
}

class SliderCallbackContinuity : public vtkCommand
{
public:
  static SliderCallbackContinuity *New()
  {
    return new SliderCallbackContinuity;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D *>(sliderWidget->GetRepresentation())->GetValue();
    dynamic_cast<vtkKochanekSpline*>(this->ParametricSpline->GetXSpline())->SetDefaultContinuity(value);
    dynamic_cast<vtkKochanekSpline*>(this->ParametricSpline->GetYSpline())->SetDefaultContinuity(value);
    dynamic_cast<vtkKochanekSpline*>(this->ParametricSpline->GetZSpline())->SetDefaultContinuity(value);
    ParametricSource->Modified();
    ParametricSource->Update();
  }
  SliderCallbackContinuity():ParametricSource(0), ParametricSpline(0) {}
  vtkParametricSpline *ParametricSpline;
  vtkParametricFunctionSource *ParametricSource;
};

void
MakeContinuityWidget(vtkSmartPointer<vtkSliderWidget> &widget,
                  vtkSmartPointer<vtkParametricFunctionSource> &parametricSource,
                  vtkSmartPointer<vtkParametricSpline> &parametricSpline,
                  vtkSmartPointer<vtkRenderer> &renderer,
                  vtkSmartPointer<vtkRenderWindowInteractor> &interactor)
{
  // Setup a slider widget for each varying parameter
  double tubeWidth(.005);
  double sliderLength(.02);
  double titleHeight(.02);
  double labelHeight(.02);

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRepContinuity =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepContinuity->SetRenderer(renderer);

  sliderRepContinuity->SetMinimumValue(-1.0);
  sliderRepContinuity->SetMaximumValue(1.0);
  sliderRepContinuity->SetValue(dynamic_cast<vtkKochanekSpline*>(parametricSpline->GetXSpline())->GetDefaultContinuity());
  sliderRepContinuity->SetTitleText("Continuity");
  sliderRepContinuity->SetRenderer(renderer);
  sliderRepContinuity->GetPoint1Coordinate()->SetValue(0.4, 0.1);
  sliderRepContinuity->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedViewport();
  sliderRepContinuity->GetPoint2Coordinate()->SetValue(0.6, 0.1);
  sliderRepContinuity->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedViewport();

  sliderRepContinuity->SetTubeWidth(tubeWidth);
  sliderRepContinuity->SetSliderLength(sliderLength);
  sliderRepContinuity->SetTitleHeight(titleHeight);
  sliderRepContinuity->SetLabelHeight(labelHeight);
  sliderRepContinuity->SetEndCapLength(tubeWidth*1.5);
  sliderRepContinuity->SetSliderWidth(tubeWidth*1.5);
  sliderRepContinuity->GetSliderProperty()->SetColor(0.0, 0.0, 0.0);
  sliderRepContinuity->BuildRepresentation();

  widget->SetRepresentation(sliderRepContinuity);
  widget->SetAnimationModeToAnimate();
  widget->SetNumberOfAnimationSteps(10);
  widget->SetInteractor(interactor);
  widget->EnabledOn();

  vtkSmartPointer<SliderCallbackContinuity> callbackContinuity =
    vtkSmartPointer<SliderCallbackContinuity>::New();
  callbackContinuity->ParametricSpline = parametricSpline;
  callbackContinuity->ParametricSource = parametricSource;

  widget->AddObserver(vtkCommand::InteractionEvent,callbackContinuity);
}

class SliderCallbackBias : public vtkCommand
{
public:
  static SliderCallbackBias *New()
  {
    return new SliderCallbackBias;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D *>(sliderWidget->GetRepresentation())->GetValue();
    dynamic_cast<vtkKochanekSpline*>(this->ParametricSpline->GetXSpline())->SetDefaultBias(value);
    dynamic_cast<vtkKochanekSpline*>(this->ParametricSpline->GetYSpline())->SetDefaultBias(value);
    dynamic_cast<vtkKochanekSpline*>(this->ParametricSpline->GetZSpline())->SetDefaultBias(value);
    ParametricSource->Modified();
    ParametricSource->Update();
  }
  SliderCallbackBias():ParametricSource(0), ParametricSpline(0) {}
  vtkParametricSpline *ParametricSpline;
  vtkParametricFunctionSource *ParametricSource;
};

void
MakeBiasWidget(vtkSmartPointer<vtkSliderWidget> &widget,
                  vtkSmartPointer<vtkParametricFunctionSource> &parametricSource,
                  vtkSmartPointer<vtkParametricSpline> &parametricSpline,
                  vtkSmartPointer<vtkRenderer> &renderer,
                  vtkSmartPointer<vtkRenderWindowInteractor> &interactor)
{
  // Setup a slider widget for each varying parameter
  double tubeWidth(.005);
  double sliderLength(.02);
  double titleHeight(.02);
  double labelHeight(.02);

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRepBias =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepBias->SetRenderer(renderer);

  sliderRepBias->SetMinimumValue(-1.0);
  sliderRepBias->SetMaximumValue(1.0);
  sliderRepBias->SetValue(dynamic_cast<vtkKochanekSpline*>(parametricSpline->GetXSpline())->GetDefaultBias());
  sliderRepBias->SetTitleText("Bias");
  sliderRepBias->SetRenderer(renderer);
  sliderRepBias->GetPoint1Coordinate()->SetValue(0.7, 0.1);
  sliderRepBias->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedViewport();
  sliderRepBias->GetPoint2Coordinate()->SetValue(0.9, 0.1);
  sliderRepBias->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedViewport();

  sliderRepBias->SetTubeWidth(tubeWidth);
  sliderRepBias->SetSliderLength(sliderLength);
  sliderRepBias->SetTitleHeight(titleHeight);
  sliderRepBias->SetLabelHeight(labelHeight);
  sliderRepBias->SetEndCapLength(tubeWidth*1.5);
  sliderRepBias->SetSliderWidth(tubeWidth*1.5);
  sliderRepBias->GetSliderProperty()->SetColor(0.0, 0.0, 0.0);
  sliderRepBias->BuildRepresentation();

  widget->SetRepresentation(sliderRepBias);
  widget->SetAnimationModeToAnimate();
  widget->SetNumberOfAnimationSteps(10);
  widget->SetInteractor(interactor);
  widget->EnabledOn();

  vtkSmartPointer<SliderCallbackBias> callbackBias =
    vtkSmartPointer<SliderCallbackBias>::New();
  callbackBias->ParametricSpline = parametricSpline;
  callbackBias->ParametricSource = parametricSource;

  widget->AddObserver(vtkCommand::InteractionEvent,callbackBias);
}
}
