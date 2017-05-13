[VTKExamples](Home)/[Cxx](Cxx)/GeometricObjects/Circle

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/GeometricObjects/TestCircle.png" width="256" />

### Description
A circle is simply the limiting case of a regular polygon. We use vtkRegularPolygonSource with a large number of Sides to approximate a circle.

**Circle.cxx**
```c++
// Classes specific to this example
#include <vtkRegularPolygonSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
// Generic VTK pipeline elements
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
// Auxiliary class
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  // Create a circle
  vtkSmartPointer<vtkRegularPolygonSource> polygonSource =
    vtkSmartPointer<vtkRegularPolygonSource>::New();
  
  //polygonSource->GeneratePolygonOff(); // Uncomment this line to generate only the outline of the circle
  polygonSource->SetNumberOfSides(50);
  polygonSource->SetRadius(5);
  polygonSource->SetCenter(0, 0, 0);
  
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(polygonSource->GetOutputPort());;
  
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(.3,.3,.5); // Background color purple
  
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Circle)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Circle MACOSX_BUNDLE Circle.cxx)
 
target_link_libraries(Circle ${VTK_LIBRARIES})
```

**Download and Build Circle**

Click [here to download Circle](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Circle.tar) and its *CMakeLists.txt* file.
Once the *tarball Circle.tar* has been downloaded and extracted,
```
cd Circle/build 
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
./Circle
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

