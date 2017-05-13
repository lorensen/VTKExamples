[VTKExamples](/home/)/[Cxx](/Cxx)/DataStructures/ModifiedBSPTree/VisualizeModifiedBSPTree

### Description
Prior to August 20, 2010, the vtkModifiedBSPTree.cxx did not produce a proper data representation. To operate properly, update your vtk source tree.

**VisualizeModifiedBSPTree.cxx**
```c++
#include <vtkVersion.h>
#include <vtkPointSource.h>
#include <vtkSphereSource.h>
#include <vtkModifiedBSPTree.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
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

#include <cmath>

class vtkSliderCallback : public vtkCommand
{
public:
  static vtkSliderCallback *New()
  {
    return new vtkSliderCallback;
  }
  vtkSliderCallback():BSPTree(0), Level(0), PolyData(0),Renderer(0){}

  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    this->Level = vtkMath::Round(static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue());
    this->BSPTree->GenerateRepresentation(this->Level, this->PolyData);
    this->Renderer->Render();
  }

  vtkModifiedBSPTree* BSPTree;
  int Level;
  vtkPolyData* PolyData;
  vtkRenderer* Renderer;
};

int main (int, char *[])
{
  // Create a point cloud - apparently vtkModifiedBSPTree needs cells?
  /*
  vtkSmartPointer<vtkPointSource> inputSource =
    vtkSmartPointer<vtkPointSource>::New();
  inputSource->SetRadius(4);
  inputSource->SetNumberOfPoints(1000);
  inputSource->Update();
  */

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
  vtkSmartPointer<vtkModifiedBSPTree> bspTree =
    vtkSmartPointer<vtkModifiedBSPTree>::New();
  bspTree->SetDataSet(inputSource->GetOutput());
  bspTree->BuildLocator();

  // Initialize the representation
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  bspTree->GenerateRepresentation(0, polydata);

  vtkSmartPointer<vtkPolyDataMapper> bspTreeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  bspTreeMapper->SetInputConnection(polydata->GetProducerPort());
#else
  bspTreeMapper->SetInputData(polydata);
#endif

  vtkSmartPointer<vtkActor> bspTreeActor =
    vtkSmartPointer<vtkActor>::New();
  bspTreeActor->SetMapper(bspTreeMapper);
  bspTreeActor->GetProperty()->SetInterpolationToFlat();
  bspTreeActor->GetProperty()->SetRepresentationToWireframe();

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
  renderer->AddActor(bspTreeActor);

  // Render an image (lights and cameras are created automatically)
  renderWindow->Render();

  vtkSmartPointer<vtkSliderRepresentation2D> sliderRep =
    vtkSmartPointer<vtkSliderRepresentation2D>::New();
  sliderRep->SetMinimumValue(0);
  sliderRep->SetMaximumValue(bspTree->GetLevel());
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
  callback->BSPTree = bspTree;
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
 
PROJECT(VisualizeModifiedBSPTree)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VisualizeModifiedBSPTree MACOSX_BUNDLE VisualizeModifiedBSPTree.cxx)
 
target_link_libraries(VisualizeModifiedBSPTree ${VTK_LIBRARIES})
```

**Download and Build VisualizeModifiedBSPTree**

Click [here to download VisualizeModifiedBSPTree](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VisualizeModifiedBSPTree.tar) and its *CMakeLists.txt* file.
Once the *tarball VisualizeModifiedBSPTree.tar* has been downloaded and extracted,
```
cd VisualizeModifiedBSPTree/build 
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
./VisualizeModifiedBSPTree
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

