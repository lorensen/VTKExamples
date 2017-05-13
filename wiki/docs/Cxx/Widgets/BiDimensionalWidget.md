[VTKExamples](Home)/[Cxx](Cxx)/Widgets/BiDimensionalWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Widgets/TestBiDimensionalWidget.png" width="256" />

**BiDimensionalWidget.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkBiDimensionalWidget.h>
#include <vtkBiDimensionalRepresentation2D.h>
#include <vtkCommand.h>

class vtkBiDimensionalCallback : public vtkCommand
{
  public:
    static vtkBiDimensionalCallback *New()
    {
      return new vtkBiDimensionalCallback;
    }
    
    virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      
      vtkBiDimensionalWidget *biDimensionalWidget = 
          reinterpret_cast<vtkBiDimensionalWidget*>(caller);
      
      vtkBiDimensionalRepresentation2D* representation = 
          static_cast<vtkBiDimensionalRepresentation2D*>(biDimensionalWidget->GetRepresentation());
      
      double p1[3];
      representation->GetPoint1DisplayPosition(p1);
      double p2[3];
      representation->GetPoint1DisplayPosition(p2);
      double p3[3];
      representation->GetPoint1DisplayPosition(p3);
      double p4[3];
      representation->GetPoint1DisplayPosition(p4);
      
      // Display one of the points, just so we know it's working
      std::cout << "P1: " << p1[0] << " " << p1[1] << " " << p1[2] << std::endl;
      
    }
    vtkBiDimensionalCallback(){}
    
};
 
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

  vtkSmartPointer<vtkBiDimensionalWidget> biDimensionalWidget = 
    vtkSmartPointer<vtkBiDimensionalWidget>::New();
  biDimensionalWidget->SetInteractor(renderWindowInteractor);
  biDimensionalWidget->CreateDefaultRepresentation();
  
  vtkSmartPointer<vtkBiDimensionalCallback> biDimensionalCallback = 
      vtkSmartPointer<vtkBiDimensionalCallback>::New();
 
  biDimensionalWidget->AddObserver(vtkCommand::InteractionEvent,biDimensionalCallback);
  
  // Render an image (lights and cameras are created automatically)
  renderWindow->Render();
  
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  biDimensionalWidget->On();
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BiDimensionalWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BiDimensionalWidget MACOSX_BUNDLE BiDimensionalWidget.cxx)
 
target_link_libraries(BiDimensionalWidget ${VTK_LIBRARIES})
```

**Download and Build BiDimensionalWidget**

Click [here to download BiDimensionalWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BiDimensionalWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball BiDimensionalWidget.tar* has been downloaded and extracted,
```
cd BiDimensionalWidget/build 
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
./BiDimensionalWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

