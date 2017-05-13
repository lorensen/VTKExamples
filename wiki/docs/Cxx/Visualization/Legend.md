[VTKExamples](Home)/[Cxx](Cxx)/Visualization/Legend

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestLegend.png" width="256" />

**Legend.cxx**
```c++
#include <vtkVersion.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkLegendBoxActor.h>
#include <vtkNamedColors.h>

#include <vtkSmartPointer.h>
 
int main (int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5000.0);
  sphereSource->Update();

  vtkPolyData* polydata = sphereSource->GetOutput();
 
  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInput(polydata);
#else
  mapper->SetInputData(polydata);
#endif
 
  // Create an actor
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
 
  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  vtkSmartPointer<vtkLegendBoxActor> legend = 
    vtkSmartPointer<vtkLegendBoxActor>::New();
  legend->SetNumberOfEntries(2);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  double color[4];

  vtkSmartPointer<vtkCubeSource> legendBox = 
    vtkSmartPointer<vtkCubeSource>::New();
  legendBox->Update();
  colors->GetColor("tomato", color);
  legend->SetEntry(0, legendBox->GetOutput(), "Box", color);

  colors->GetColor("banana", color);
  legend->SetEntry(1, sphereSource->GetOutput(), "Ball", color);
  
  // place legend in lower right
  legend->GetPositionCoordinate()->SetCoordinateSystemToView();
  legend->GetPositionCoordinate()->SetValue(.5, -1.0);

  legend->GetPosition2Coordinate()->SetCoordinateSystemToView();
  legend->GetPosition2Coordinate()->SetValue(1.0, -0.5);

  legend->UseBackgroundOn();
  double background[4];
  colors->GetColor("warm_grey", background);
  legend->SetBackgroundColor(background);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->AddActor(legend);
  renderer->SetBackground(0,1,1); // Background color cyan
 
  // Render an image (lights and cameras are created automatically)
  renderWindow->Render();
 
  // Begin mouse interaction
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Legend)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Legend MACOSX_BUNDLE Legend.cxx)
 
target_link_libraries(Legend ${VTK_LIBRARIES})
```

**Download and Build Legend**

Click [here to download Legend](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Legend.tar) and its *CMakeLists.txt* file.
Once the *tarball Legend.tar* has been downloaded and extracted,
```
cd Legend/build 
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
./Legend
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

