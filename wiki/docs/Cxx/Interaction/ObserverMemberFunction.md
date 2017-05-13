[VTKExamples](/home/)/[Cxx](/Cxx)/Interaction/ObserverMemberFunction

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Interaction/TestObserverMemberFunction.png?raw=true" width="256" />

### Description
You must use the git version of VTK from at least 10/11/2010 to use this functionality.

**ObserverMemberFunction.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkObjectFactory.h>
#include <vtkCommand.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyle.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballCamera.h>

// A class not derived from vtkObjectBase
class MyClass
{
  public:
    void KeypressCallbackFunction(vtkObject*,
                                  long unsigned int vtkNotUsed(eventId),
                                  void* vtkNotUsed(callData))
    {
    std::cout << "Caught event in MyClass" << std::endl;
    }

};

// A class that is derived from vtkObjectBase
class MyInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
  static MyInteractorStyle* New();
  vtkTypeMacro(MyInteractorStyle, vtkInteractorStyleTrackballCamera);

  void KeypressCallbackFunction(vtkObject*,
                                long unsigned int vtkNotUsed(eventId),
                                void* vtkNotUsed(callData) )
  {
    std::cout << "Caught event in MyInteractorStyle" << std::endl;
  }

};
vtkStandardNewMacro(MyInteractorStyle);

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  // Create an actor
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

  MyClass myClass;
  renderWindowInteractor->AddObserver(vtkCommand::KeyPressEvent, &myClass, &MyClass::KeypressCallbackFunction);

  MyInteractorStyle* style = MyInteractorStyle::New();
  renderWindowInteractor->AddObserver(vtkCommand::KeyPressEvent, style, &MyInteractorStyle::KeypressCallbackFunction);

  vtkSmartPointer<MyInteractorStyle> style2 =
    vtkSmartPointer<MyInteractorStyle>::New();
  renderWindowInteractor->AddObserver(vtkCommand::KeyPressEvent, style2, &MyInteractorStyle::KeypressCallbackFunction);

  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white
  renderWindow->Render();
  renderWindowInteractor->Start();

  style->Delete();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ObserverMemberFunction)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ObserverMemberFunction MACOSX_BUNDLE ObserverMemberFunction.cxx)
 
target_link_libraries(ObserverMemberFunction ${VTK_LIBRARIES})
```

**Download and Build ObserverMemberFunction**

Click [here to download ObserverMemberFunction](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ObserverMemberFunction.tar) and its *CMakeLists.txt* file.
Once the *tarball ObserverMemberFunction.tar* has been downloaded and extracted,
```
cd ObserverMemberFunction/build 
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
./ObserverMemberFunction
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

