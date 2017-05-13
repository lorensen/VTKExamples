[VTKExamples](/index/)/[Cxx](/Cxx)/Visualization/RotateActor

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestRotateActor.png?raw=true" width="256" />

### Description
This example shows how to rotate an actor. It also shows how to get the current transformation of the actor so it can then be applied to the actual object if so desired.

**RotateActor.cxx**
```c++
#include <vtkConeSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkObjectFactory.h>
#include <vtkMatrix4x4.h>

// Define interaction style
class MyInteractorStyle : public vtkInteractorStyleTrackballActor
{
  public:
    static MyInteractorStyle* New();
    vtkTypeMacro(MyInteractorStyle, vtkInteractorStyleTrackballActor);
 
    virtual void OnLeftButtonDown() 
    {
      std::cout << "Pressed left mouse button." << std::endl;
      
      vtkSmartPointer<vtkMatrix4x4> m = 
          vtkSmartPointer<vtkMatrix4x4>::New();
      this->Actor->GetMatrix(m);
      std::cout << "Matrix: " << endl << *m << std::endl;
      
      // Forward events
      vtkInteractorStyleTrackballActor::OnLeftButtonDown();
    }
    
    virtual void OnLeftButtonUp() 
    {
      std::cout << "Released left mouse button." << std::endl;
      
      vtkSmartPointer<vtkMatrix4x4> m = 
          vtkSmartPointer<vtkMatrix4x4>::New();
      this->Actor->GetMatrix(m);
      std::cout << "Matrix: " << endl << *m << std::endl;
      
      // Forward events
      vtkInteractorStyleTrackballActor::OnLeftButtonUp();
    }
    
    void SetActor(vtkSmartPointer<vtkActor> actor) {this->Actor = actor;}
    
  private:
    vtkSmartPointer<vtkActor> Actor;
 
 
};
vtkStandardNewMacro(MyInteractorStyle);

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkConeSource> coneSource = 
    vtkSmartPointer<vtkConeSource>::New();
  coneSource->Update();
  
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(coneSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->RotateY(45);
  
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  
  vtkSmartPointer<MyInteractorStyle> style = 
    vtkSmartPointer<MyInteractorStyle>::New();
  style->SetActor(actor);
  
  renderWindowInteractor->SetInteractorStyle( style );

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); //white

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
         
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RotateActor)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RotateActor MACOSX_BUNDLE RotateActor.cxx)
 
target_link_libraries(RotateActor ${VTK_LIBRARIES})
```

**Download and Build RotateActor**

Click [here to download RotateActor](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RotateActor.tar) and its *CMakeLists.txt* file.
Once the *tarball RotateActor.tar* has been downloaded and extracted,
```
cd RotateActor/build 
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
./RotateActor
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

