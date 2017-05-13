[VTKExamples](Home)/[Cxx](Cxx)/Widgets/BoxWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Widgets/TestBoxWidget.png" width="256" />

### Description
This example uses a vtkBoxWidget to manipulate an actor. The class includes geometry to draw a box around the object, which is bound to it via *SetProp3D*. The box is dimensioned using the *SetPlaceFactor* method, and positioned with the *PlaceWidget* method. After the initial setup, synchronizing the box with the object is done through a custom callback class, which is passed to the box widget through the *AddObserver* method.

For a widget that isn't tied to a specific vtkProp3D and has its geometric representation separate from the interaction logic, see the [example BoxWidget2]([Cxx/Widgets/BoxWidget2).

**BoxWidget.cxx**
```c++
#include <vtkSmartPointer.h>
// For the rendering pipeline setup:
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
// For vtkBoxWidget:
#include <vtkBoxWidget.h>
#include <vtkCommand.h>
#include <vtkTransform.h>

class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New()
  {
    return new vtkMyCallback;
  }
  virtual void Execute( vtkObject *caller, unsigned long, void* )
  {
    // Here we use the vtkBoxWidget to transform the underlying coneActor
    // (by manipulating its transformation matrix).
    vtkSmartPointer<vtkTransform> t =
      vtkSmartPointer<vtkTransform>::New();
    vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
    widget->GetTransform( t );
    widget->GetProp3D()->SetUserTransform( t );
  }
};

int main( int vtkNotUsed( argc ), char* vtkNotUsed( argv )[] )
{
  vtkSmartPointer<vtkConeSource> cone =
    vtkSmartPointer<vtkConeSource>::New();

  vtkSmartPointer<vtkPolyDataMapper> coneMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection( cone->GetOutputPort() );

  vtkSmartPointer<vtkActor> coneActor =
    vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper( coneMapper );

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor( coneActor );
  renderer->SetBackground( 0.1, 0.2, 0.4 );

  vtkSmartPointer<vtkRenderWindow> window =
    vtkSmartPointer<vtkRenderWindow>::New();
  window->AddRenderer( renderer );
  window->SetSize( 300, 300 );

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow( window );

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  interactor->SetInteractorStyle( style );

  vtkSmartPointer<vtkBoxWidget> boxWidget =
    vtkSmartPointer<vtkBoxWidget>::New();
  boxWidget->SetInteractor( interactor );

  boxWidget->SetProp3D( coneActor );
  boxWidget->SetPlaceFactor( 1.25 ); // Make the box 1.25x larger than the actor
  boxWidget->PlaceWidget();

  vtkSmartPointer<vtkMyCallback> callback =
    vtkSmartPointer<vtkMyCallback>::New();
  boxWidget->AddObserver( vtkCommand::InteractionEvent, callback );

  boxWidget->On();

  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BoxWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BoxWidget MACOSX_BUNDLE BoxWidget.cxx)
 
target_link_libraries(BoxWidget ${VTK_LIBRARIES})
```

**Download and Build BoxWidget**

Click [here to download BoxWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BoxWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball BoxWidget.tar* has been downloaded and extracted,
```
cd BoxWidget/build 
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
./BoxWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

