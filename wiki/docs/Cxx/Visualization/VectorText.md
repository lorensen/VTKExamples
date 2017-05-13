[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/VectorText

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestVectorText.png?raw=true" width="256" />

### Description
This example displays a red "Hello" in 3D space. For an example where the text always faces the camera, see []([../Follower]).

If you want to draw text in 2D rather than 3D, take a look at [or [[../../Widgets/TextWidget]]([../DrawText]]).

**VectorText.cxx**
```c++
#include <vtkVectorText.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>

int main(int, char *[])
{
  // Create text
  vtkSmartPointer<vtkVectorText> textSource = 
    vtkSmartPointer<vtkVectorText>::New();
  textSource->SetText("Hello");
  textSource->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(textSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(1.0, 0.0, 0.0);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(VectorText)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VectorText MACOSX_BUNDLE VectorText.cxx)
 
target_link_libraries(VectorText ${VTK_LIBRARIES})
```

**Download and Build VectorText**

Click [here to download VectorText](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VectorText.tar) and its *CMakeLists.txt* file.
Once the *tarball VectorText.tar* has been downloaded and extracted,
```
cd VectorText/build 
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
./VectorText
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

