[VTKExamples](/index/)/[Cxx](/Cxx)/Filtering/Glyph3D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestGlyph3D.png?raw=true" width="256" />

### Description
This example applies an object at every point. We use a cube for the demo.

**Glyph3D.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkGlyph3D.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,1,1);
  points->InsertNextPoint(2,2,2);
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
 
  vtkSmartPointer<vtkPolyData> glyph = 
    vtkSmartPointer<vtkPolyData>::New();
  // Create anything you want here, we will use a cube for the demo.
  vtkSmartPointer<vtkCubeSource> cubeSource = 
      vtkSmartPointer<vtkCubeSource>::New();
 
  vtkSmartPointer<vtkGlyph3D> glyph3D = 
    vtkSmartPointer<vtkGlyph3D>::New();
#if VTK_MAJOR_VERSION <= 5
  glyph3D->SetSource(cubeSource->GetOutput());
  glyph3D->SetInput(polydata);
#else
  glyph3D->SetSourceConnection(cubeSource->GetOutputPort());
  glyph3D->SetInputData(polydata);
#endif
  glyph3D->Update();
    
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyph3D->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green
 
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Glyph3D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Glyph3D MACOSX_BUNDLE Glyph3D.cxx)
 
target_link_libraries(Glyph3D ${VTK_LIBRARIES})
```

**Download and Build Glyph3D**

Click [here to download Glyph3D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Glyph3D.tar) and its *CMakeLists.txt* file.
Once the *tarball Glyph3D.tar* has been downloaded and extracted,
```
cd Glyph3D/build 
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
./Glyph3D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

