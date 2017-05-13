[VTKExamples](/home/)/[Cxx](/Cxx)/Widgets/TextWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Widgets/TestTextWidget.png?raw=true" width="256" />

### Description
:''See also: []([../../Visualization/DrawText])''

**TextWidget.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkTextWidget.h>
#include <vtkTextActor.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkTextRepresentation.h>
#include <vtkCoordinate.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>

int main(int, char *[])
{
  // Create the RenderWindow, Renderer and both Actors
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Create a test pipeline
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create the widget
  vtkSmartPointer<vtkTextActor> textActor =
    vtkSmartPointer<vtkTextActor>::New();
  textActor->SetInput("This is a test");
  textActor->GetTextProperty()->SetColor( 0.0, 1.0, 0.0 );

  vtkSmartPointer<vtkTextWidget> textWidget =
    vtkSmartPointer<vtkTextWidget>::New();

  vtkSmartPointer<vtkTextRepresentation> textRepresentation =
    vtkSmartPointer<vtkTextRepresentation>::New();
  textRepresentation->GetPositionCoordinate()->SetValue( .15, .15 );
  textRepresentation->GetPosition2Coordinate()->SetValue( .7, .2 );
  textWidget ->SetRepresentation( textRepresentation );

  textWidget->SetInteractor(interactor);
  textWidget->SetTextActor(textActor);
  textWidget->SelectableOff();

  // Add the actors to the renderer, set the background and size
  renderer->AddActor(actor);
  renderer->SetBackground(0.1, 0.2, 0.4);
  renderWindow->SetSize(300, 300);

  interactor->Initialize();
  renderWindow->Render();
  textWidget->On();
  renderWindow->Render();

  interactor->Start();
  
  return EXIT_SUCCESS;

}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TextWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TextWidget MACOSX_BUNDLE TextWidget.cxx)
 
target_link_libraries(TextWidget ${VTK_LIBRARIES})
```

**Download and Build TextWidget**

Click [here to download TextWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TextWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball TextWidget.tar* has been downloaded and extracted,
```
cd TextWidget/build 
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
./TextWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

