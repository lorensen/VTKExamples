[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/DrawText

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestDrawText.png?raw=true" width="256" />

### Description
This example writes "Hello world" in the bottom left corner of the render window. The text size and color are set. There are many properties that can be set that control how the text is changed when the render window is resized, but they are not covered in this example.

This example draws text in 2D. For an example using 3D text that can be placed on the scene like a regular vtkActor, see [For an example of drawing text, also in 2D, but into a vtkImageData object rather than into the render window, see [[../../Images/ImageText]]([../VectorText]].).

:''See also: []([../../Widgets/TextWidget])''

**DrawText.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter ( 0.0, 0.0, 0.0 );
  sphereSource->SetRadius ( 5.0 );
  sphereSource->Update();

  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInput ( sphereSource->GetOutput() );
#else
  mapper->SetInputData ( sphereSource->GetOutput() );
#endif

  // Create an actor
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper ( mapper );

  // Create a renderer
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground ( 1, 1, 1 ); // Set background color to white
  renderer->AddActor ( actor );

  // Create a render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer ( renderer );

  // Create an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow ( renderWindow );

  // Setup the text and add it to the renderer
  vtkSmartPointer<vtkTextActor> textActor = 
    vtkSmartPointer<vtkTextActor>::New();
  textActor->SetInput ( "Hello world" );
  textActor->SetPosition2 ( 10, 40 );
  textActor->GetTextProperty()->SetFontSize ( 24 );
  textActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
  renderer->AddActor2D ( textActor );
  
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DrawText)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DrawText MACOSX_BUNDLE DrawText.cxx)
 
target_link_libraries(DrawText ${VTK_LIBRARIES})
```

**Download and Build DrawText**

Click [here to download DrawText](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DrawText.tar) and its *CMakeLists.txt* file.
Once the *tarball DrawText.tar* has been downloaded and extracted,
```
cd DrawText/build 
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
./DrawText
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

