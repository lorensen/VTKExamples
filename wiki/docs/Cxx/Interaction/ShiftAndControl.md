[VTKExamples](/index/)/[Cxx](/Cxx)/Interaction/ShiftAndControl

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Interaction/TestShiftAndControl.png?raw=true" width="256" />

### Description
Some parts of this example are currently broken.

GetAltKey() does not work? The window moves instead.

This example demonstrates how to "control+click" and "shift+click" an actor.

**ShiftAndControl.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkObjectFactory.h>

class MouseInteractorStyleShiftAndControl : public vtkInteractorStyleTrackballActor
{
  public:
    static MouseInteractorStyleShiftAndControl* New();

    virtual void OnLeftButtonDown()
    {
      if(this->Interactor->GetShiftKey())
      {
        std::cout << "Shift held. ";
      }

      if(this->Interactor->GetControlKey())
      {
        std::cout << "Control held. ";
      }

        /* this doesn't work ??? */
      if(this->Interactor->GetAltKey())
      {
        std::cout << "Alt held. ";
      }

      std::cout << "Pressed left mouse button." << std::endl;

      // Forward events
      vtkInteractorStyleTrackballActor::OnLeftButtonDown();
    }

};

vtkStandardNewMacro(MouseInteractorStyleShiftAndControl);

int main (int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

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
  renderer->SetBackground(1,1,1); // Background color white

  // Render
  renderWindow->Render();

  vtkSmartPointer<MouseInteractorStyleShiftAndControl> style =
    vtkSmartPointer<MouseInteractorStyleShiftAndControl>::New();

  renderWindowInteractor->SetInteractorStyle( style );

  // Begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ShiftAndControl)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ShiftAndControl MACOSX_BUNDLE ShiftAndControl.cxx)
 
target_link_libraries(ShiftAndControl ${VTK_LIBRARIES})
```

**Download and Build ShiftAndControl**

Click [here to download ShiftAndControl](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ShiftAndControl.tar) and its *CMakeLists.txt* file.
Once the *tarball ShiftAndControl.tar* has been downloaded and extracted,
```
cd ShiftAndControl/build 
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
./ShiftAndControl
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

