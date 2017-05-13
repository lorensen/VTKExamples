[VTKExamples](/index/)/[Cxx](/Cxx)/Images/RTAnalyticSource

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestRTAnalyticSource.png?raw=true" width="256" />

**RTAnalyticSource.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkImageData.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRTAnalyticSource.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkRTAnalyticSource> analyticSource =
    vtkSmartPointer<vtkRTAnalyticSource>::New();
  analyticSource->SetWholeExtent(-10,10, -10,10, 0,0);
  
  vtkSmartPointer<vtkImageActor> imageActor =
    vtkSmartPointer<vtkImageActor>::New();
  imageActor->GetMapper()->SetInputConnection(
    analyticSource->GetOutputPort());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle( style );

  interactor->SetRenderWindow(renderWindow);

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(1,0,0);
  renderWindow->AddRenderer(renderer);

  renderer->AddActor(imageActor);

  renderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RTAnalyticSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RTAnalyticSource MACOSX_BUNDLE RTAnalyticSource.cxx)
 
target_link_libraries(RTAnalyticSource ${VTK_LIBRARIES})
```

**Download and Build RTAnalyticSource**

Click [here to download RTAnalyticSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RTAnalyticSource.tar) and its *CMakeLists.txt* file.
Once the *tarball RTAnalyticSource.tar* has been downloaded and extracted,
```
cd RTAnalyticSource/build 
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
./RTAnalyticSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

