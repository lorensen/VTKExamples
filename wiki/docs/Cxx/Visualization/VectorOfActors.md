[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/VectorOfActors

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestVectorOfActors.png?raw=true" width="256" />

### Description
This example creates multiple actors and stores them in a vector. The resulting image is 10 spheres in a line.

**VectorOfActors.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleTrackball.h>

#include <vector>

int main(int, char *[])
{
  std::vector<vtkSmartPointer<vtkActor> > actors;

  for(unsigned int i = 0; i < 10; i++)
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(i, 0.0, 0.0);
    sphereSource->SetRadius(.2);

    vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    actors.push_back(actor);
  }


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
  for(unsigned int i = 0; i < actors.size(); i++)
  {
    renderer->AddActor(actors[i]);
  }

  renderer->SetBackground(1,1,1); // Background color white

  // Render
  renderWindow->Render();

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

  renderWindowInteractor->SetInteractorStyle( style );

  // Begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(VectorOfActors)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VectorOfActors MACOSX_BUNDLE VectorOfActors.cxx)
 
target_link_libraries(VectorOfActors ${VTK_LIBRARIES})
```

**Download and Build VectorOfActors**

Click [here to download VectorOfActors](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VectorOfActors.tar) and its *CMakeLists.txt* file.
Once the *tarball VectorOfActors.tar* has been downloaded and extracted,
```
cd VectorOfActors/build 
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
./VectorOfActors
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

