[VTKExamples](Home)/[Cxx](Cxx)/Visualization/Follower

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestFollower.png" width="256" />

### Description
The text is a 3D actor and is placed in 3D space, but stays right side up and facing the camera, while the cube does not.

**Follower.cxx**
```c++
#include <vtkActor.h>
#include <vtkCubeSource.h>
#include <vtkFollower.h>
#include <vtkInteractorStyle.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkVectorText.h>

int main(int, char *[])
{
  // Create some text
  vtkSmartPointer<vtkVectorText> textSource = 
    vtkSmartPointer<vtkVectorText>::New();
  textSource->SetText( "Hello" );

  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection( textSource->GetOutputPort() );

  // Create a subclass of vtkActor: a vtkFollower that remains facing the camera
  vtkSmartPointer<vtkFollower> follower = 
    vtkSmartPointer<vtkFollower>::New();
  follower->SetMapper( mapper );
  follower->GetProperty()->SetColor( 1, 0, 0 ); // red 

  // Create a transparent cube that does not move around to face the camera
  vtkSmartPointer<vtkCubeSource> cubeSource = 
    vtkSmartPointer<vtkCubeSource>::New();
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection( cubeSource->GetOutputPort() );
  vtkSmartPointer<vtkActor> cubeActor = 
    vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper( cubeMapper );
  cubeActor->GetProperty()->SetColor( 0, 0, 1 ); // blue
  cubeActor->GetProperty()->SetOpacity( 0.3 );

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkInteractorStyle::SafeDownCast(renderWindowInteractor->GetInteractorStyle())->AutoAdjustCameraClippingRangeOn();
  renderWindowInteractor->SetRenderWindow( renderWindow );

  // Add the actor to the scene
  renderer->AddActor( follower );
  renderer->AddActor( cubeActor );
  renderer->SetBackground( 1, 1, 1 ); // Background color white
  follower->SetCamera( renderer->GetActiveCamera() );

  // Render and interact
  renderWindow->Render();
  renderer->ResetCamera();
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Follower)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Follower MACOSX_BUNDLE Follower.cxx)
 
target_link_libraries(Follower ${VTK_LIBRARIES})
```

**Download and Build Follower**

Click [here to download Follower](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Follower.tar) and its *CMakeLists.txt* file.
Once the *tarball Follower.tar* has been downloaded and extracted,
```
cd Follower/build 
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
./Follower
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

