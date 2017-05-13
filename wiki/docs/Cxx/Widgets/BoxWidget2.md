[VTKExamples](/index/)/[Cxx](/Cxx)/Widgets/BoxWidget2

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Widgets/TestBoxWidget2.png?raw=true" width="256" />

### Description
This example uses a {{class|vtkBoxWidget2}} to manipulate an actor. The widget only contains the interaction logic; the actual box is drawn by the accompanying {{class|vtkBoxRepresentation}}.
Contrary to the older {{class|vtkBoxWidget|older implementation}}, this widget doesn't provide functionality to assign it to one or more actors, so that has to be implemented manually. The box is dimensioned and positioned by passing a bounding box to <code>PlaceWidget</code> method, with the <code>SetPlaceFactor</code> method providing a scaling factor in relation to that bounding box. The transformations applied to the box can be used to manipulate any number of object(s), via a custom callback class, which is passed to the box widget through the <code>AddObserver</code> method.

The older implementation {{class|vtkBoxWidget}} provides functionality to receive a {{class|vtkProp3D}} for the initial positioning and sizing, but the transformation synchronization still needs to be done manually. See []([../BoxWidget|BoxWidget]) for a simple example of how to use it.

**BoxWidget2.cxx**
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
// For vtkBoxWidget2:
#include <vtkBoxWidget2.h>
#include <vtkBoxRepresentation.h>
#include <vtkCommand.h>
#include <vtkTransform.h>

class vtkBoxCallback : public vtkCommand
{
public:
  static vtkBoxCallback *New()
  {
    return new vtkBoxCallback;
  }

  vtkSmartPointer<vtkActor> m_actor;

  void SetActor( vtkSmartPointer<vtkActor> actor )
  {
    m_actor = actor;
  }

  virtual void Execute( vtkObject *caller, unsigned long, void* )
  {
    vtkSmartPointer<vtkBoxWidget2> boxWidget =
      vtkBoxWidget2::SafeDownCast(caller);

    vtkSmartPointer<vtkTransform> t =
      vtkSmartPointer<vtkTransform>::New();

    vtkBoxRepresentation::SafeDownCast( boxWidget->GetRepresentation() )->GetTransform( t );
    this->m_actor->SetUserTransform( t );
  }

  vtkBoxCallback(){}
};

int main( int vtkNotUsed( argc ), char* vtkNotUsed( argv )[] )
{
  vtkSmartPointer<vtkConeSource> coneSource =
    vtkSmartPointer<vtkConeSource>::New();
  coneSource->SetHeight( 1.5 );

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection( coneSource->GetOutputPort() );

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper( mapper );

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera(); // Reposition camera so the whole scene is visible

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow( renderWindow );

  // Use the "trackball camera" interactor style, rather than the default "joystick camera"
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  renderWindowInteractor->SetInteractorStyle( style );

  vtkSmartPointer<vtkBoxWidget2> boxWidget =
    vtkSmartPointer<vtkBoxWidget2>::New();
  boxWidget->SetInteractor( renderWindowInteractor );
  boxWidget->GetRepresentation()->SetPlaceFactor( 1 ); // Default is 0.5
  boxWidget->GetRepresentation()->PlaceWidget(actor->GetBounds());
  
  // Set up a callback for the interactor to call so we can manipulate the actor
  vtkSmartPointer<vtkBoxCallback> boxCallback =
    vtkSmartPointer<vtkBoxCallback>::New();
  boxCallback->SetActor(actor);
  boxWidget->AddObserver( vtkCommand::InteractionEvent, boxCallback );

  boxWidget->On();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BoxWidget2)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BoxWidget2 MACOSX_BUNDLE BoxWidget2.cxx)
 
target_link_libraries(BoxWidget2 ${VTK_LIBRARIES})
```

**Download and Build BoxWidget2**

Click [here to download BoxWidget2](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BoxWidget2.tar) and its *CMakeLists.txt* file.
Once the *tarball BoxWidget2.tar* has been downloaded and extracted,
```
cd BoxWidget2/build 
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
./BoxWidget2
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

