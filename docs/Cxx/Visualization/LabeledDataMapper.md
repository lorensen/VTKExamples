[VTKExamples](/index/)/[Cxx](/Cxx)/Visualization/LabeledDataMapper

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestLabeledDataMapper.png?raw=true" width="256" />

### Description
This example demonstrates how to display the point ID at each point.

**LabeledDataMapper.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkLabeledDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create a point set
  vtkSmartPointer<vtkPointSource> pointSource = 
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(10);
  pointSource->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> pointMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pointMapper->SetInputConnection(pointSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> pointActor = 
    vtkSmartPointer<vtkActor>::New();
  pointActor->SetMapper(pointMapper);
  pointActor->GetProperty()->SetPointSize(10);
  pointActor->GetProperty()->SetColor(1, 1, .4);

  vtkSmartPointer<vtkLabeledDataMapper> labelMapper = 
    vtkSmartPointer<vtkLabeledDataMapper>::New();
  labelMapper->SetInputConnection(pointSource->GetOutputPort());
  vtkSmartPointer<vtkActor2D> labelActor = 
    vtkSmartPointer<vtkActor2D>::New();
  labelActor->SetMapper(labelMapper);
  
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(pointActor);
  renderer->AddActor(labelActor);
  
  renderer->SetBackground(.1, .3, .2); // Background color green

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(LabeledDataMapper)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(LabeledDataMapper MACOSX_BUNDLE LabeledDataMapper.cxx)
 
target_link_libraries(LabeledDataMapper ${VTK_LIBRARIES})
```

**Download and Build LabeledDataMapper**

Click [here to download LabeledDataMapper](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/LabeledDataMapper.tar) and its *CMakeLists.txt* file.
Once the *tarball LabeledDataMapper.tar* has been downloaded and extracted,
```
cd LabeledDataMapper/build 
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
./LabeledDataMapper
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

