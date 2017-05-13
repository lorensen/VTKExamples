[VTKExamples](Home)/[Cxx](Cxx)/Meshes/BoundaryEdges

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Meshes/TestBoundaryEdges.png" width="256" />

### Description
This filter will extract the boundary edges of a mesh. The original mesh is shown with the feature edges shown in red.

**BoundaryEdges.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkFeatureEdges.h>
#include <vtkPolyData.h>
#include <vtkDiskSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDiskSource> diskSource =
    vtkSmartPointer<vtkDiskSource>::New();
  diskSource->Update();

  vtkSmartPointer<vtkFeatureEdges> featureEdges =
    vtkSmartPointer<vtkFeatureEdges>::New();
  featureEdges->SetInputConnection(diskSource->GetOutputPort());
  featureEdges->BoundaryEdgesOn();
  featureEdges->FeatureEdgesOff();
  featureEdges->ManifoldEdgesOff();
  featureEdges->NonManifoldEdgesOff();
  featureEdges->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> edgeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  edgeMapper->SetInputConnection(featureEdges->GetOutputPort());
  vtkSmartPointer<vtkActor> edgeActor =
    vtkSmartPointer<vtkActor>::New();
  edgeActor->SetMapper(edgeMapper);

  vtkSmartPointer<vtkPolyDataMapper> diskMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  diskMapper->SetInputConnection(diskSource->GetOutputPort());
  vtkSmartPointer<vtkActor> diskActor =
    vtkSmartPointer<vtkActor>::New();
  diskActor->SetMapper(diskMapper);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(edgeActor);
  renderer->AddActor(diskActor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BoundaryEdges)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BoundaryEdges MACOSX_BUNDLE BoundaryEdges.cxx)
 
target_link_libraries(BoundaryEdges ${VTK_LIBRARIES})
```

**Download and Build BoundaryEdges**

Click [here to download BoundaryEdges](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BoundaryEdges.tar) and its *CMakeLists.txt* file.
Once the *tarball BoundaryEdges.tar* has been downloaded and extracted,
```
cd BoundaryEdges/build 
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
./BoundaryEdges
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

