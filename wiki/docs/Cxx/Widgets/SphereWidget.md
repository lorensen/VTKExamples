[VTKExamples](Home)/[Cxx](Cxx)/Widgets/SphereWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Widgets/TestSphereWidget.png" width="256" />

**SphereWidget.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkSphereWidget.h>
#include <vtkSphereRepresentation.h>
#include <vtkCommand.h>

class SphereCallback : public vtkCommand
{
  public:
    static SphereCallback *New()
    {
      return new SphereCallback;
    }
    SphereCallback(){}
    
    virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      
      vtkSphereWidget *sphereWidget = 
          reinterpret_cast<vtkSphereWidget*>(caller);
      
      double center[3];
      sphereWidget->GetCenter(center);
      std::cout << "Center: " << center[0] << " " << center[1] << " " << center[2] << std::endl;
    }
    
};

int main(int, char *[])
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

  vtkSmartPointer<vtkSphereWidget> sphereWidget = 
    vtkSmartPointer<vtkSphereWidget>::New();
  sphereWidget->SetInteractor(renderWindowInteractor);
  sphereWidget->SetRepresentationToSurface();
  
  vtkSmartPointer<SphereCallback> sphereCallback = 
    vtkSmartPointer<SphereCallback>::New();
 
  sphereWidget->AddObserver(vtkCommand::InteractionEvent,sphereCallback);
  
  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  sphereWidget->On();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SphereWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SphereWidget MACOSX_BUNDLE SphereWidget.cxx)
 
target_link_libraries(SphereWidget ${VTK_LIBRARIES})
```

**Download and Build SphereWidget**

Click [here to download SphereWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SphereWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball SphereWidget.tar* has been downloaded and extracted,
```
cd SphereWidget/build 
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
./SphereWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

