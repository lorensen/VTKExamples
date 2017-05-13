[VTKExamples](Home)/[Cxx](Cxx)/Widgets/CaptionWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Widgets/TestCaptionWidget.png" width="256" />

**CaptionWidget.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkCaptionWidget.h>
#include <vtkCaptionRepresentation.h>
#include <vtkCaptionActor2D.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>

int main(int, char *[])
{
  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
    
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
  
  // Create the widget and its representation
  vtkSmartPointer<vtkCaptionRepresentation> captionRepresentation = 
    vtkSmartPointer<vtkCaptionRepresentation>::New();
  captionRepresentation->GetCaptionActor2D()->SetCaption("Test caption");
  captionRepresentation->GetCaptionActor2D()->GetTextActor()->GetTextProperty()->SetFontSize(100);
  
  double pos[3] = {.5,0,0};
  captionRepresentation->SetAnchorPosition(pos);
  
  vtkSmartPointer<vtkCaptionWidget> captionWidget = 
    vtkSmartPointer<vtkCaptionWidget>::New();
  captionWidget->SetInteractor(renderWindowInteractor);
  captionWidget->SetRepresentation(captionRepresentation);
  
  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,0,0);

  renderWindow->Render();
  captionWidget->On();
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CaptionWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CaptionWidget MACOSX_BUNDLE CaptionWidget.cxx)
 
target_link_libraries(CaptionWidget ${VTK_LIBRARIES})
```

**Download and Build CaptionWidget**

Click [here to download CaptionWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CaptionWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball CaptionWidget.tar* has been downloaded and extracted,
```
cd CaptionWidget/build 
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
./CaptionWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

