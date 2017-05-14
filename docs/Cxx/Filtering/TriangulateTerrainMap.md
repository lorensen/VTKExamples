[VTKExamples](/index/)/[Cxx](/Cxx)/Filtering/TriangulateTerrainMap

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestTriangulateTerrainMap.png?raw=true" width="256" />

### Description
This example generates heights (z value) on a 10x10 grid (a terrain map) and triangulates the points.

**TriangulateTerrainMap.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkDelaunay2D.h>
#include <vtkMath.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVertexGlyphFilter.h>

int main(int, char *[])
{
  // Create points on an XY grid with random Z coordinate
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  unsigned int gridSize = 10;
  for(unsigned int x = 0; x < gridSize; x++)
  {
    for(unsigned int y = 0; y < gridSize; y++)
    {
      points->InsertNextPoint(x, y, vtkMath::Random(0.0, 3.0));
    }
  }

  // Add the grid points to a polydata object
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

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> pointsMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pointsMapper->SetInputConnection(glyphFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> pointsActor =
    vtkSmartPointer<vtkActor>::New();
  pointsActor->SetMapper(pointsMapper);
  pointsActor->GetProperty()->SetPointSize(3);
  pointsActor->GetProperty()->SetColor(1,0,0);
  // Triangulate the grid points
  vtkSmartPointer<vtkDelaunay2D> delaunay =
    vtkSmartPointer<vtkDelaunay2D>::New();
#if VTK_MAJOR_VERSION <= 5
  delaunay->SetInput(polydata);
#else
  delaunay->SetInputData(polydata);
#endif
  delaunay->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> triangulatedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  triangulatedMapper->SetInputConnection(delaunay->GetOutputPort());

  vtkSmartPointer<vtkActor> triangulatedActor =
    vtkSmartPointer<vtkActor>::New();
  triangulatedActor->SetMapper(triangulatedMapper);

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
  renderer->AddActor(pointsActor);
  renderer->AddActor(triangulatedActor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TriangulateTerrainMap)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TriangulateTerrainMap MACOSX_BUNDLE TriangulateTerrainMap.cxx)
 
target_link_libraries(TriangulateTerrainMap ${VTK_LIBRARIES})
```

**Download and Build TriangulateTerrainMap**

Click [here to download TriangulateTerrainMap](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TriangulateTerrainMap.tar) and its *CMakeLists.txt* file.
Once the *tarball TriangulateTerrainMap.tar* has been downloaded and extracted,
```
cd TriangulateTerrainMap/build 
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
./TriangulateTerrainMap
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

