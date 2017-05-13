[VTKExamples](/home/)/[Cxx](/Cxx)/Interaction/RubberBand3D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Interaction/TestRubberBand3D.png?raw=true" width="256" />

**RubberBand3D.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleRubberBand3D.h>
#include <vtkObjectFactory.h>

class MyRubberBand3D : public vtkInteractorStyleRubberBand3D
{
  public:
    static MyRubberBand3D* New();
    vtkTypeMacro(MyRubberBand3D, vtkInteractorStyleRubberBand3D);

    virtual void OnLeftButtonUp() 
    {
      // Forward events
      vtkInteractorStyleRubberBand3D::OnLeftButtonUp();
 
      std::cout << "Start position: " << this->StartPosition[0] << " " << this->StartPosition[1] << std::endl;
      std::cout << "End position: " << this->EndPosition[0] << " " << this->EndPosition[1] << std::endl;
    }
 
};
vtkStandardNewMacro(MyRubberBand3D);

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  
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

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();

  vtkSmartPointer<MyRubberBand3D> style = 
    vtkSmartPointer<MyRubberBand3D>::New();
  renderWindowInteractor->SetInteractorStyle( style );
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RubberBand3D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RubberBand3D MACOSX_BUNDLE RubberBand3D.cxx)
 
target_link_libraries(RubberBand3D ${VTK_LIBRARIES})
```

**Download and Build RubberBand3D**

Click [here to download RubberBand3D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RubberBand3D.tar) and its *CMakeLists.txt* file.
Once the *tarball RubberBand3D.tar* has been downloaded and extracted,
```
cd RubberBand3D/build 
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
./RubberBand3D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

