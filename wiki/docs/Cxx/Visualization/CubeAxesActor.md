[VTKExamples](/index/)/[Cxx](/Cxx)/Visualization/CubeAxesActor

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestCubeAxesActor.png?raw=true" width="256" />

**CubeAxesActor.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkCubeAxesActor.h>
#include <vtkTextProperty.h>
#include <vtkActorCollection.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSuperquadricSource.h>
#include <vtkActor.h>

int main(int, char *[])
{
  // Create a superquadric
  vtkSmartPointer<vtkSuperquadricSource> superquadricSource = 
    vtkSmartPointer<vtkSuperquadricSource>::New();
  superquadricSource->SetPhiRoundness(3.1);
  superquadricSource->SetThetaRoundness(1.0);
  superquadricSource->Update(); // needed to GetBounds later

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(superquadricSource->GetOutputPort());

  vtkSmartPointer<vtkActor> superquadricActor =
    vtkSmartPointer<vtkActor>::New();
  superquadricActor->SetMapper(mapper);
  
  vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor =
    vtkSmartPointer<vtkCubeAxesActor>::New();
  cubeAxesActor->SetBounds(superquadricSource->GetOutput()->GetBounds());
  cubeAxesActor->SetCamera(renderer->GetActiveCamera());
  cubeAxesActor->GetTitleTextProperty(0)->SetColor(1.0, 0.0, 0.0);
  cubeAxesActor->GetLabelTextProperty(0)->SetColor(1.0, 0.0, 0.0);

  cubeAxesActor->GetTitleTextProperty(1)->SetColor(0.0, 1.0, 0.0);
  cubeAxesActor->GetLabelTextProperty(1)->SetColor(0.0, 1.0, 0.0);

  cubeAxesActor->GetTitleTextProperty(2)->SetColor(0.0, 0.0, 1.0);
  cubeAxesActor->GetLabelTextProperty(2)->SetColor(0.0, 0.0, 1.0);

  cubeAxesActor->DrawXGridlinesOn();
  cubeAxesActor->DrawYGridlinesOn();
  cubeAxesActor->DrawZGridlinesOn();
#if VTK_MAJOR_VERSION == 6
  cubeAxesActor->SetGridLineLocation(VTK_GRID_LINES_FURTHEST);
#endif
#if VTK_MAJOR_VERSION > 6
  cubeAxesActor->SetGridLineLocation(
    cubeAxesActor->VTK_GRID_LINES_FURTHEST);
#endif
  
  cubeAxesActor->XAxisMinorTickVisibilityOff();
  cubeAxesActor->YAxisMinorTickVisibilityOff();
  cubeAxesActor->ZAxisMinorTickVisibilityOff();

  renderer->AddActor(cubeAxesActor);
  renderer->AddActor(superquadricActor);
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);

  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
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
 
PROJECT(CubeAxesActor)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CubeAxesActor MACOSX_BUNDLE CubeAxesActor.cxx)
 
target_link_libraries(CubeAxesActor ${VTK_LIBRARIES})
```

**Download and Build CubeAxesActor**

Click [here to download CubeAxesActor](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CubeAxesActor.tar) and its *CMakeLists.txt* file.
Once the *tarball CubeAxesActor.tar* has been downloaded and extracted,
```
cd CubeAxesActor/build 
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
./CubeAxesActor
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

