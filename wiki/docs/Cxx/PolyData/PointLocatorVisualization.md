[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/PointLocatorVisualization

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestPointLocatorVisualization.png?raw=true" width="256" />

### Description
The idea of this example is to navigate levels of a uniform spatial tree (vtkPointLocator) using a slider. 

Note: it is not desirable to have PointsPerBucket set "too small". This is because at some point, refining a bucket will result in each cell in that bucket to also be in the bucket's children.  This only wastes memory and computation.  The value that is "too small" is dependent on the grid but in general a value between 10 and 100 should work well (the default value is 25).

**PointLocatorVisualization.cxx**
```c++
#include <vtkVersion.h>
#include <vtkPointSource.h>
#include <vtkSphereSource.h>
#include <vtkPointLocator.h>
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
#include <vtkCommand.h>
#include <vtkWidgetEvent.h>
#include <vtkCallbackCommand.h>
#include <vtkWidgetEventTranslator.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkProperty.h>

#include <vtkMath.h>

class vtkSliderCallback : public vtkCommand
{
public:
  static vtkSliderCallback *New()
  {
    return new vtkSliderCallback;
  }
  vtkSliderCallback():PointLocator(0), Level(0), PolyData(0), Renderer(0){}

  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    this->Level = vtkMath::Round(static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue());
    this->PointLocator->GenerateRepresentation(this->Level, this->PolyData);
    this->Renderer->Render();
  }

  vtkPointLocator* PointLocator;
  int Level;
  vtkPolyData* PolyData;
  vtkRenderer* Renderer;
};

int main (int, char *[])
{
  vtkSmartPointer<vtkSphereSource> inputSource =
    vtkSmartPointer<vtkSphereSource>::New();
  inputSource->SetPhiResolution(10);
  inputSource->SetThetaResolution(10);
  inputSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> pointsMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pointsMapper->SetInputConnection(inputSource->GetOutputPort());

  vtkSmartPointer<vtkActor> pointsActor =
    vtkSmartPointer<vtkActor>::New();
  pointsActor->SetMapper(pointsMapper);
  pointsActor->GetProperty()->SetInterpolationToFlat();

  // Create the tree
  vtkSmartPointer<vtkPointLocator> pointLocator =
    vtkSmartPointer<vtkPointLocator>::New();
  pointLocator->SetDataSet(inputSource->GetOutput());
  pointLocator->BuildLocator();

  // Initialize the representation
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  pointLocator->GenerateRepresentation(0, polydata);

  vtkSmartPointer<vtkPolyDataMapper> locatorTreeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  locatorTreeMapper->SetInputConnection(polydata->GetProducerPort());
#else
  locatorTreeMapper->SetInputData(polydata);
#endif

  vtkSmartPointer<vtkActor> locatorTreeActor =
    vtkSmartPointer<vtkActor>::New();
  locatorTreeActor->SetMapper(locatorTreeMapper);
  locatorTreeActor->GetProperty()->SetInterpolationToFlat();
  locatorTreeActor->GetProperty()->SetRepresentationToWireframe();

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
  renderer->AddActor(pointsActor);
  renderer->AddActor(locatorTreeActor);

  // Render an image (lights and cameras are created automatically)
  renderWindow->Render();

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRep =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();
  sliderRep->SetMinimumValue(0);
  sliderRep->SetMaximumValue(pointLocator->GetLevel());
  sliderRep->SetValue(0);
  sliderRep->SetTitleText("MaxPointsPerRegion");
  sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRep->GetPoint1Coordinate()->SetValue(.2, .2);
  sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRep->GetPoint2Coordinate()->SetValue(.8, .2);
  sliderRep->SetSliderLength(0.075);
  sliderRep->SetSliderWidth(0.05);
  sliderRep->SetEndCapLength(0.05);

  vtkSmartPointer<vtkSliderWidget> sliderWidget =
    vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidget->SetInteractor(renderWindowInteractor);
  sliderWidget->SetRepresentation(sliderRep);
  sliderWidget->SetAnimationModeToAnimate();
  sliderWidget->EnabledOn();

  vtkSmartPointer<vtkSliderCallback> callback =
    vtkSmartPointer<vtkSliderCallback>::New();
  callback->PointLocator = pointLocator;
  callback->PolyData = polydata;
  callback->Renderer = renderer;

  sliderWidget->AddObserver(vtkCommand::InteractionEvent,callback);

  renderWindowInteractor->Initialize();
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PointLocatorVisualization)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PointLocatorVisualization MACOSX_BUNDLE PointLocatorVisualization.cxx)
 
target_link_libraries(PointLocatorVisualization ${VTK_LIBRARIES})
```

**Download and Build PointLocatorVisualization**

Click [here to download PointLocatorVisualization](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PointLocatorVisualization.tar) and its *CMakeLists.txt* file.
Once the *tarball PointLocatorVisualization.tar* has been downloaded and extracted,
```
cd PointLocatorVisualization/build 
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
./PointLocatorVisualization
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

