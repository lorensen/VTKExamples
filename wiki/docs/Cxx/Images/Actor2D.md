[VTKExamples](/home/)/[Cxx](/Cxx)/Images/Actor2D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestActor2D.png?raw=true" width="256" />

**Actor2D.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor2D.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty2D.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(10,10,0);
  points->InsertNextPoint(100,100,0);
  points->InsertNextPoint(200,200,0);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  glyphFilter->SetInputConnection(polydata->GetProducerPort());
#else
  glyphFilter->SetInputData(polydata);
#endif
  glyphFilter->Update();

  vtkSmartPointer<vtkPolyDataMapper2D> mapper =
    vtkSmartPointer<vtkPolyDataMapper2D>::New();
  mapper->SetInputConnection(glyphFilter->GetOutputPort());
  mapper->Update();

  vtkSmartPointer<vtkActor2D> actor = 
    vtkSmartPointer<vtkActor2D>::New();
  actor->SetMapper(mapper);
 
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
  renderWindow->SetSize(300,300);
  actor->GetProperty()->SetColor(0,1,0);
  actor->GetProperty()->SetPointSize(3);
  
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Actor2D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Actor2D MACOSX_BUNDLE Actor2D.cxx)
 
target_link_libraries(Actor2D ${VTK_LIBRARIES})
```

**Download and Build Actor2D**

Click [here to download Actor2D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Actor2D.tar) and its *CMakeLists.txt* file.
Once the *tarball Actor2D.tar* has been downloaded and extracted,
```
cd Actor2D/build 
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
./Actor2D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

