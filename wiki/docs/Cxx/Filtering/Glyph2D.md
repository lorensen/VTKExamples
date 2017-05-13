[VTKExamples](Home)/[Cxx](Cxx)/Filtering/Glyph2D

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Filtering/TestGlyph2D.png" width="256" />

### Description
Copy a polydata to every point in the input set. We use a hexagon for the demo.

**Glyph2D.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkRegularPolygonSource.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkGlyph2D.h>
#include <vtkCellArray.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,1,0);
  points->InsertNextPoint(2,2,0);
  
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  
  // Create anything you want here, we will use a polygon for the demo.
  vtkSmartPointer<vtkRegularPolygonSource> polygonSource = 
      vtkSmartPointer<vtkRegularPolygonSource>::New(); //default is 6 sides
  
  vtkSmartPointer<vtkGlyph2D> glyph2D = 
    vtkSmartPointer<vtkGlyph2D>::New();
  glyph2D->SetSourceConnection(polygonSource->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
  glyph2D->SetInput(polydata);
#else
  glyph2D->SetInputData(polydata);
#endif
  glyph2D->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyph2D->GetOutputPort());
  mapper->Update();
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(actor);
 
  vtkSmartPointer<vtkInteractorStyleImage> style = 
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  renderWindowInteractor->SetInteractorStyle( style );
  
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Glyph2D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Glyph2D MACOSX_BUNDLE Glyph2D.cxx)
 
target_link_libraries(Glyph2D ${VTK_LIBRARIES})
```

**Download and Build Glyph2D**

Click [here to download Glyph2D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Glyph2D.tar) and its *CMakeLists.txt* file.
Once the *tarball Glyph2D.tar* has been downloaded and extracted,
```
cd Glyph2D/build 
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
./Glyph2D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

