[VTKExamples](/index/)/[Cxx](/Cxx)/GeometricObjects/Frustum

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestFrustum.png?raw=true" width="256" />

### Description
This example gets the frustum from a camera and displays it on the screen.

**Frustum.cxx**
```c++
#include <vtkVersion.h>
#include <vtkFrustumSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkPlanes.h>
#include <vtkMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  double planesArray[24];
  
  camera->GetFrustumPlanes(1, planesArray);
  
  vtkSmartPointer<vtkPlanes> planes =
    vtkSmartPointer<vtkPlanes>::New();
  planes->SetFrustumPlanes(planesArray);
  
  vtkSmartPointer<vtkFrustumSource> frustumSource =
    vtkSmartPointer<vtkFrustumSource>::New();
  frustumSource->ShowLinesOff();
  frustumSource->SetPlanes(planes);
  frustumSource->Update();

  vtkPolyData* frustum = frustumSource->GetOutput();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInput(frustum);
#else
  mapper->SetInputData(frustum);
#endif

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
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
  renderer->AddActor(actor);
  renderer->SetBackground( .2, .1, .3); // Background color dark purple

  // render an image (lights and cameras are created automatically)
  renderWindow->Render();

  // begin mouse interaction
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Frustum)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Frustum MACOSX_BUNDLE Frustum.cxx)
 
target_link_libraries(Frustum ${VTK_LIBRARIES})
```

**Download and Build Frustum**

Click [here to download Frustum](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Frustum.tar) and its *CMakeLists.txt* file.
Once the *tarball Frustum.tar* has been downloaded and extracted,
```
cd Frustum/build 
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
./Frustum
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

