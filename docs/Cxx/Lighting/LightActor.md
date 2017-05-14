[VTKExamples](/index/)/[Cxx](/Cxx)/Lighting/LightActor

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Lighting/TestLightActor.png?raw=true" width="256" />

**LightActor.cxx**
```c++
#include <cstdlib>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkLightActor.h>
#include <vtkLight.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

  // Display where the light is
  vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
  light->SetPositional(true); // without this line, the program crashes
  vtkSmartPointer<vtkLightActor> lightActor = vtkSmartPointer<vtkLightActor>::New();
  lightActor->SetLight(light);
  renderer->AddViewProp(lightActor);

  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(LightActor)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(LightActor MACOSX_BUNDLE LightActor.cxx)
 
target_link_libraries(LightActor ${VTK_LIBRARIES})
```

**Download and Build LightActor**

Click [here to download LightActor](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/LightActor.tar) and its *CMakeLists.txt* file.
Once the *tarball LightActor.tar* has been downloaded and extracted,
```
cd LightActor/build 
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
./LightActor
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

