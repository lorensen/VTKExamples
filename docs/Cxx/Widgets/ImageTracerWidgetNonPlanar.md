[VTKExamples](/index/)/[Cxx](/Cxx)/Widgets/ImageTracerWidgetNonPlanar

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Widgets/TestImageTracerWidgetNonPlanar.png?raw=true" width="256" />

**ImageTracerWidgetNonPlanar.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkImageTracerWidget.h>
#include <vtkInteractorStyleTrackballCamera.h>

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

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  
  renderWindowInteractor->SetInteractorStyle(style);
  
  vtkSmartPointer<vtkImageTracerWidget> tracerWidget = 
    vtkSmartPointer<vtkImageTracerWidget>::New();
  tracerWidget->SetInteractor(renderWindowInteractor);
  tracerWidget->SetViewProp(actor);
  
  renderWindow->Render();
  
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  tracerWidget->On();
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageTracerWidgetNonPlanar)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageTracerWidgetNonPlanar MACOSX_BUNDLE ImageTracerWidgetNonPlanar.cxx)
 
target_link_libraries(ImageTracerWidgetNonPlanar ${VTK_LIBRARIES})
```

**Download and Build ImageTracerWidgetNonPlanar**

Click [here to download ImageTracerWidgetNonPlanar](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageTracerWidgetNonPlanar.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageTracerWidgetNonPlanar.tar* has been downloaded and extracted,
```
cd ImageTracerWidgetNonPlanar/build 
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
./ImageTracerWidgetNonPlanar
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

