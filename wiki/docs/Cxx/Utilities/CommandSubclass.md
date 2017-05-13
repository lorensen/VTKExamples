[VTKExamples](Home)/[Cxx](Cxx)/Utilities/CommandSubclass

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Utilities/TestCommandSubclass.png" width="256" />

**CommandSubclass.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>

class CommandSubclass2 : public vtkCommand
{
  public:
    vtkTypeMacro(CommandSubclass2, vtkCommand);
    
    static CommandSubclass2 *New()
    {
      return new CommandSubclass2;
    }
        
    void Execute(vtkObject *vtkNotUsed(caller), unsigned long vtkNotUsed(eventId), 
                        void *vtkNotUsed(callData))
    {
      std::cout << "timer callback" << std::endl;
    }

};

int main(int, char *[])
{
  // Create a sphere
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
 
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  
  // Initialize must be called prior to creating timer events.
  renderWindowInteractor->Initialize();
  renderWindowInteractor->CreateRepeatingTimer(500);
  
  vtkSmartPointer<CommandSubclass2> timerCallback = 
    vtkSmartPointer<CommandSubclass2>::New();
  renderWindowInteractor->AddObserver ( vtkCommand::TimerEvent, timerCallback );
  
  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white
 
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CommandSubclass)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CommandSubclass MACOSX_BUNDLE CommandSubclass.cxx)
 
target_link_libraries(CommandSubclass ${VTK_LIBRARIES})
```

**Download and Build CommandSubclass**

Click [here to download CommandSubclass](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CommandSubclass.tar) and its *CMakeLists.txt* file.
Once the *tarball CommandSubclass.tar* has been downloaded and extracted,
```
cd CommandSubclass/build 
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
./CommandSubclass
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

