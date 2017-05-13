[VTKExamples](/home/)/[Cxx](/Cxx)/Meshes/Triangulate

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Meshes/TestTriangulate.png?raw=true" width="256" />

**Triangulate.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkTriangleFilter.h>
#include <vtkRegularPolygonSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkRegularPolygonSource> polygonSource =
    vtkSmartPointer<vtkRegularPolygonSource>::New();
  polygonSource->Update();

  vtkSmartPointer<vtkTriangleFilter> triangleFilter =
    vtkSmartPointer<vtkTriangleFilter>::New();
  triangleFilter->SetInputConnection(polygonSource->GetOutputPort());
  triangleFilter->Update();

  vtkSmartPointer<vtkPolyDataMapper> inputMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  inputMapper->SetInputConnection(polygonSource->GetOutputPort());
  vtkSmartPointer<vtkActor> inputActor =
      vtkSmartPointer<vtkActor>::New();
  inputActor->SetMapper(inputMapper);
  inputActor->GetProperty()->SetRepresentationToWireframe();

  vtkSmartPointer<vtkPolyDataMapper> triangleMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  triangleMapper->SetInputConnection(triangleFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> triangleActor =
      vtkSmartPointer<vtkActor>::New();
  triangleActor->SetMapper(triangleMapper);
  triangleActor->GetProperty()->SetRepresentationToWireframe();
  
  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  // And one interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  leftRenderer->AddActor(inputActor);
  rightRenderer->AddActor(triangleActor);

  leftRenderer->ResetCamera();

  rightRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Triangulate)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Triangulate MACOSX_BUNDLE Triangulate.cxx)
 
target_link_libraries(Triangulate ${VTK_LIBRARIES})
```

**Download and Build Triangulate**

Click [here to download Triangulate](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Triangulate.tar) and its *CMakeLists.txt* file.
Once the *tarball Triangulate.tar* has been downloaded and extracted,
```
cd Triangulate/build 
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
./Triangulate
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

