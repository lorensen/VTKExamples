[VTKExamples](/home/)/[Cxx](/Cxx)/Widgets/AngleWidget2D

### Description
The arc is still visible?

**AngleWidget2D.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkAngleWidget.h>
#include <vtkAngleRepresentation2D.h>

int main(int argc, char *argv[])
{
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

  vtkSmartPointer<vtkAngleRepresentation2D> rep = 
    vtkSmartPointer<vtkAngleRepresentation2D>::New();
  rep->ArcVisibilityOff();
  
  vtkSmartPointer<vtkAngleWidget> angleWidget = 
    vtkSmartPointer<vtkAngleWidget>::New();
  angleWidget->SetRepresentation(rep);
  angleWidget->SetInteractor(renderWindowInteractor);
  angleWidget->CreateDefaultRepresentation();
  
  renderWindow->Render();
  
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  angleWidget->On();
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(AngleWidget2D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(AngleWidget2D MACOSX_BUNDLE AngleWidget2D.cxx)
 
target_link_libraries(AngleWidget2D ${VTK_LIBRARIES})
```

**Download and Build AngleWidget2D**

Click [here to download AngleWidget2D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/AngleWidget2D.tar) and its *CMakeLists.txt* file.
Once the *tarball AngleWidget2D.tar* has been downloaded and extracted,
```
cd AngleWidget2D/build 
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
./AngleWidget2D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

