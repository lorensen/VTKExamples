[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/LabelPlacementMapper

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestLabelPlacementMapper.png?raw=true" width="256" />

### Description
This example demonstrates how to add labels from an array to points. Each point is given a priority that determines which labels are visible when space is limited.

**LabelPlacementMapper.cxx**
```c++
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkIntArray.h>
#include <vtkLabelPlacementMapper.h>
#include <vtkPointData.h>
#include <vtkPointSetToLabelHierarchy.h>
#include <vtkPointSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkStringArray.h>

int main(int, char *[])
{
  // Create a point set.
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(6);
  pointSource->Update();

  // Add label array.
  vtkSmartPointer<vtkStringArray> labels =
    vtkSmartPointer<vtkStringArray>::New();
  labels->SetNumberOfValues(6);
  labels->SetName("labels");
  labels->SetValue(0, "Priority 10");
  labels->SetValue(1, "Priority 7");
  labels->SetValue(2, "Priority 6");
  labels->SetValue(3, "Priority 4");
  labels->SetValue(4, "Priority 4");
  labels->SetValue(5, "Priority 4");
  pointSource->GetOutput()->GetPointData()->AddArray(labels);

  // Add priority array.
  vtkSmartPointer<vtkIntArray> sizes =
    vtkSmartPointer<vtkIntArray>::New();
  sizes->SetNumberOfValues(6);
  sizes->SetName("sizes");
  sizes->SetValue(0, 10);
  sizes->SetValue(1, 7);
  sizes->SetValue(2, 6);
  sizes->SetValue(3, 4);
  sizes->SetValue(4, 4);
  sizes->SetValue(5, 4);
  pointSource->GetOutput()->GetPointData()->AddArray(sizes);

  // Create a mapper and actor for the points.
  vtkSmartPointer<vtkPolyDataMapper> pointMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pointMapper->SetInputConnection(pointSource->GetOutputPort());

  vtkSmartPointer<vtkActor> pointActor =
    vtkSmartPointer<vtkActor>::New();
  pointActor->SetMapper(pointMapper);

  // Generate the label hierarchy.
  vtkSmartPointer<vtkPointSetToLabelHierarchy> pointSetToLabelHierarchyFilter =
    vtkSmartPointer<vtkPointSetToLabelHierarchy>::New();
  pointSetToLabelHierarchyFilter->SetInputConnection(
    pointSource->GetOutputPort());
  pointSetToLabelHierarchyFilter->SetLabelArrayName("labels");
  pointSetToLabelHierarchyFilter->SetPriorityArrayName("sizes");
  pointSetToLabelHierarchyFilter->Update();

  // Create a mapper and actor for the labels.
  vtkSmartPointer<vtkLabelPlacementMapper> labelMapper =
    vtkSmartPointer<vtkLabelPlacementMapper>::New();
  labelMapper->SetInputConnection(
    pointSetToLabelHierarchyFilter->GetOutputPort());
  vtkSmartPointer<vtkActor2D> labelActor =
    vtkSmartPointer<vtkActor2D>::New();
  labelActor->SetMapper(labelMapper);

  // Create a renderer, render window, and interactor.
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene.
  renderer->AddActor(pointActor);
  renderer->AddActor(labelActor);

  // Render and interact.
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(LabelPlacementMapper)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(LabelPlacementMapper MACOSX_BUNDLE LabelPlacementMapper.cxx)
 
target_link_libraries(LabelPlacementMapper ${VTK_LIBRARIES})
```

**Download and Build LabelPlacementMapper**

Click [here to download LabelPlacementMapper](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/LabelPlacementMapper.tar) and its *CMakeLists.txt* file.
Once the *tarball LabelPlacementMapper.tar* has been downloaded and extracted,
```
cd LabelPlacementMapper/build 
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
./LabelPlacementMapper
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

