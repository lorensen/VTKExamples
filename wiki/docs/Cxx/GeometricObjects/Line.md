[VTKExamples](/home/)/[Cxx](/Cxx)/GeometricObjects/Line

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestLine.png?raw=true" width="256" />

**Line.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkLineSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
 
int main(int, char *[])
{
  // Create two points, P0 and P1
  double p0[3] = {1.0, 0.0, 0.0};
  double p1[3] = {0.0, 1.0, 0.0};

  vtkSmartPointer<vtkLineSource> lineSource = 
    vtkSmartPointer<vtkLineSource>::New();
  lineSource->SetPoint1(p0);
  lineSource->SetPoint2(p1);
  lineSource->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(lineSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetLineWidth(4);
 
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
 
PROJECT(Line)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Line MACOSX_BUNDLE Line.cxx)
 
target_link_libraries(Line ${VTK_LIBRARIES})
```

**Download and Build Line**

Click [here to download Line](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Line.tar) and its *CMakeLists.txt* file.
Once the *tarball Line.tar* has been downloaded and extracted,
```
cd Line/build 
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
./Line
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

