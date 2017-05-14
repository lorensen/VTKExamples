[VTKExamples](/index/)/[Cxx](/Cxx)/GeometricObjects/TriangleStrip

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestTriangleStrip.png?raw=true" width="256" />

### Description
A triangle strip is a compact representation of a series of triangles. See [this wikipedia article](http://en.wikipedia.org/wiki/Triangle_strip) for an explanation.

**TriangleStrip.cxx**
```c++
#include <vtkVersion.h>
#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkDataSetMapper.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTriangleStrip.h>
 
int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(0,1,0);
  points->InsertNextPoint(1,0,0);
  points->InsertNextPoint(1.5,1,0);
 
  vtkSmartPointer<vtkTriangleStrip> triangleStrip =
    vtkSmartPointer<vtkTriangleStrip>::New();
  triangleStrip->GetPointIds()->SetNumberOfIds(4);
  triangleStrip->GetPointIds()->SetId(0,0);
  triangleStrip->GetPointIds()->SetId(1,1);
  triangleStrip->GetPointIds()->SetId(2,2);
  triangleStrip->GetPointIds()->SetId(3,3);
 
  vtkSmartPointer<vtkCellArray> cells = 
    vtkSmartPointer<vtkCellArray>::New();
  cells->InsertNextCell(triangleStrip);
 
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetStrips(cells);
 
  // Create an actor and mapper
  vtkSmartPointer<vtkDataSetMapper> mapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInput(polydata);
#else
  mapper->SetInputData(polydata);
#endif
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetRepresentationToWireframe();
 
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(actor);
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TriangleStrip)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TriangleStrip MACOSX_BUNDLE TriangleStrip.cxx)
 
target_link_libraries(TriangleStrip ${VTK_LIBRARIES})
```

**Download and Build TriangleStrip**

Click [here to download TriangleStrip](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TriangleStrip.tar) and its *CMakeLists.txt* file.
Once the *tarball TriangleStrip.tar* has been downloaded and extracted,
```
cd TriangleStrip/build 
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
./TriangleStrip
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

