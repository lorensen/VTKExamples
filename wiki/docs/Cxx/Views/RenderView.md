[VTKExamples](/home/)/[Cxx](/Cxx)/Views/RenderView

### Description
Here is a little bit easier way to get your objects to appear on the screen.

'''NOTE: This examples requires the Views library (which requires the InfoVis and Rendering libraries).'''

**RenderView.cxx**
```c++
#include <vtkRenderView.h>
#include <vtkSphereSource.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderView> renderView =
    vtkSmartPointer<vtkRenderView>::New();
  renderView->SetInteractionMode(vtkRenderView::INTERACTION_MODE_3D);
  renderView->GetRenderer()->AddActor(actor);
  renderView->Update();

  renderView->ResetCamera();
  renderView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RenderView)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RenderView MACOSX_BUNDLE RenderView.cxx)
 
target_link_libraries(RenderView ${VTK_LIBRARIES})
```

**Download and Build RenderView**

Click [here to download RenderView](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RenderView.tar) and its *CMakeLists.txt* file.
Once the *tarball RenderView.tar* has been downloaded and extracted,
```
cd RenderView/build 
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
./RenderView
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

