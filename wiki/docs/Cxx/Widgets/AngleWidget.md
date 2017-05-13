[VTKExamples](Home)/[Cxx](Cxx)/Widgets/AngleWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Widgets/TestAngleWidget.png" width="256" />

### Description
Click three points to create an angle. You can then drag the points around.

**AngleWidget.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkAngleWidget.h>

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

  vtkSmartPointer<vtkAngleWidget> angleWidget = 
    vtkSmartPointer<vtkAngleWidget>::New();
  angleWidget->SetInteractor(renderWindowInteractor);
  angleWidget->CreateDefaultRepresentation();
  
  // Render
  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  angleWidget->On();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(AngleWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(AngleWidget MACOSX_BUNDLE AngleWidget.cxx)
 
target_link_libraries(AngleWidget ${VTK_LIBRARIES})
```

**Download and Build AngleWidget**

Click [here to download AngleWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/AngleWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball AngleWidget.tar* has been downloaded and extracted,
```
cd AngleWidget/build 
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
./AngleWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

