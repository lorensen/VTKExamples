[VTKExamples](/index/)/[Cxx](/Cxx)/Filtering/PerlinNoise

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestPerlinNoise.png?raw=true" width="256" />

**PerlinNoise.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <vtkProperty.h>
#include <vtkCamera.h>

#include <vtkPerlinNoise.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPerlinNoise> perlinNoise =
    vtkSmartPointer<vtkPerlinNoise>::New();
  perlinNoise->SetFrequency(2, 1.25, 1.5);
  perlinNoise->SetPhase(0, 0, 0);

  vtkSmartPointer<vtkSampleFunction> sample =
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetImplicitFunction(perlinNoise);
  sample->SetSampleDimensions(65, 65, 20);
  sample->ComputeNormalsOff();

  vtkSmartPointer<vtkContourFilter> surface =
    vtkSmartPointer<vtkContourFilter>::New();
  surface->SetInputConnection(sample->GetOutputPort());
  surface->SetValue(0, 0.0);
  
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(surface->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(0.2, 0.4, 0.6);
  
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  
  // Add the actors to the renderer, set the background and size
  
  renderer->AddActor(actor);
  renderer->SetBackground(1, 1, 1);
  renderWindow->SetSize(300, 300);
  renderer->ResetCamera();
  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PerlinNoise)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PerlinNoise MACOSX_BUNDLE PerlinNoise.cxx)
 
target_link_libraries(PerlinNoise ${VTK_LIBRARIES})
```

**Download and Build PerlinNoise**

Click [here to download PerlinNoise](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PerlinNoise.tar) and its *CMakeLists.txt* file.
Once the *tarball PerlinNoise.tar* has been downloaded and extracted,
```
cd PerlinNoise/build 
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
./PerlinNoise
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

