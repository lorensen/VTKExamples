[VTKExamples](Home)/[Cxx](Cxx)/PolyData/TransformFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/PolyData/TestTransformFilter.png" width="256" />

### Description
This example stretches an arrow.

**TransformFilter.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkArrowSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
 
int main(int, char *[])
{
  // Create an arrow.
  vtkSmartPointer<vtkArrowSource> arrowSource = 
    vtkSmartPointer<vtkArrowSource>::New();
 
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->Scale(5,1,1);
  
  vtkSmartPointer<vtkTransformFilter> transformFilter =
    vtkSmartPointer<vtkTransformFilter>::New();
  transformFilter->SetInputConnection(arrowSource->GetOutputPort());
  transformFilter->SetTransform(transform);
  
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(transformFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(actor);
  renderer->SetBackground(.2, .3, .4);
 
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TransformFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TransformFilter MACOSX_BUNDLE TransformFilter.cxx)
 
target_link_libraries(TransformFilter ${VTK_LIBRARIES})
```

**Download and Build TransformFilter**

Click [here to download TransformFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TransformFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball TransformFilter.tar* has been downloaded and extracted,
```
cd TransformFilter/build 
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
./TransformFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

