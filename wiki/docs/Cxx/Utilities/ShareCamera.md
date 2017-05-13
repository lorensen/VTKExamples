[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/ShareCamera

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Utilities/TestShareCamera.png?raw=true" width="256" />

**ShareCamera.cxx**
```c++
#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  double xmins[4] = {0,.5,0,.5};
  double xmaxs[4] = {0.5,1,0.5,1};
  double ymins[4] = {0,0,.5,.5};
  double ymaxs[4]= {0.5,0.5,1,1};

  vtkCamera* camera;

  for(unsigned i = 0; i < 4; i++)
  {
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

    renderWindow->AddRenderer(renderer);

    if(i == 0)
    {
      camera = renderer->GetActiveCamera();
    }
    else
    {
      renderer->SetActiveCamera(camera);
    }
    renderer->SetViewport(xmins[i],ymins[i],xmaxs[i],ymaxs[i]);

    // Create a sphere
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(0.0, 0.0, 0.0);
    sphereSource->SetRadius(5);
    sphereSource->Update();

    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    renderer->AddActor(actor);
    renderer->ResetCamera();

    renderWindow->Render();
    renderWindow->SetWindowName("Multiple ViewPorts");

  }

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ShareCamera)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ShareCamera MACOSX_BUNDLE ShareCamera.cxx)
 
target_link_libraries(ShareCamera ${VTK_LIBRARIES})
```

**Download and Build ShareCamera**

Click [here to download ShareCamera](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ShareCamera.tar) and its *CMakeLists.txt* file.
Once the *tarball ShareCamera.tar* has been downloaded and extracted,
```
cd ShareCamera/build 
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
./ShareCamera
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

