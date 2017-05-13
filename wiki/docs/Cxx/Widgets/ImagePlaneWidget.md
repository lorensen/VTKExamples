[VTKExamples](Home)/[Cxx](Cxx)/Widgets/ImagePlaneWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Widgets/TestImagePlaneWidget.png" width="256" />

**ImagePlaneWidget.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkImagePlaneWidget.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkInteractorStyleTrackballCamera.h>

int main(int, char *[])
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
  
  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderer->AddActor(actor);
  
  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  
  //vtkSmartPointer<vtkInteractorStyleTrackballActor> style = 
    //vtkSmartPointer<vtkInteractorStyleTrackballActor>::New();
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  
  renderWindowInteractor->SetInteractorStyle( style );
  
  vtkSmartPointer<vtkImagePlaneWidget> planeWidget = 
    vtkSmartPointer<vtkImagePlaneWidget>::New();
  planeWidget->SetInteractor(renderWindowInteractor);
  planeWidget->TextureVisibilityOff();
  
  double origin[3] = {0, 1,0};
  planeWidget->SetOrigin(origin);
  planeWidget->UpdatePlacement();
    
  // Render
  renderWindow->Render();
  
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  planeWidget->On();
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImagePlaneWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImagePlaneWidget MACOSX_BUNDLE ImagePlaneWidget.cxx)
 
target_link_libraries(ImagePlaneWidget ${VTK_LIBRARIES})
```

**Download and Build ImagePlaneWidget**

Click [here to download ImagePlaneWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImagePlaneWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball ImagePlaneWidget.tar* has been downloaded and extracted,
```
cd ImagePlaneWidget/build 
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
./ImagePlaneWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

