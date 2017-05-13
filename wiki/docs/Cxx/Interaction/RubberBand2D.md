[VTKExamples](Home)/[Cxx](Cxx)/Interaction/RubberBand2D

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Interaction/TestRubberBand2D.png" width="256" />

### Description
This example shows how to get the coordinates of the corners of the rubber band (the box that is drawn).

**RubberBand2D.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleRubberBand2D.h>
#include <vtkObjectFactory.h>
 
class MyRubberBand : public vtkInteractorStyleRubberBand2D
{
  public:
    static MyRubberBand* New();
    vtkTypeMacro(MyRubberBand, vtkInteractorStyleRubberBand2D);
 
    virtual void OnLeftButtonUp() 
    {
      // Forward events
      vtkInteractorStyleRubberBand2D::OnLeftButtonUp();
 
      std::cout << "Start position: " << this->StartPosition[0] << " " << this->StartPosition[1] << std::endl;
      std::cout << "End position: " << this->EndPosition[0] << " " << this->EndPosition[1] << std::endl;
    }
 
};

vtkStandardNewMacro(MyRubberBand);
 
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
 
  // Render
  renderWindow->Render();
 
  vtkSmartPointer<MyRubberBand> style = 
    vtkSmartPointer<MyRubberBand>::New();
  renderWindowInteractor->SetInteractorStyle( style );

  // Begin mouse interaction
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RubberBand2D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RubberBand2D MACOSX_BUNDLE RubberBand2D.cxx)
 
target_link_libraries(RubberBand2D ${VTK_LIBRARIES})
```

**Download and Build RubberBand2D**

Click [here to download RubberBand2D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RubberBand2D.tar) and its *CMakeLists.txt* file.
Once the *tarball RubberBand2D.tar* has been downloaded and extracted,
```
cd RubberBand2D/build 
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
./RubberBand2D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

