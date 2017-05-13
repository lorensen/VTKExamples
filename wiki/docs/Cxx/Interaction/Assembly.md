[VTKExamples](/index/)/[Cxx](/Cxx)/Interaction/Assembly

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Interaction/TestAssembly.png?raw=true" width="256" />

**Assembly.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkCubeSource.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkAssembly.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>
#include <vtkPropAssembly.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);

  // Create a cube
  vtkSmartPointer<vtkCubeSource> cubeSource =
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->SetCenter(5.0, 0.0, 0.0);
  cubeSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
  vtkSmartPointer<vtkActor> cubeActor =
    vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);

  // Combine the sphere and cube into an assembly
  vtkSmartPointer<vtkAssembly> assembly =
    vtkSmartPointer<vtkAssembly>::New();
  assembly->AddPart(sphereActor);
  assembly->AddPart(cubeActor);

  // Apply a transform to the whole assembly
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->PostMultiply(); //this is the key line
  transform->Translate(5.0, 0, 0);

  assembly->SetUserTransform(transform);

  // Extract each actor from the assembly and change its opacity
  vtkSmartPointer<vtkPropCollection> collection =
    vtkSmartPointer<vtkPropCollection>::New();

  assembly->GetActors(collection);
  collection->InitTraversal();
  for(vtkIdType i = 0; i < collection->GetNumberOfItems(); i++)
  {
    vtkActor::SafeDownCast(collection->GetNextProp())->GetProperty()->SetOpacity(0.5);
  }

  // Visualization
  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(assembly);
  renderer->SetBackground(1,1,1); // Background color white

  renderer->ResetCamera();
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Assembly)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Assembly MACOSX_BUNDLE Assembly.cxx)
 
target_link_libraries(Assembly ${VTK_LIBRARIES})
```

**Download and Build Assembly**

Click [here to download Assembly](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Assembly.tar) and its *CMakeLists.txt* file.
Once the *tarball Assembly.tar* has been downloaded and extracted,
```
cd Assembly/build 
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
./Assembly
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

