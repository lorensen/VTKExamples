[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/IntersectionPolyDataFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestIntersectionPolyDataFilter.png?raw=true" width="256" />

### Description
NOTE: This example requires version 5.9.20111206 or higher. 

**IntersectionPolyDataFilter.cxx**
```c++
#include <vtkActor.h>
#include <vtkIntersectionPolyDataFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource1 = vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->SetCenter(0.0, 0.0, 0.0);
  sphereSource1->SetRadius(2.0f);
  sphereSource1->Update();
  vtkSmartPointer<vtkPolyDataMapper> sphere1Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  sphere1Mapper->SetInputConnection( sphereSource1->GetOutputPort() );
  sphere1Mapper->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> sphere1Actor = vtkSmartPointer<vtkActor>::New();
  sphere1Actor->SetMapper( sphere1Mapper );
  sphere1Actor->GetProperty()->SetOpacity(.3);
  sphere1Actor->GetProperty()->SetColor(1,0,0);

  vtkSmartPointer<vtkSphereSource> sphereSource2 = vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetCenter(1.0, 0.0, 0.0);
  sphereSource2->SetRadius(2.0f);
  vtkSmartPointer<vtkPolyDataMapper> sphere2Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  sphere2Mapper->SetInputConnection( sphereSource2->GetOutputPort() );
  sphere2Mapper->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> sphere2Actor = vtkSmartPointer<vtkActor>::New();
  sphere2Actor->SetMapper( sphere2Mapper );
  sphere2Actor->GetProperty()->SetOpacity(.3);
  sphere2Actor->GetProperty()->SetColor(0,1,0);

  vtkSmartPointer<vtkIntersectionPolyDataFilter> intersectionPolyDataFilter =
    vtkSmartPointer<vtkIntersectionPolyDataFilter>::New();
  intersectionPolyDataFilter->SetInputConnection( 0, sphereSource1->GetOutputPort() );
  intersectionPolyDataFilter->SetInputConnection( 1, sphereSource2->GetOutputPort() );
  intersectionPolyDataFilter->Update();

  vtkSmartPointer<vtkPolyDataMapper> intersectionMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  intersectionMapper->SetInputConnection( intersectionPolyDataFilter->GetOutputPort() );
  intersectionMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> intersectionActor = vtkSmartPointer<vtkActor>::New();
  intersectionActor->SetMapper( intersectionMapper );

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddViewProp(sphere1Actor);
  renderer->AddViewProp(sphere2Actor);
  renderer->AddViewProp(intersectionActor);

  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> renWinInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renWinInteractor->SetRenderWindow( renderWindow );

  renderWindow->Render();
  renWinInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(IntersectionPolyDataFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(IntersectionPolyDataFilter MACOSX_BUNDLE IntersectionPolyDataFilter.cxx)
 
target_link_libraries(IntersectionPolyDataFilter ${VTK_LIBRARIES})
```

**Download and Build IntersectionPolyDataFilter**

Click [here to download IntersectionPolyDataFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/IntersectionPolyDataFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball IntersectionPolyDataFilter.tar* has been downloaded and extracted,
```
cd IntersectionPolyDataFilter/build 
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
./IntersectionPolyDataFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

