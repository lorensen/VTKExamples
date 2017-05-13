[VTKExamples](/home/)/[Cxx](/Cxx)/Picking/HighlightPickedActor

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Picking/TestHighlightPickedActor.png?raw=true" width="256" />

### Description
Click on a sphere to highlight it.

**HighlightPickedActor.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkMath.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkPropPicker.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

// Handle mouse events
class MouseInteractorHighLightActor : public vtkInteractorStyleTrackballCamera
{
public:
  static MouseInteractorHighLightActor* New();
  vtkTypeMacro(MouseInteractorHighLightActor, vtkInteractorStyleTrackballCamera);

  MouseInteractorHighLightActor()
  {
    LastPickedActor = NULL;
    LastPickedProperty = vtkProperty::New();
  }
  virtual ~MouseInteractorHighLightActor()
  {
    LastPickedProperty->Delete();
  }
  virtual void OnLeftButtonDown()
  {
    int* clickPos = this->GetInteractor()->GetEventPosition();

    // Pick from this location.
    vtkSmartPointer<vtkPropPicker>  picker =
      vtkSmartPointer<vtkPropPicker>::New();
    picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

    // If we picked something before, reset its property
    if (this->LastPickedActor)
    {
      this->LastPickedActor->GetProperty()->DeepCopy(this->LastPickedProperty);
    }
    this->LastPickedActor = picker->GetActor();
    if (this->LastPickedActor)
    {
      // Save the property of the picked actor so that we can
      // restore it next time
      this->LastPickedProperty->DeepCopy(this->LastPickedActor->GetProperty());
      // Highlight the picked actor by changing its properties
      this->LastPickedActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
      this->LastPickedActor->GetProperty()->SetDiffuse(1.0);
      this->LastPickedActor->GetProperty()->SetSpecular(0.0);
    }

    // Forward events
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
  }

private:
  vtkActor    *LastPickedActor;
  vtkProperty *LastPickedProperty;
};

vtkStandardNewMacro(MouseInteractorHighLightActor);

// Execute application.
int main(int argc, char *argv[])
{
  int numberOfSpheres = 10;
  if (argc > 1)
  {
    numberOfSpheres = atoi(argv[1]);
  }
  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer ( renderer );

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow ( renderWindow );

  // Set the custom type to use for interaction.
  vtkSmartPointer<MouseInteractorHighLightActor> style =
    vtkSmartPointer<MouseInteractorHighLightActor>::New();
  style->SetDefaultRenderer(renderer);

  renderWindowInteractor->SetInteractorStyle( style );

  for (int i = 0; i < numberOfSpheres; ++i)
  {
    vtkSmartPointer<vtkSphereSource> source =
      vtkSmartPointer<vtkSphereSource>::New();
    double x, y, z, radius;
    x = vtkMath::Random(-5,5);
    y = vtkMath::Random(-5,5);
    z = vtkMath::Random(-5,5);
    radius = vtkMath::Random(.5, 1.0);
    source->SetRadius(radius);
    source->SetCenter(x, y, z);
    source->SetPhiResolution(11);
    source->SetThetaResolution(21);
    vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection ( source->GetOutputPort());
    vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper ( mapper );
    double r, g, b;
    r = vtkMath::Random(.4, 1.0);
    g = vtkMath::Random(.4, 1.0);
    b = vtkMath::Random(.4, 1.0);
    actor->GetProperty()->SetDiffuseColor(r, g, b);
    actor->GetProperty()->SetDiffuse(.8);
    actor->GetProperty()->SetSpecular(.5);
    actor->GetProperty()->SetSpecularColor(1.0,1.0,1.0);
    actor->GetProperty()->SetSpecularPower(30.0);
    renderer->AddActor ( actor );
  }

  renderer->SetBackground ( .3, .4, .5 );

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(HighlightPickedActor)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(HighlightPickedActor MACOSX_BUNDLE HighlightPickedActor.cxx)
 
target_link_libraries(HighlightPickedActor ${VTK_LIBRARIES})
```

**Download and Build HighlightPickedActor**

Click [here to download HighlightPickedActor](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/HighlightPickedActor.tar) and its *CMakeLists.txt* file.
Once the *tarball HighlightPickedActor.tar* has been downloaded and extracted,
```
cd HighlightPickedActor/build 
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
./HighlightPickedActor
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

