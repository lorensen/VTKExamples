[VTKExamples](/index/)/[Cxx](/Cxx)/Visualization/MultipleRenderWindows

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestMultipleRenderWindows.png?raw=true" width="256" />

### Description
This example creates 4 render windows. When you close one, the next one opens? Or do they all open simultaneously?

**MultipleRenderWindows.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

#include <sstream>
#include <vector>

int main(int, char *[])
{
  std::vector<vtkSmartPointer<vtkRenderWindowInteractor> > interactors;

  for(unsigned int i = 0; i < 4; i++)
  {
    vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();

    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();

    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();

    interactors.push_back(renderWindowInteractor);

    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindow->Render();
    std::stringstream ss;
    ss << "Window " << i;
    renderWindow->SetWindowName(ss.str().c_str());
    renderWindow->SetPosition(i*300,0);

    //create a sphere
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(0.0, 0.0, 0.0);
    sphereSource->SetRadius(5.0);
    sphereSource->Update();

    //Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    renderer->AddActor(actor);
    renderer->ResetCamera();
  }

  interactors[3]->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MultipleRenderWindows)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MultipleRenderWindows MACOSX_BUNDLE MultipleRenderWindows.cxx)
 
target_link_libraries(MultipleRenderWindows ${VTK_LIBRARIES})
```

**Download and Build MultipleRenderWindows**

Click [here to download MultipleRenderWindows](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MultipleRenderWindows.tar) and its *CMakeLists.txt* file.
Once the *tarball MultipleRenderWindows.tar* has been downloaded and extracted,
```
cd MultipleRenderWindows/build 
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
./MultipleRenderWindows
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

