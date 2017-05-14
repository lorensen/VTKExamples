[VTKExamples](/index/)/[Cxx](/Cxx)/Widgets/HoverWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Widgets/TestHoverWidget.png?raw=true" width="256" />

**HoverWidget.cxx**
```c++
#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkHoverWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

class vtkHoverCallback : public vtkCommand
{
  public:
    static vtkHoverCallback *New()
    {
      return new vtkHoverCallback;
    }

    vtkHoverCallback() {}

    virtual void Execute(vtkObject*, unsigned long event, void *vtkNotUsed(calldata))
    {
      switch (event)
      {
        case vtkCommand::TimerEvent:
          std::cout << "TimerEvent -> the mouse stopped moving and the widget hovered" << std::endl;
          break;
        case vtkCommand::EndInteractionEvent:
          std::cout << "EndInteractionEvent -> the mouse started to move" << std::endl;
          break;
      }
    }
};

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

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
  renderer->AddActor(actor);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Create the widget
  vtkSmartPointer<vtkHoverWidget> hoverWidget =
    vtkSmartPointer<vtkHoverWidget>::New();
  hoverWidget->SetInteractor(renderWindowInteractor);
  hoverWidget->SetTimerDuration(1000);

  // Create a callback to listen to the widget's two VTK events
  vtkSmartPointer<vtkHoverCallback> hoverCallback =
    vtkSmartPointer<vtkHoverCallback>::New();
  hoverWidget->AddObserver(vtkCommand::TimerEvent,hoverCallback);
  hoverWidget->AddObserver(vtkCommand::EndInteractionEvent,hoverCallback);

  renderWindow->Render();

  renderWindowInteractor->Initialize();
  renderWindow->Render();
  hoverWidget->On();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(HoverWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(HoverWidget MACOSX_BUNDLE HoverWidget.cxx)
 
target_link_libraries(HoverWidget ${VTK_LIBRARIES})
```

**Download and Build HoverWidget**

Click [here to download HoverWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/HoverWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball HoverWidget.tar* has been downloaded and extracted,
```
cd HoverWidget/build 
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
./HoverWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

