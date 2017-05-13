[VTKExamples](/home/)/[Cxx](/Cxx)/Filtering/ConnectivityFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestConnectivityFilter.png?raw=true" width="256" />

**ConnectivityFilter.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSphereSource.h>
#include <vtkConnectivityFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendFilter.h>
#include <vtkDelaunay3D.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource1 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->Update();

  vtkSmartPointer<vtkDelaunay3D> delaunay1 =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay1->SetInputConnection(sphereSource1->GetOutputPort());
  delaunay1->Update();
  
  vtkSmartPointer<vtkSphereSource> sphereSource2 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetCenter(5,0,0);
  sphereSource2->Update();

  vtkSmartPointer<vtkDelaunay3D> delaunay2 =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay2->SetInputConnection(sphereSource2->GetOutputPort());
  delaunay2->Update();
  
  vtkSmartPointer<vtkAppendFilter> appendFilter =
    vtkSmartPointer<vtkAppendFilter>::New();
  appendFilter->AddInputConnection(delaunay1->GetOutputPort());
  appendFilter->AddInputConnection(delaunay2->GetOutputPort());
  appendFilter->Update();

  vtkSmartPointer<vtkConnectivityFilter> connectivityFilter =
    vtkSmartPointer<vtkConnectivityFilter>::New();
  connectivityFilter->SetInputConnection(appendFilter->GetOutputPort());
  connectivityFilter->SetExtractionModeToAllRegions();
  connectivityFilter->ColorRegionsOn();
  connectivityFilter->Update();

  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(connectivityFilter->GetOutputPort());
  mapper->Update();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> renwin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renwin->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renwin);
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ConnectivityFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ConnectivityFilter MACOSX_BUNDLE ConnectivityFilter.cxx)
 
target_link_libraries(ConnectivityFilter ${VTK_LIBRARIES})
```

**Download and Build ConnectivityFilter**

Click [here to download ConnectivityFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ConnectivityFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball ConnectivityFilter.tar* has been downloaded and extracted,
```
cd ConnectivityFilter/build 
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
./ConnectivityFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

