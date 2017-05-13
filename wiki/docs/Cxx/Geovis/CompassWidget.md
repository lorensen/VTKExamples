[VTKExamples](/index/)/[Cxx](/Cxx)/Geovis/CompassWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Geovis/TestCompassWidget.png?raw=true" width="256" />

### Description
This example creates a compass in the top right corner of the window.

**CompassWidget.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkCompassWidget.h>
#include <vtkCompassRepresentation.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleTrackball.h>

int main (int, char *[])
{

  //sphere 1
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(4.0);
    
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  // a renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  
  // Create the widget and its representation
  vtkSmartPointer<vtkCompassRepresentation> compassRepresentation = vtkSmartPointer<vtkCompassRepresentation>::New();
  
  vtkSmartPointer<vtkCompassWidget> compassWidget = 
    vtkSmartPointer<vtkCompassWidget>::New();
  compassWidget->SetInteractor(renderWindowInteractor);
  compassWidget->SetRepresentation(compassRepresentation);
  
  // add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white
  renderWindow->Render();
  compassWidget->EnabledOn();
      
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
      vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();   
  renderWindowInteractor->SetInteractorStyle( style );
  
  // begin interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CompassWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CompassWidget MACOSX_BUNDLE CompassWidget.cxx)
 
target_link_libraries(CompassWidget ${VTK_LIBRARIES})
```

**Download and Build CompassWidget**

Click [here to download CompassWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CompassWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball CompassWidget.tar* has been downloaded and extracted,
```
cd CompassWidget/build 
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
./CompassWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

