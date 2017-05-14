[VTKExamples](/index/)/[Cxx](/Cxx)/Visualization/ScaleGlyphs

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestScaleGlyphs.png?raw=true" width="256" />

**ScaleGlyphs.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
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
#include <vtkFloatArray.h>

int main(int, char *[])
{
  // Create points
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(5,0,0);
  points->InsertNextPoint(10,0,0);
  
  // Setup scales
  vtkSmartPointer<vtkFloatArray> scales = 
    vtkSmartPointer<vtkFloatArray>::New();
  scales->SetName("scales");
 
  scales->InsertNextValue(1.0);
  scales->InsertNextValue(2.0);
  scales->InsertNextValue(3.0);
    
  // Combine into a polydata
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->GetPointData()->SetScalars(scales);
  
  // Create anything you want here, we will use a cube for the demo.
  vtkSmartPointer<vtkCubeSource> cubeSource = 
    vtkSmartPointer<vtkCubeSource>::New();
  
  vtkSmartPointer<vtkGlyph3D> glyph3D = 
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph3D->SetScaleModeToScaleByScalar();
  glyph3D->SetSourceConnection(cubeSource->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
  glyph3D->SetInput(polydata);
#else
  glyph3D->SetInputData(polydata);
#endif
  glyph3D->Update();
  
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyph3D->GetOutputPort());
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
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
  renderer->SetBackground(1,1,1); // Background color white
 
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ScaleGlyphs)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ScaleGlyphs MACOSX_BUNDLE ScaleGlyphs.cxx)
 
target_link_libraries(ScaleGlyphs ${VTK_LIBRARIES})
```

**Download and Build ScaleGlyphs**

Click [here to download ScaleGlyphs](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ScaleGlyphs.tar) and its *CMakeLists.txt* file.
Once the *tarball ScaleGlyphs.tar* has been downloaded and extracted,
```
cd ScaleGlyphs/build 
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
./ScaleGlyphs
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

