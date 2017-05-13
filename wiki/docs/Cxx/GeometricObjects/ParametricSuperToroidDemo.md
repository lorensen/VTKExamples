[VTKExamples](/index/)/[Cxx](/Cxx)/GeometricObjects/ParametricSuperToroidDemo

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestParametricSuperToroidDemo.png?raw=true" width="256" />

**ParametricSuperToroidDemo.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkParametricSuperToroid.h>
#include <vtkParametricFunctionSource.h>

#include <vtkCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMath.h>

#include <vtkCommand.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>

// These callbacks do the actual work.
// Callbacks for the interactions
class SliderCallbackN1 : public vtkCommand
{
public:
  static SliderCallbackN1 *New()
  {
    return new SliderCallbackN1;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D *>(sliderWidget->GetRepresentation())->GetValue();
    this->SuperToroid->SetN1(value);
  }
  SliderCallbackN1():SuperToroid(0) {}
  vtkParametricSuperToroid *SuperToroid;
};

class SliderCallbackN2 : public vtkCommand
{
public:
  static SliderCallbackN2 *New()
  {
    return new SliderCallbackN2;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation2D *>(sliderWidget->GetRepresentation())->GetValue();
    this->SuperToroid->SetN2(value);
  }
  SliderCallbackN2():SuperToroid(0) {}
  vtkParametricSuperToroid *SuperToroid;
};

int main(int, char *[])
{
  vtkSmartPointer<vtkParametricSuperToroid> surface =
    vtkSmartPointer<vtkParametricSuperToroid>::New();
  vtkSmartPointer<vtkParametricFunctionSource> source =
    vtkSmartPointer<vtkParametricFunctionSource>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();

  vtkSmartPointer<vtkProperty> backProperty =
    vtkSmartPointer<vtkProperty>::New();
  backProperty->SetColor(1.0000, 0.3882, 0.2784);

  // Create a parametric function source, renderer, mapper, and actor
  source->SetParametricFunction(surface);

  mapper->SetInputConnection(source->GetOutputPort());

  actor->SetMapper(mapper);
  actor->SetBackfaceProperty(backProperty);
  actor->GetProperty()->SetDiffuseColor(0.8900, 0.8100, 0.3400);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640,480);
  renderer->AddActor(actor);
  renderer->SetBackground(.2, .3, .4);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(-30);
  renderer->GetActiveCamera()->Zoom(0.9);
  renderer->ResetCameraClippingRange();

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Setup a slider widget for each varying parameter
  double tubeWidth(.004);
  double sliderLength(.004);
  double titleHeight(.02);
  double labelHeight(.02);

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRepN1 =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepN1->SetMinimumValue(0.0);
  sliderRepN1->SetMaximumValue(4.0);
  sliderRepN1->SetValue(1.0);
  sliderRepN1->SetTitleText("Z squareness");

  sliderRepN1->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRepN1->GetPoint1Coordinate()->SetValue(.1, .1);
  sliderRepN1->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRepN1->GetPoint2Coordinate()->SetValue(.9, .1);

  sliderRepN1->SetTubeWidth(tubeWidth);
  sliderRepN1->SetSliderLength(sliderLength);
  sliderRepN1->SetTitleHeight(titleHeight);
  sliderRepN1->SetLabelHeight(labelHeight);

  vtkSmartPointer<vtkSliderWidget> sliderWidgetN1 =
    vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidgetN1->SetInteractor(interactor);
  sliderWidgetN1->SetRepresentation(sliderRepN1);
  sliderWidgetN1->SetAnimationModeToAnimate();
  sliderWidgetN1->EnabledOn();

  vtkSmartPointer<SliderCallbackN1> callbackN1 =
    vtkSmartPointer<SliderCallbackN1>::New();
  callbackN1->SuperToroid = surface;

  sliderWidgetN1->AddObserver(vtkCommand::InteractionEvent,callbackN1);

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRepN2 =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepN2->SetMinimumValue(0.0001);
  sliderRepN2->SetMaximumValue(4.0);
  sliderRepN2->SetValue(1.0);
  sliderRepN2->SetTitleText("XY squareness");

  sliderRepN2->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRepN2->GetPoint1Coordinate()->SetValue(.1, .9);
  sliderRepN2->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRepN2->GetPoint2Coordinate()->SetValue(.9, .9);

  sliderRepN2->SetTubeWidth(tubeWidth);
  sliderRepN2->SetSliderLength(sliderLength);
  sliderRepN2->SetTitleHeight(titleHeight);
  sliderRepN2->SetLabelHeight(labelHeight);

  vtkSmartPointer<vtkSliderWidget> sliderWidgetN2 =
    vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidgetN2->SetInteractor(interactor);
  sliderWidgetN2->SetRepresentation(sliderRepN2);
  sliderWidgetN2->SetAnimationModeToAnimate();
  sliderWidgetN2->EnabledOn();

  vtkSmartPointer<SliderCallbackN2> callbackN2 =
    vtkSmartPointer<SliderCallbackN2>::New();
  callbackN2->SuperToroid = surface;

  sliderWidgetN2->AddObserver(vtkCommand::InteractionEvent,callbackN2);

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRepMinimumV =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();

  sliderRepN1->SetMinimumValue(.0001);
  sliderRepMinimumV->SetMaximumValue(.9999*vtkMath::Pi());
  sliderRepMinimumV->SetValue(.0001);
  sliderRepMinimumV->SetTitleText("V min");

  sliderRepMinimumV->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRepMinimumV->GetPoint1Coordinate()->SetValue(.1, .1);
  sliderRepMinimumV->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRepMinimumV->GetPoint2Coordinate()->SetValue(.1, .9);

  sliderRepMinimumV->SetTubeWidth(tubeWidth);
  sliderRepMinimumV->SetSliderLength(sliderLength);
  sliderRepMinimumV->SetTitleHeight(titleHeight);
  sliderRepMinimumV->SetLabelHeight(labelHeight);

  surface->SetN1(1.0);
  surface->SetN2(1.0);

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(-30);
  renderer->GetActiveCamera()->Zoom(0.9);
  renderer->ResetCameraClippingRange();
  renderWindow->Render();

  interactor->Initialize();

  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ParametricSuperToroidDemo)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ParametricSuperToroidDemo MACOSX_BUNDLE ParametricSuperToroidDemo.cxx)
 
target_link_libraries(ParametricSuperToroidDemo ${VTK_LIBRARIES})
```

**Download and Build ParametricSuperToroidDemo**

Click [here to download ParametricSuperToroidDemo](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ParametricSuperToroidDemo.tar) and its *CMakeLists.txt* file.
Once the *tarball ParametricSuperToroidDemo.tar* has been downloaded and extracted,
```
cd ParametricSuperToroidDemo/build 
```
If VTK is installed:
```
cmake ..
```
If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build:
```
cmake -DVTK_DIR:PATH=/home/me/vtk_build ..
```
Build the project:
```
make
```
and run it:
```
./ParametricSuperToroidDemo
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

