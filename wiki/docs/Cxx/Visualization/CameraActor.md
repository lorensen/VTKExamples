[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/CameraActor

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestCameraActor.png?raw=true" width="256" />

**CameraActor.cxx**
```c++
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkPlanes.h>
#include <vtkMapper.h>
#include <vtkCameraActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(400);
  sphereSource->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor = 
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  
  // Camera
  vtkSmartPointer<vtkCamera> camera = 
    vtkSmartPointer<vtkCamera>::New();

  vtkSmartPointer<vtkCameraActor> cameraActor = 
    vtkSmartPointer<vtkCameraActor>::New();
  cameraActor->SetCamera(camera);
  
  // (Xmin,Xmax,Ymin,Ymax,Zmin,Zmax).
  double* bounds = new double[6];
  bounds = cameraActor->GetBounds();
  std::cout << "bounds: " << bounds[0] << " " << bounds[1] << " " << bounds[2] << " " << 
      bounds[3] << " " << bounds[4] << " " << bounds[5] << std::endl;

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(cameraActor);
  renderer->AddActor(sphereActor);
  
  renderer->SetBackground(1,1,1); // Background color white
  renderWindow->Render();
  renderWindowInteractor->Start();
  
 return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CameraActor)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CameraActor MACOSX_BUNDLE CameraActor.cxx)
 
target_link_libraries(CameraActor ${VTK_LIBRARIES})
```

**Download and Build CameraActor**

Click [here to download CameraActor](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CameraActor.tar) and its *CMakeLists.txt* file.
Once the *tarball CameraActor.tar* has been downloaded and extracted,
```
cd CameraActor/build 
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
./CameraActor
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

