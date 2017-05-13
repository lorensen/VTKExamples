[VTKExamples](/home/)/[Cxx](/Cxx)/Filtering/ConstrainedDelaunay2D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestConstrainedDelaunay2D.png?raw=true" width="256" />

### Description
Perform a 2D Delaunay triangulation respecting a specified boundary. This examples constructs a 10x10 grid of points. It then defines a polygon that uses the points in the grid. We want to triangulate all of the points except the region inside the boundary of the polygon. We expect a rectangular hole of size 4x3 in the resulting triangulated plane.

**ConstrainedDelaunay2D.cxx**
```c++
#include <vtkVersion.h>
#include <vtkCellArray.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolygon.h>
#include <vtkSmartPointer.h>
#include <vtkDelaunay2D.h>
#include <vtkMath.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Generate a 10 x 10 grid of points
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  for(unsigned int x = 0; x < 10; x++)
  {
    for(unsigned int y = 0; y < 10; y++)
    {
      points->InsertNextPoint(x + vtkMath::Random(-.25, .25),
                              y + vtkMath::Random(-.25,.25),
                              0);
    }
  }

  vtkSmartPointer<vtkPolyData> aPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  aPolyData->SetPoints(points);

  // Create a cell array to store the polygon in
  vtkSmartPointer<vtkCellArray> aCellArray =
    vtkSmartPointer<vtkCellArray>::New();

  // Define a polygonal hole with a clockwise polygon
  vtkSmartPointer<vtkPolygon> aPolygon =
   vtkSmartPointer<vtkPolygon>::New();

  aPolygon->GetPointIds()->InsertNextId(22);
  aPolygon->GetPointIds()->InsertNextId(23);
  aPolygon->GetPointIds()->InsertNextId(24);
  aPolygon->GetPointIds()->InsertNextId(25);
  aPolygon->GetPointIds()->InsertNextId(35);
  aPolygon->GetPointIds()->InsertNextId(45);
  aPolygon->GetPointIds()->InsertNextId(44);
  aPolygon->GetPointIds()->InsertNextId(43);
  aPolygon->GetPointIds()->InsertNextId(42);
  aPolygon->GetPointIds()->InsertNextId(32);

  aCellArray->InsertNextCell(aPolygon);

  // Create a polydata to store the boundary. The points must be the
  // same as the points we will triangulate.
  vtkSmartPointer<vtkPolyData> boundary =
   vtkSmartPointer<vtkPolyData>::New();
  boundary->SetPoints(aPolyData->GetPoints());
  boundary->SetPolys(aCellArray);

  // Triangulate the grid points
  vtkSmartPointer<vtkDelaunay2D> delaunay =
   vtkSmartPointer<vtkDelaunay2D>::New();
#if VTK_MAJOR_VERSION <= 5
  delaunay->SetInput(aPolyData);
  delaunay->SetSource(boundary);
#else
  delaunay->SetInputData(aPolyData);
  delaunay->SetSourceData(boundary);
#endif
  delaunay->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> meshMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  meshMapper->SetInputConnection(delaunay->GetOutputPort());

  vtkSmartPointer<vtkActor> meshActor =
    vtkSmartPointer<vtkActor>::New();
  meshActor->SetMapper(meshMapper);
  //meshActor->GetProperty()->SetEdgeColor(0,0,1); // Why aren't the edges aren't visible unless we set the representation to wireframe?
  //meshActor->GetProperty()->SetInterpolationToFlat();
  meshActor->GetProperty()->SetRepresentationToWireframe();

  vtkSmartPointer<vtkPolyDataMapper> boundaryMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  boundaryMapper->SetInputConnection(boundary->GetProducerPort());
#else
  boundaryMapper->SetInputData(boundary);
#endif

  vtkSmartPointer<vtkActor> boundaryActor =
    vtkSmartPointer<vtkActor>::New();
  boundaryActor->SetMapper(boundaryMapper);
  boundaryActor->GetProperty()->SetColor(1,0,0);

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
  renderer->AddActor(meshActor);
  renderer->AddActor(boundaryActor);
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
 
PROJECT(ConstrainedDelaunay2D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ConstrainedDelaunay2D MACOSX_BUNDLE ConstrainedDelaunay2D.cxx)
 
target_link_libraries(ConstrainedDelaunay2D ${VTK_LIBRARIES})
```

**Download and Build ConstrainedDelaunay2D**

Click [here to download ConstrainedDelaunay2D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ConstrainedDelaunay2D.tar) and its *CMakeLists.txt* file.
Once the *tarball ConstrainedDelaunay2D.tar* has been downloaded and extracted,
```
cd ConstrainedDelaunay2D/build 
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
./ConstrainedDelaunay2D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

