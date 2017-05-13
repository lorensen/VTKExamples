[VTKExamples](Home)/[Cxx](Cxx)/Widgets/PlaneWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Widgets/TestPlaneWidget.png" width="256" />

**PlaneWidget.cxx**
```c++
#include <vtkPlaneWidget.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{  
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkPlaneWidget> planeWidget = 
      vtkSmartPointer<vtkPlaneWidget>::New();
  planeWidget->SetInteractor(renderWindowInteractor);
  
  planeWidget->On();

  renderWindowInteractor->Initialize();
  
  renderer->ResetCamera();
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PlaneWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PlaneWidget MACOSX_BUNDLE PlaneWidget.cxx)
 
target_link_libraries(PlaneWidget ${VTK_LIBRARIES})
```

**Download and Build PlaneWidget**

Click [here to download PlaneWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PlaneWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball PlaneWidget.tar* has been downloaded and extracted,
```
cd PlaneWidget/build 
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
./PlaneWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

