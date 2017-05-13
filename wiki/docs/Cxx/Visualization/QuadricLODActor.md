[VTKExamples](Home)/[Cxx](Cxx)/Visualization/QuadricLODActor

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestQuadricLODActor.png" width="256" />

### Description
If you have a fast graphics card you may not see a difference with the sphere model.

**QuadricLODActor.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkQuadricLODActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

int main(int, char *[])
{
  // High res sphere
  vtkSmartPointer<vtkSphereSource> highResSphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  highResSphereSource->SetThetaResolution(200);
  highResSphereSource->SetPhiResolution(200);
  highResSphereSource->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> highResMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  highResMapper->SetInputConnection(highResSphereSource->GetOutputPort());
  
  vtkSmartPointer<vtkQuadricLODActor> actor = 
    vtkSmartPointer<vtkQuadricLODActor>::New();
  actor->SetMapper(highResMapper);
  actor->GetProperty()->SetInterpolationToFlat();
  
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

  renderWindowInteractor->SetDesiredUpdateRate(1e20);
      
  renderer->AddActor(actor);
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(QuadricLODActor)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(QuadricLODActor MACOSX_BUNDLE QuadricLODActor.cxx)
 
target_link_libraries(QuadricLODActor ${VTK_LIBRARIES})
```

**Download and Build QuadricLODActor**

Click [here to download QuadricLODActor](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/QuadricLODActor.tar) and its *CMakeLists.txt* file.
Once the *tarball QuadricLODActor.tar* has been downloaded and extracted,
```
cd QuadricLODActor/build 
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
./QuadricLODActor
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

