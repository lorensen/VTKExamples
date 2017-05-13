[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/ColorDisconnectedRegions

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestColorDisconnectedRegions.png?raw=true" width="256" />

**ColorDisconnectedRegions.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>

int main(int, char*[])
{
  // Create some spheres
  vtkSmartPointer<vtkSphereSource> sphereSource1 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->Update();

  vtkSmartPointer<vtkSphereSource> sphereSource2 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetCenter(5,0,0);
  sphereSource2->Update();

  vtkSmartPointer<vtkSphereSource> sphereSource3 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource3->SetCenter(10,0,0);
  sphereSource3->Update();

  vtkSmartPointer<vtkAppendPolyData> appendFilter =
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendFilter->AddInputConnection(sphereSource1->GetOutputPort());
  appendFilter->AddInputConnection(sphereSource2->GetOutputPort());
  appendFilter->AddInputConnection(sphereSource3->GetOutputPort());
  appendFilter->Update();

  vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter =
    vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
  connectivityFilter->SetInputConnection(appendFilter->GetOutputPort());
  connectivityFilter->SetExtractionModeToAllRegions();
  connectivityFilter->ColorRegionsOn();
  connectivityFilter->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(connectivityFilter->GetOutputPort());
  mapper->SetScalarRange(connectivityFilter->GetOutput()->GetPointData()->GetArray("RegionId")->GetRange());
  mapper->Update();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ColorDisconnectedRegions)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ColorDisconnectedRegions MACOSX_BUNDLE ColorDisconnectedRegions.cxx)
 
target_link_libraries(ColorDisconnectedRegions ${VTK_LIBRARIES})
```

**Download and Build ColorDisconnectedRegions**

Click [here to download ColorDisconnectedRegions](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ColorDisconnectedRegions.tar) and its *CMakeLists.txt* file.
Once the *tarball ColorDisconnectedRegions.tar* has been downloaded and extracted,
```
cd ColorDisconnectedRegions/build 
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
./ColorDisconnectedRegions
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

