[VTKExamples](/index/)/[Cxx](/Cxx)/GeometricObjects/Axes

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestAxes.png?raw=true" width="256" />

### Description
This example shows how to position an AxesActor in 3D. Notice that position and orientation of the AxesActor is done with a user transform.

See also: [DisplayCoordinateAxes](Cxx/Visualization/DisplayCoordinateAxes).

**Axes.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkAxesActor.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
 
int main (int, char*[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(0.5);

  //create a mapper
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
 
  // create an actor
  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
 
  // a renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
 
  // an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  // add the actors to the scene
  renderer->AddActor(sphereActor);
  renderer->SetBackground(.1,.2,.3); // Background dark blue
 
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->Translate(1.0, 0.0, 0.0);

  vtkSmartPointer<vtkAxesActor> axes =
    vtkSmartPointer<vtkAxesActor>::New();

  // The axes are positioned with a user transform
  axes->SetUserTransform(transform);
 
  // properties of the axes labels can be set as follows
  // this sets the x axis label to red
  // axes->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->SetColor(1,0,0);

  // the actual text of the axis label can be changed:
  // axes->SetXAxisLabelText("test");

  renderer->AddActor(axes);
 
  renderer->ResetCamera();
  renderWindow->Render();
 
  // begin mouse interaction
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Axes)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Axes MACOSX_BUNDLE Axes.cxx)
 
target_link_libraries(Axes ${VTK_LIBRARIES})
```

**Download and Build Axes**

Click [here to download Axes](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Axes.tar) and its *CMakeLists.txt* file.
Once the *tarball Axes.tar* has been downloaded and extracted,
```
cd Axes/build 
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
./Axes
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

