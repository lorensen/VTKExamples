[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/Reflection

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestReflection.png?raw=true" width="256" />

### Description
'''Note:''' This example uses {{class|vtkReflectionFilter}}, which outputs a {{class|vtkDataObject}}. For an example that returns a {{class|vtkPolyData}}, see ''[]([../../Filtering/TransformPolyData|TransformPolyData])''.

**Reflection.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkReflectionFilter.h>
#include <vtkPolyData.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkConeSource> coneSource = 
    vtkSmartPointer<vtkConeSource>::New();
  coneSource->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> coneMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection(coneSource->GetOutputPort());
  vtkSmartPointer<vtkActor> coneActor = 
      vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMapper);
  coneActor->GetProperty()->SetColor(0.0, 1.0, 0.0); //(R,G,B)
  
  // Reflection
  vtkSmartPointer<vtkReflectionFilter> reflectionFilter = 
    vtkSmartPointer<vtkReflectionFilter>::New();
  reflectionFilter->SetInputConnection(coneSource->GetOutputPort());
  reflectionFilter->CopyInputOff();
  reflectionFilter->Update();
  
  vtkSmartPointer<vtkDataSetMapper> reflectionMapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
  reflectionMapper->SetInputConnection(reflectionFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> reflectionActor = 
    vtkSmartPointer<vtkActor>::New();
  reflectionActor->SetMapper(reflectionMapper);
  reflectionActor->GetProperty()->SetColor(1.0, 0.0, 0.0); //(R,G,B)
  
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  // Add the actor to the scene
  renderer->AddActor(coneActor);
  renderer->AddActor(reflectionActor);
  renderer->SetBackground(1,1,1); // Background color white
 
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Reflection)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Reflection MACOSX_BUNDLE Reflection.cxx)
 
target_link_libraries(Reflection ${VTK_LIBRARIES})
```

**Download and Build Reflection**

Click [here to download Reflection](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Reflection.tar) and its *CMakeLists.txt* file.
Once the *tarball Reflection.tar* has been downloaded and extracted,
```
cd Reflection/build 
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
./Reflection
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

