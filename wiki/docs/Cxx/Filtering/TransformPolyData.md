[VTKExamples](/index/)/[Cxx](/Cxx)/Filtering/TransformPolyData

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestTransformPolyData.png?raw=true" width="256" />

### Description
This example demonstrates how to apply a transform to a data set. It uses {{class|vtkTransformPolyDataFilter}}, but it can be replaced with {{class|vtkTransformFilter}} for different types of data sets, including {{class|vtkUnstructuredGrid}} and {{class|vtkStructuredGrid}}. ({{class|vtkTransformFilter}} will work with {{class|vtkPolyData}}, too).

**TransformPolyData.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create the polydata geometry

  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  // Set up the actor to display the untransformed polydata
 
  vtkSmartPointer<vtkPolyDataMapper> originalMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetColor(1,0,0);

  // Set up the transform filter

  vtkSmartPointer<vtkTransform> translation =
    vtkSmartPointer<vtkTransform>::New();
  translation->Translate(1.0, 2.0, 3.0);

  vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformFilter->SetInputConnection(sphereSource->GetOutputPort());
  transformFilter->SetTransform(translation);
  transformFilter->Update();

  // Set up the actor to display the transformed polydata

  vtkSmartPointer<vtkPolyDataMapper> transformedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  transformedMapper->SetInputConnection(transformFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> transformedActor =
    vtkSmartPointer<vtkActor>::New();
  transformedActor->SetMapper(transformedMapper);
  transformedActor->GetProperty()->SetColor(0,1,0);

  // Set up the rest of the visualization pipeline

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(originalActor);
  renderer->AddActor(transformedActor);
  renderer->SetBackground(.3, .6, .3); // Set renderer's background color to green

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TransformPolyData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TransformPolyData MACOSX_BUNDLE TransformPolyData.cxx)
 
target_link_libraries(TransformPolyData ${VTK_LIBRARIES})
```

**Download and Build TransformPolyData**

Click [here to download TransformPolyData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TransformPolyData.tar) and its *CMakeLists.txt* file.
Once the *tarball TransformPolyData.tar* has been downloaded and extracted,
```
cd TransformPolyData/build 
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
./TransformPolyData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

