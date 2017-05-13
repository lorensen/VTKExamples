[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/QuadraticSurface

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestQuadraticSurface.png?raw=true" width="256" />

### Description
This example demonstrates how to create and display a quadratic surface.

**QuadraticSurface.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkQuadric.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>

int main(int, char *[])
{
  // Create the quadric function definition
  vtkSmartPointer<vtkQuadric> quadric =
    vtkSmartPointer<vtkQuadric>::New();
  quadric->SetCoefficients(.5,1,.2,0,.1,0,0,.2,0,0);
 
  // Sample the quadric function
  vtkSmartPointer<vtkSampleFunction> sample =
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(50,50,50);
  sample->SetImplicitFunction(quadric);
  double xmin = 0, xmax=1, ymin=0, ymax=1, zmin=0, zmax=1;
  sample->SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax);
 
  vtkSmartPointer<vtkContourFilter> contourFilter =
    vtkSmartPointer<vtkContourFilter>::New();
  contourFilter->SetInputConnection(sample->GetOutputPort());
  contourFilter->GenerateValues(1, 1.0, 1.0);
  contourFilter->Update();
  
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(contourFilter->GetOutputPort());
 
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
 
PROJECT(QuadraticSurface)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(QuadraticSurface MACOSX_BUNDLE QuadraticSurface.cxx)
 
target_link_libraries(QuadraticSurface ${VTK_LIBRARIES})
```

**Download and Build QuadraticSurface**

Click [here to download QuadraticSurface](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/QuadraticSurface.tar) and its *CMakeLists.txt* file.
Once the *tarball QuadraticSurface.tar* has been downloaded and extracted,
```
cd QuadraticSurface/build 
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
./QuadraticSurface
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

