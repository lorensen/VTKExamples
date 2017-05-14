[VTKExamples](/index/)/[Cxx](/Cxx)/Widgets/SplineWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Widgets/TestSplineWidget.png?raw=true" width="256" />

**SplineWidget.cxx**
```c++
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSplineWidget2.h>

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

  vtkSmartPointer<vtkSplineWidget2> splineWidget = 
    vtkSmartPointer<vtkSplineWidget2>::New();
  splineWidget->SetInteractor(renderWindowInteractor);
  
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  splineWidget->On();
  renderer->ResetCamera();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SplineWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SplineWidget MACOSX_BUNDLE SplineWidget.cxx)
 
target_link_libraries(SplineWidget ${VTK_LIBRARIES})
```

**Download and Build SplineWidget**

Click [here to download SplineWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SplineWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball SplineWidget.tar* has been downloaded and extracted,
```
cd SplineWidget/build 
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
./SplineWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

