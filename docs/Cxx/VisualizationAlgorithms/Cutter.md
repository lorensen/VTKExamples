[VTKExamples](/index/)/[Cxx](/Cxx)/VisualizationAlgorithms/Cutter

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/VisualizationAlgorithms/TestCutter.png?raw=true" width="256" />

**Cutter.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkPlane.h>
#include <vtkCutter.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{ 
  vtkSmartPointer<vtkCubeSource> cube =
    vtkSmartPointer<vtkCubeSource>::New();
  cube->SetXLength(40);
  cube->SetYLength(30);
  cube->SetZLength(20);
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cube->GetOutputPort());
  
  // Create a plane to cut,here it cuts in the XZ direction (xz normal=(1,0,0);XY =(0,0,1),YZ =(0,1,0)
  vtkSmartPointer<vtkPlane> plane =
    vtkSmartPointer<vtkPlane>::New();
  plane->SetOrigin(10,0,0);
  plane->SetNormal(1,0,0);
  
  // Create cutter
  vtkSmartPointer<vtkCutter> cutter =
    vtkSmartPointer<vtkCutter>::New();
  cutter->SetCutFunction(plane);
  cutter->SetInputConnection(cube->GetOutputPort());
  cutter->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> cutterMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cutterMapper->SetInputConnection( cutter->GetOutputPort());
  
  // Create plane actor
  vtkSmartPointer<vtkActor> planeActor =
    vtkSmartPointer<vtkActor>::New();
  planeActor->GetProperty()->SetColor(1.0,1,0);
  planeActor->GetProperty()->SetLineWidth(2);
  planeActor->SetMapper(cutterMapper);
  
  // Create cube actor
  vtkSmartPointer<vtkActor> cubeActor =
    vtkSmartPointer<vtkActor>::New();
  cubeActor->GetProperty()->SetColor(0.5,1,0.5);
  cubeActor->GetProperty()->SetOpacity(0.5);
  cubeActor->SetMapper(cubeMapper);
  
  // Create renderers and add actors of plane and cube
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(planeActor); //display the rectangle resulting from the cut
  renderer->AddActor(cubeActor); //display the cube
  
  // Add renderer to renderwindow and render
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(600, 600);
  
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  renderer->SetBackground(0,0,0);
  renderWindow->Render();

  interactor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Cutter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Cutter MACOSX_BUNDLE Cutter.cxx)
 
target_link_libraries(Cutter ${VTK_LIBRARIES})
```

**Download and Build Cutter**

Click [here to download Cutter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Cutter.tar) and its *CMakeLists.txt* file.
Once the *tarball Cutter.tar* has been downloaded and extracted,
```
cd Cutter/build 
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
./Cutter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

