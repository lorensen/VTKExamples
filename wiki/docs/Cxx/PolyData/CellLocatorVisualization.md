[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/CellLocatorVisualization

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestCellLocatorVisualization.png?raw=true" width="256" />

### Description
The idea of this example is to navigate levels of a uniform spatial tree (vtkCellLocator) using a slider.

**Note:** it is not desirable to have CellsPerBucket set "too small". This is because at some point, refining a bucket will result in each cell in that bucket to also be in the bucket's children.  This only wastes memory and computation.  The value that is "too small" is dependent on the grid but in general a value between 10 and 100 should work well (the default value is 25).

**CellLocatorVisualization.cxx**
```c++
#include <vtkVersion.h>
#include <vtkPointSource.h>
#include <vtkSphereSource.h>
#include <vtkCellLocator.h>
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
  vtkSliderCallback():CellLocator(0), Level(0), PolyData(0), Renderer(0){}

  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    this->Level = vtkMath::Round(static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue());
    this->CellLocator->GenerateRepresentation(this->Level, this->PolyData);
    this->Renderer->Render();
  }

  vtkCellLocator* CellLocator;
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
  vtkSmartPointer<vtkCellLocator> cellLocator =
    vtkSmartPointer<vtkCellLocator>::New();
  cellLocator->SetDataSet(inputSource->GetOutput());
  cellLocator->BuildLocator();

  // Initialize the representation
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  cellLocator->GenerateRepresentation(0, polydata);

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
  sliderRep->SetMaximumValue(cellLocator->GetLevel());
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
  callback->CellLocator = cellLocator;
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
 
PROJECT(CellLocatorVisualization)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CellLocatorVisualization MACOSX_BUNDLE CellLocatorVisualization.cxx)
 
target_link_libraries(CellLocatorVisualization ${VTK_LIBRARIES})
```

**Download and Build CellLocatorVisualization**

Click [here to download CellLocatorVisualization](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CellLocatorVisualization.tar) and its *CMakeLists.txt* file.
Once the *tarball CellLocatorVisualization.tar* has been downloaded and extracted,
```
cd CellLocatorVisualization/build 
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
./CellLocatorVisualization
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

