[VTKExamples](Home)/[Cxx](Cxx)/Widgets/AffineWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Widgets/TestAffineWidget.png" width="256" />

### Description
This example demonstrates use of a vtkAffineWidget to apply transforms to a 3D prop in the x-y plane.

**AffineWidget.cxx**
```c++
#include <vtkActor.h>
#include <vtkAffineRepresentation2D.h>
#include <vtkAffineWidget.h>
#include <vtkAppendPolyData.h>
#include <vtkCommand.h>
#include <vtkInteractorStyleSwitch.h>
#include <vtkPlaneSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTransform.h>

class vtkAffineCallback : public vtkCommand
{
public:
  static vtkAffineCallback *New()
    { return new vtkAffineCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*);
  vtkAffineCallback():Actor(0),AffineRep(0)
  {
      this->Transform = vtkTransform::New();
  }
  ~vtkAffineCallback()
  {
      this->Transform->Delete();
  }
  vtkActor *Actor;
  vtkAffineRepresentation2D *AffineRep;
  vtkTransform *Transform;
};

void vtkAffineCallback::Execute(vtkObject*, unsigned long vtkNotUsed(event), void*)
{
  this->AffineRep->GetTransform(this->Transform);
  this->Actor->SetUserTransform(this->Transform);
}

int main(int, char *[])
{
  // Create two spheres: a larger one and a smaller one on top of the larger one
  // to show a reference point while rotating
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkSphereSource> sphereSource2 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetRadius(0.075);
  sphereSource2->SetCenter(0,0.5,0);
  sphereSource2->Update();

  // Append the two spheres into one vtkPolyData
  vtkSmartPointer<vtkAppendPolyData> append =
    vtkSmartPointer<vtkAppendPolyData>::New();
  append->AddInputConnection(sphereSource->GetOutputPort());
  append->AddInputConnection(sphereSource2->GetOutputPort());

  // Create a plane centered over the larger sphere with 4x4 sub sections
  vtkSmartPointer<vtkPlaneSource> planeSource =
    vtkSmartPointer<vtkPlaneSource>::New();
  planeSource->SetXResolution(4);
  planeSource->SetYResolution(4);
  planeSource->SetOrigin(-1,-1,0);
  planeSource->SetPoint1(1,-1,0);
  planeSource->SetPoint2(-1,1,0);

  // Create a mapper and actor for the plane: show it as a wireframe
  vtkSmartPointer<vtkPolyDataMapper> planeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  planeMapper->SetInputConnection(planeSource->GetOutputPort());
  vtkSmartPointer<vtkActor> planeActor =
    vtkSmartPointer<vtkActor>::New();
  planeActor->SetMapper(planeMapper);
  planeActor->GetProperty()->SetRepresentationToWireframe();
  planeActor->GetProperty()->SetColor(1,0,0);

  // Create a mapper and actor for the spheres
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(append->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create a renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderer->AddActor(actor);
  renderer->AddActor(planeActor);
  renderer->GradientBackgroundOn();
  renderer->SetBackground(1,1,1);
  renderer->SetBackground2(0,0,1);

  // Create an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  vtkInteractorStyleSwitch::SafeDownCast(
    renderWindowInteractor->GetInteractorStyle())->SetCurrentStyleToTrackballCamera();

  // Create an affine widget to manipulate the actor
  // the widget currently only has a 2D representation and therefore applies transforms in the X-Y plane only
  vtkSmartPointer<vtkAffineWidget> affineWidget =
    vtkSmartPointer<vtkAffineWidget>::New();
  affineWidget->SetInteractor(renderWindowInteractor);
  affineWidget->CreateDefaultRepresentation();
  vtkAffineRepresentation2D::SafeDownCast(affineWidget->GetRepresentation())->PlaceWidget(actor->GetBounds());

  vtkSmartPointer<vtkAffineCallback> affineCallback =
      vtkSmartPointer<vtkAffineCallback>::New();
  affineCallback->Actor = actor;
  affineCallback->AffineRep = vtkAffineRepresentation2D::SafeDownCast(affineWidget->GetRepresentation());

  affineWidget->AddObserver(vtkCommand::InteractionEvent,affineCallback);
  affineWidget->AddObserver(vtkCommand::EndInteractionEvent,affineCallback);

  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  affineWidget->On();

  // begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(AffineWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(AffineWidget MACOSX_BUNDLE AffineWidget.cxx)
 
target_link_libraries(AffineWidget ${VTK_LIBRARIES})
```

**Download and Build AffineWidget**

Click [here to download AffineWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/AffineWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball AffineWidget.tar* has been downloaded and extracted,
```
cd AffineWidget/build 
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
./AffineWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

