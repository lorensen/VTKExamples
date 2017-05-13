[VTKExamples](/home/)/[Cxx](/Cxx)/Meshes/WindowedSincPolyDataFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Meshes/TestWindowedSincPolyDataFilter.png?raw=true" width="256" />

### Description
This example demonstrates how to smooth a mesh.

**WindowedSincPolyDataFilter.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkWindowedSincPolyDataFilter.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  vtkSmartPointer<vtkWindowedSincPolyDataFilter> smoother =
    vtkSmartPointer<vtkWindowedSincPolyDataFilter>::New();
  smoother->SetInputConnection(sphereSource->GetOutputPort());
  smoother->SetNumberOfIterations(15);
  smoother->BoundarySmoothingOff();
  smoother->FeatureEdgeSmoothingOff();
  smoother->SetFeatureAngle(120.0);
  smoother->SetPassBand(.001);
  smoother->NonManifoldSmoothingOn();
  smoother->NormalizeCoordinatesOn();
  smoother->Update();

  vtkSmartPointer<vtkPolyDataMapper> smoothedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  smoothedMapper->SetInputConnection(smoother->GetOutputPort());
  vtkSmartPointer<vtkActor> smoothedActor =
    vtkSmartPointer<vtkActor>::New();
  smoothedActor->SetMapper(smoothedMapper);
  
  vtkSmartPointer<vtkPolyDataMapper> inputMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  inputMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->SetMapper(inputMapper);
  
  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  // And one interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  // Add the sphere to the left and the cube to the right
  leftRenderer->AddActor(inputActor);
  rightRenderer->AddActor(smoothedActor);

  leftRenderer->ResetCamera();

  rightRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(WindowedSincPolyDataFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(WindowedSincPolyDataFilter MACOSX_BUNDLE WindowedSincPolyDataFilter.cxx)
 
target_link_libraries(WindowedSincPolyDataFilter ${VTK_LIBRARIES})
```

**Download and Build WindowedSincPolyDataFilter**

Click [here to download WindowedSincPolyDataFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/WindowedSincPolyDataFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball WindowedSincPolyDataFilter.tar* has been downloaded and extracted,
```
cd WindowedSincPolyDataFilter/build 
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
./WindowedSincPolyDataFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

