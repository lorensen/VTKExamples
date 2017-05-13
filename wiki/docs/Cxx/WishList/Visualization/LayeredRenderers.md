[VTKExamples](/home/)/[Cxx](/Cxx)/WishList/Visualization/LayeredRenderers

**LayeredRenderers.cxx**
```c++
#include <vtkSphereSource.h>
#include <vtkTransform.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVectorText.h>

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

  // Create text
  vtkSmartPointer<vtkVectorText> textSource =
    vtkSmartPointer<vtkVectorText>::New();
  textSource->SetText("TEXT");
  textSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> textMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  textMapper->SetInputConnection(textSource->GetOutputPort());

  vtkSmartPointer<vtkActor> textActor =
    vtkSmartPointer<vtkActor>::New();
  textActor->SetMapper(textMapper);

  vtkSmartPointer<vtkRenderer> renderer1 =
    vtkSmartPointer<vtkRenderer>::New();
  renderer1->SetLayer(0);

  vtkSmartPointer<vtkRenderer> renderer2 =
    vtkSmartPointer<vtkRenderer>::New();
  renderer2->SetActiveCamera(renderer1->GetActiveCamera());
  renderer2->SetLayer(1);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer1);
  renderWindow->AddRenderer(renderer2);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer1->AddActor(sphereActor);
  renderer2->AddActor(textActor);

  renderWindow->SetNumberOfLayers(2);
  renderer1->ResetCamera();
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(LayeredRenderers)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(LayeredRenderers MACOSX_BUNDLE LayeredRenderers.cxx)
 
target_link_libraries(LayeredRenderers ${VTK_LIBRARIES})
```

**Download and Build LayeredRenderers**

Click [here to download LayeredRenderers](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/LayeredRenderers.tar) and its *CMakeLists.txt* file.
Once the *tarball LayeredRenderers.tar* has been downloaded and extracted,
```
cd LayeredRenderers/build 
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
./LayeredRenderers
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

