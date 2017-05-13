[VTKExamples](/home/)/[Cxx](/Cxx)/DataStructures/OctreeVisualize

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/DataStructures/TestOctreeVisualize.png?raw=true" width="256" />

**OctreeVisualize.cxx**
```c++
#include <vtkVersion.h>
#include <vtkPointSource.h>
#include <vtkOctreePointLocator.h>
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
#include <vtkMath.h>

#include <cmath>

class vtkSliderCallback : public vtkCommand
{
public:
  static vtkSliderCallback *New()
  {
    return new vtkSliderCallback;
  }
  vtkSliderCallback():Octree(0), Level(0), PolyData(0), Renderer(0){}

  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    this->Level = vtkMath::Round(static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue());

    this->Octree->GenerateRepresentation(this->Level, this->PolyData);
    this->Renderer->Render();
  }

  vtkOctreePointLocator* Octree;
  int Level;
  vtkPolyData* PolyData;
  vtkRenderer* Renderer;
};

int main (int, char *[])
{
  // Create a point cloud
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetRadius(4);
  pointSource->SetNumberOfPoints(1000);
  pointSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> pointsMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pointsMapper->SetInputConnection(pointSource->GetOutputPort());

  vtkSmartPointer<vtkActor> pointsActor =
    vtkSmartPointer<vtkActor>::New();
  pointsActor->SetMapper(pointsMapper);
  pointsActor->GetProperty()->SetInterpolationToFlat();

  // Create the tree
  vtkSmartPointer<vtkOctreePointLocator> octree =
    vtkSmartPointer<vtkOctreePointLocator>::New();
  octree->SetDataSet(pointSource->GetOutput());
  octree->BuildLocator();

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  octree->GenerateRepresentation(0, polydata);

  vtkSmartPointer<vtkPolyDataMapper> octreeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  octreeMapper->SetInputConnection(polydata->GetProducerPort());
#else
  octreeMapper->SetInputData(polydata);
#endif

  vtkSmartPointer<vtkActor> octreeActor =
    vtkSmartPointer<vtkActor>::New();
  octreeActor->SetMapper(octreeMapper);
  octreeActor->GetProperty()->SetInterpolationToFlat();
  octreeActor->GetProperty()->SetRepresentationToWireframe();

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
  renderer->AddActor(octreeActor);

  // Render an image (lights and cameras are created automatically)
  renderWindow->Render();

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRep =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();
  sliderRep->SetMinimumValue(0);
  sliderRep->SetMaximumValue(octree->GetLevel());
  sliderRep->SetValue(0);
  sliderRep->SetTitleText("Level");
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
  callback->Octree = octree;
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
 
PROJECT(OctreeVisualize)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(OctreeVisualize MACOSX_BUNDLE OctreeVisualize.cxx)
 
target_link_libraries(OctreeVisualize ${VTK_LIBRARIES})
```

**Download and Build OctreeVisualize**

Click [here to download OctreeVisualize](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/OctreeVisualize.tar) and its *CMakeLists.txt* file.
Once the *tarball OctreeVisualize.tar* has been downloaded and extracted,
```
cd OctreeVisualize/build 
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
./OctreeVisualize
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

