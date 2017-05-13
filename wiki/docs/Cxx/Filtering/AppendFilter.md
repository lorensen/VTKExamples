[VTKExamples](/home/)/[Cxx](/Cxx)/Filtering/AppendFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestAppendFilter.png?raw=true" width="256" />

### Description
This example loads points into a polydata and an unstructured grid then combines them.

The example should be extended to show cells being combined as well.

**AppendFilter.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkAppendFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkPointSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkUnstructuredGrid.h>

int main(int, char *[])
{
  // Create 5 points (vtkPolyData)
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(5);
  pointSource->Update();

  vtkSmartPointer<vtkPolyData> polydata = pointSource->GetOutput();

  std::cout << "There are " << polydata->GetNumberOfPoints()
            << " points in the polydata." << std::endl;

  // Create 2 points in a vtkUnstructuredGrid

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(0,0,1);

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);

  std::cout << "There are " << ug->GetNumberOfPoints()
            << " points in the unstructured grid." << std::endl;

  // Combine the two data sets
  vtkSmartPointer<vtkAppendFilter> appendFilter =
    vtkSmartPointer<vtkAppendFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  appendFilter->AddInput(polydata);
  appendFilter->AddInput(ug);
#else
  appendFilter->AddInputData(polydata);
  appendFilter->AddInputData(ug);
#endif
  appendFilter->Update();

  vtkSmartPointer<vtkUnstructuredGrid> combined =
    appendFilter->GetOutput();
  std::cout << "There are " << combined->GetNumberOfPoints()
            << " points combined." << std::endl;

  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(appendFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(5);

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
  renderer->AddActor(actor);
  renderer->SetBackground(.2, .3, .4);

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(AppendFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(AppendFilter MACOSX_BUNDLE AppendFilter.cxx)
 
target_link_libraries(AppendFilter ${VTK_LIBRARIES})
```

**Download and Build AppendFilter**

Click [here to download AppendFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/AppendFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball AppendFilter.tar* has been downloaded and extracted,
```
cd AppendFilter/build 
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
./AppendFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

