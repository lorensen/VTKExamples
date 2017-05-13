[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/PolyDataConnectivityFilter_LargestRegion

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestPolyDataConnectivityFilter_LargestRegion.png?raw=true" width="256" />

### Description
This example keeps the largest connected region of a mesh. Note that this is based on the number of points, not the actual area of the region.

* Contributed by: Jinyoung Hwang

**PolyDataConnectivityFilter_LargestRegion.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>
 
int main(int, char *[])
{
  // Small sphere
  vtkSmartPointer<vtkSphereSource> sphereSource1 = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->Update();
  
  // Large sphere
  vtkSmartPointer<vtkSphereSource> sphereSource2 = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetRadius(10);
  sphereSource2->SetCenter(25,0,0);
  sphereSource2->SetThetaResolution(10);
  sphereSource2->SetPhiResolution(10);
  sphereSource2->Update();
  
  vtkSmartPointer<vtkAppendPolyData> appendFilter = 
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendFilter->AddInputConnection(sphereSource1->GetOutputPort());
  appendFilter->AddInputConnection(sphereSource2->GetOutputPort());
  appendFilter->Update();
  
  vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter = 
    vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
  connectivityFilter->SetInputConnection(appendFilter->GetOutputPort());
  connectivityFilter->SetExtractionModeToLargestRegion(); 
  connectivityFilter->Update();
  
  // Create a mapper and actor for original data
  vtkSmartPointer<vtkPolyDataMapper> originalMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(appendFilter->GetOutputPort());
  originalMapper->Update();
  
  vtkSmartPointer<vtkActor> originalActor = 
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  
  // Create a mapper and actor for extracted data
  vtkSmartPointer<vtkPolyDataMapper> extractedMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  extractedMapper->SetInputConnection(connectivityFilter->GetOutputPort());
  extractedMapper->Update();
  
  vtkSmartPointer<vtkActor> extractedActor = 
    vtkSmartPointer<vtkActor>::New();
  extractedActor->GetProperty()->SetColor(1,0,0);
  extractedActor->SetMapper(extractedMapper);
  
  // Visualization
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(originalActor);
  renderer->AddActor(extractedActor);
  
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
 
PROJECT(PolyDataConnectivityFilter_LargestRegion)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PolyDataConnectivityFilter_LargestRegion MACOSX_BUNDLE PolyDataConnectivityFilter_LargestRegion.cxx)
 
target_link_libraries(PolyDataConnectivityFilter_LargestRegion ${VTK_LIBRARIES})
```

**Download and Build PolyDataConnectivityFilter_LargestRegion**

Click [here to download PolyDataConnectivityFilter_LargestRegion](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PolyDataConnectivityFilter_LargestRegion.tar) and its *CMakeLists.txt* file.
Once the *tarball PolyDataConnectivityFilter_LargestRegion.tar* has been downloaded and extracted,
```
cd PolyDataConnectivityFilter_LargestRegion/build 
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
./PolyDataConnectivityFilter_LargestRegion
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

