[VTKExamples](/home/)/[Cxx](/Cxx)/Widgets/DistanceWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Widgets/TestDistanceWidget.png?raw=true" width="256" />

### Description
* Contributed by Arnaud Gelas


Click two points to see the distance between them.

**DistanceWidget.cxx**
```c++
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkDistanceWidget.h>
#include <vtkDistanceRepresentation.h>

int main(int, char *[])
{
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

  vtkSmartPointer<vtkDistanceWidget> distanceWidget =
    vtkSmartPointer<vtkDistanceWidget>::New();
  distanceWidget->SetInteractor(renderWindowInteractor);
  distanceWidget->CreateDefaultRepresentation();
  static_cast<vtkDistanceRepresentation *>(distanceWidget->GetRepresentation())
    ->SetLabelFormat("%-#6.3g mm");
  
  // Render an image (lights and cameras are created automatically)
  renderWindow->Render();
  
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  distanceWidget->On();
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DistanceWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DistanceWidget MACOSX_BUNDLE DistanceWidget.cxx)
 
target_link_libraries(DistanceWidget ${VTK_LIBRARIES})
```

**Download and Build DistanceWidget**

Click [here to download DistanceWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DistanceWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball DistanceWidget.tar* has been downloaded and extracted,
```
cd DistanceWidget/build 
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
./DistanceWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

