[VTKExamples](/index/)/[Cxx](/Cxx)/Filtering/Delaunay2D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestDelaunay2D.png?raw=true" width="256" />

### Description
This example generates a set of points aligned with an XY grid with random heights (z values). The Delaunay2D filter "magically" knows how to triangulate this type of point set because it projects the points by default onto the XY axis and then performs a 2D Delaunay triangulation. The result is a mesh on the input points.

**Delaunay2D.cxx**
```c++
#include <vtkVersion.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkTriangle.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkLine.h>
#include <vtkCellLocator.h>
#include <vtkSmartPointer.h>
#include <vtkDelaunay2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkVertexGlyphFilter.h>

int main(int, char *[])
{
  // Create a set of heighs on a grid.
  // This is often called a "terrain map".
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  unsigned int GridSize = 10;
  for(unsigned int x = 0; x < GridSize; x++)
  {
    for(unsigned int y = 0; y < GridSize; y++)
    {
        points->InsertNextPoint(x, y, (x+y)/(y+1));
    }
  }

  // Add the grid points to a polydata object
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Triangulate the grid points
  vtkSmartPointer<vtkDelaunay2D> delaunay =
  vtkSmartPointer<vtkDelaunay2D>::New();
#if VTK_MAJOR_VERSION <= 5
  delaunay->SetInput(polydata);
#else
  delaunay->SetInputData(polydata);
#endif
  delaunay->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> meshMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  meshMapper->SetInputConnection(delaunay->GetOutputPort());

  vtkSmartPointer<vtkActor> meshActor =
    vtkSmartPointer<vtkActor>::New();
  meshActor->SetMapper(meshMapper);

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  glyphFilter->SetInputConnection(polydata->GetProducerPort());
#else
  glyphFilter->SetInputData(polydata);
#endif
  glyphFilter->Update();

  vtkSmartPointer<vtkPolyDataMapper> pointMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pointMapper->SetInputConnection(glyphFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> pointActor =
    vtkSmartPointer<vtkActor>::New();
  pointActor->GetProperty()->SetColor(1,0,0);
  pointActor->GetProperty()->SetPointSize(3);
  pointActor->SetMapper(pointMapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(meshActor);
  renderer->AddActor(pointActor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Delaunay2D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Delaunay2D MACOSX_BUNDLE Delaunay2D.cxx)
 
target_link_libraries(Delaunay2D ${VTK_LIBRARIES})
```

**Download and Build Delaunay2D**

Click [here to download Delaunay2D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Delaunay2D.tar) and its *CMakeLists.txt* file.
Once the *tarball Delaunay2D.tar* has been downloaded and extracted,
```
cd Delaunay2D/build 
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
./Delaunay2D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

