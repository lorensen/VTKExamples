#include <vtkSphereSource.h>
#include <vtkTextProperty.h>
#include <vtkProperty2D.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSliderWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkCommand.h>
#include <vtkWidgetEvent.h>
#include <vtkCallbackCommand.h>
#include <vtkWidgetEventTranslator.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkProperty.h>

// This does the actual work.
// Callback for the interaction
class vtkSliderCallback : public vtkCommand
{
public:
  static vtkSliderCallback *New()
  {
    return new vtkSliderCallback;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    this->SphereSource->SetPhiResolution(static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue());
    this->SphereSource->SetThetaResolution(static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue());
  }
  vtkSliderCallback():SphereSource(0) {}
  vtkSphereSource *SphereSource;
};

int main (int, char *[])
{
  // A sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(4.0);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetInterpolationToFlat();

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(actor);

  // Render an image (lights and cameras are created automatically)
  renderWindow->Render();

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRep =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRep->SetMinimumValue(3.0);
  sliderRep->SetMaximumValue(20.0);
  sliderRep->SetValue(5.0);
  sliderRep->SetTitleText("Sphere Resolution");

  // Set color properties:
  // Change the color of the knob that slides
  sliderRep->GetSliderProperty()->SetColor(1,0,0);//red

  // Change the color of the text indicating what the slider controls
  sliderRep->GetTitleProperty()->SetColor(1,0,0);//red

  // Change the color of the text displaying the value
  sliderRep->GetLabelProperty()->SetColor(1,0,0);//red

  // Change the color of the knob when the mouse is held on it
  sliderRep->GetSelectedProperty()->SetColor(0,1,0);//green

  // Change the color of the bar
  sliderRep->GetTubeProperty()->SetColor(1,1,0);//yellow

  // Change the color of the ends of the bar
  sliderRep->GetCapProperty()->SetColor(1,1,0);//yellow

  sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToDisplay();
  sliderRep->GetPoint1Coordinate()->SetValue(40 ,40);
  sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToDisplay();
  sliderRep->GetPoint2Coordinate()->SetValue(100, 40);

  vtkSmartPointer<vtkSliderWidget> sliderWidget =
    vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidget->SetInteractor(renderWindowInteractor);
  sliderWidget->SetRepresentation(sliderRep);
  sliderWidget->SetAnimationModeToAnimate();
  sliderWidget->EnabledOn();

  vtkSmartPointer<vtkSliderCallback> callback =
    vtkSmartPointer<vtkSliderCallback>::New();
  callback->SphereSource = sphereSource;

  sliderWidget->AddObserver(vtkCommand::InteractionEvent,callback);

  renderWindowInteractor->Initialize();
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
