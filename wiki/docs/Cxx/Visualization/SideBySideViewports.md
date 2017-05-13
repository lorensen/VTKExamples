[VTKExamples](Home)/[Cxx](Cxx)/Visualization/SideBySideViewports

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestSideBySideViewports.png" width="256" />

### Description
This example splits the window into a left and right side. A sphere is drawn on the left and a cube is drawn on the right.

**SideBySideViewports.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCubeSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkXMLPolyDataReader.h>

int main(int, char*[])
{
  // Setup sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor = 
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  
  // Setup cube
  vtkSmartPointer<vtkCubeSource> cubeSource = 
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
  vtkSmartPointer<vtkActor> cubeActor = 
    vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);
  cubeActor->GetProperty()->SetDiffuseColor(.3, .6, .4);
  
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
  leftRenderer->AddActor(sphereActor);
  rightRenderer->AddActor(cubeActor);
  
  leftRenderer->ResetCamera();

  rightRenderer->ResetCamera();
  rightRenderer->GetActiveCamera()->Azimuth(30);
  rightRenderer->GetActiveCamera()->Elevation(30);

  renderWindow->Render();
  interactor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SideBySideViewports)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SideBySideViewports MACOSX_BUNDLE SideBySideViewports.cxx)
 
target_link_libraries(SideBySideViewports ${VTK_LIBRARIES})
```

**Download and Build SideBySideViewports**

Click [here to download SideBySideViewports](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SideBySideViewports.tar) and its *CMakeLists.txt* file.
Once the *tarball SideBySideViewports.tar* has been downloaded and extracted,
```
cd SideBySideViewports/build 
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
./SideBySideViewports
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

