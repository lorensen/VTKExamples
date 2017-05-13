[VTKExamples](Home)/[Cxx](Cxx)/Widgets/SeedWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Widgets/TestSeedWidget.png" width="256" />

### Description
This example demonstrates how to use vtkSeedWidget, which generates (seeds) points to be placed in the scene in the locations where the user clicks.

The points can then be used for operations like connectivity, segmentation, and region growing. For an example using a custom callback where such operations can be assembled, see []([../SeedWidgetWithCustomCallback])

**SeedWidget.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSeedWidget.h>
#include <vtkSeedRepresentation.h>
#include <vtkPointHandleRepresentation2D.h>
#include <vtkProperty2D.h> // For setting the color in the handles

int main( int vtkNotUsed( argc ), char* vtkNotUsed( argv )[] )
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> window =
    vtkSmartPointer<vtkRenderWindow>::New();
  window->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow( window );

  // Create the representation for the seed widget and for its handles
  vtkSmartPointer<vtkPointHandleRepresentation2D> handleRep =
    vtkSmartPointer<vtkPointHandleRepresentation2D>::New();
  handleRep->GetProperty()->SetColor( 1, 1, 0 ); // Make the handles yellow
  vtkSmartPointer<vtkSeedRepresentation> widgetRep =
    vtkSmartPointer<vtkSeedRepresentation>::New();
  widgetRep->SetHandleRepresentation( handleRep );

  // Create the seed widget
  vtkSmartPointer<vtkSeedWidget> seedWidget =
    vtkSmartPointer<vtkSeedWidget>::New();
  seedWidget->SetInteractor( interactor );
  seedWidget->SetRepresentation( widgetRep );

  seedWidget->On();
  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SeedWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SeedWidget MACOSX_BUNDLE SeedWidget.cxx)
 
target_link_libraries(SeedWidget ${VTK_LIBRARIES})
```

**Download and Build SeedWidget**

Click [here to download SeedWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SeedWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball SeedWidget.tar* has been downloaded and extracted,
```
cd SeedWidget/build 
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
./SeedWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

