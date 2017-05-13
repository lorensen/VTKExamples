[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/PolyDataConnectivityFilter_SpecifiedRegion

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestPolyDataConnectivityFilter_SpecifiedRegion.png?raw=true" width="256" />

### Description
This example creates two spheres and combines them together into one polydata. The vtkPolyDataConnectivityFilter is used to find the two spheres as they are separate regions (disconnected). If region 0 is selected, the small sphere is extracted. If region 1 is selected, the large sphere is extracted.

**PolyDataConnectivityFilter_SpecifiedRegion.cxx**
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
  vtkSmartPointer<vtkSphereSource> sphereSource1 = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->Update();
  
  vtkSmartPointer<vtkSphereSource> sphereSource2 = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetRadius(10);
  sphereSource2->SetCenter(25,0,0);
  sphereSource2->Update();
  
  vtkSmartPointer<vtkAppendPolyData> appendFilter = 
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendFilter->AddInputConnection(sphereSource1->GetOutputPort());
  appendFilter->AddInputConnection(sphereSource2->GetOutputPort());
  appendFilter->Update();
  
  vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter = 
    vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
  connectivityFilter->SetInputConnection(appendFilter->GetOutputPort());
  connectivityFilter->SetExtractionModeToSpecifiedRegions(); 
  connectivityFilter->AddSpecifiedRegion(1); //select the region to extract here
  connectivityFilter->Update();
  
  // Create a mapper and actor for original data
  vtkSmartPointer<vtkPolyDataMapper> originalMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(appendFilter->GetOutputPort());
  originalMapper->Update();
  
  vtkSmartPointer<vtkActor> originalActor = 
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  
  // create a mapper and actor for extracted data
  vtkSmartPointer<vtkPolyDataMapper> extractedMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  extractedMapper->SetInputConnection(connectivityFilter->GetOutputPort());
  extractedMapper->Update();
  
  vtkSmartPointer<vtkActor> extractedActor = 
    vtkSmartPointer<vtkActor>::New();
  extractedActor->GetProperty()->SetColor(1,0,0);
  extractedActor->SetMapper(extractedMapper);
  
  // create a renderer
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(originalActor);
  renderer->AddActor(extractedActor);
  
  // create a render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  
  // create an interactor
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
 
PROJECT(PolyDataConnectivityFilter_SpecifiedRegion)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PolyDataConnectivityFilter_SpecifiedRegion MACOSX_BUNDLE PolyDataConnectivityFilter_SpecifiedRegion.cxx)
 
target_link_libraries(PolyDataConnectivityFilter_SpecifiedRegion ${VTK_LIBRARIES})
```

**Download and Build PolyDataConnectivityFilter_SpecifiedRegion**

Click [here to download PolyDataConnectivityFilter_SpecifiedRegion](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PolyDataConnectivityFilter_SpecifiedRegion.tar) and its *CMakeLists.txt* file.
Once the *tarball PolyDataConnectivityFilter_SpecifiedRegion.tar* has been downloaded and extracted,
```
cd PolyDataConnectivityFilter_SpecifiedRegion/build 
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
./PolyDataConnectivityFilter_SpecifiedRegion
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

