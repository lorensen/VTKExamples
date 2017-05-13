[VTKExamples](/index/)/[Cxx](/Cxx)/Filtering/ImplicitBoolean

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestImplicitBoolean.png?raw=true" width="256" />

**ImplicitBoolean.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkImplicitBoolean.h>
 
#include <vtkSphere.h>
 
int main (int, char *[])
{
  vtkSmartPointer<vtkSphere> sphere1 = 
    vtkSmartPointer<vtkSphere>::New();
  sphere1->SetCenter(.9,0,0);
  vtkSmartPointer<vtkSphere> sphere2 = 
    vtkSmartPointer<vtkSphere>::New();
  sphere2->SetCenter(-.9,0,0);
 
  vtkSmartPointer<vtkImplicitBoolean> implicitBoolean =
    vtkSmartPointer<vtkImplicitBoolean>::New();
  implicitBoolean->AddFunction(sphere1);
  implicitBoolean->AddFunction(sphere2);
  implicitBoolean->SetOperationTypeToUnion();
  //implicitBoolean->SetOperationTypeToIntersection();
  
  // Sample the function
  vtkSmartPointer<vtkSampleFunction> sample = 
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(50,50,50);
  sample->SetImplicitFunction(implicitBoolean);
  double value = 3.0;
  double xmin = -value, xmax = value,
    ymin = -value, ymax = value,
    zmin = -value, zmax = value;
  sample->SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax);
 
  // Create the 0 isosurface
  vtkSmartPointer<vtkContourFilter> contours = 
    vtkSmartPointer<vtkContourFilter>::New();
  contours->SetInputConnection(sample->GetOutputPort());
  contours->GenerateValues(1, 1, 1);
 
  // Map the contours to graphical primitives
  vtkSmartPointer<vtkPolyDataMapper> contourMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contours->GetOutputPort());
  contourMapper->ScalarVisibilityOff();
 
  // Create an actor for the contours
  vtkSmartPointer<vtkActor> contourActor = 
    vtkSmartPointer<vtkActor>::New();
  contourActor->SetMapper(contourMapper);
 
  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(contourActor);
  renderer->SetBackground(.2, .3, .4);
 
  renderWindow->Render();
  interactor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImplicitBoolean)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImplicitBoolean MACOSX_BUNDLE ImplicitBoolean.cxx)
 
target_link_libraries(ImplicitBoolean ${VTK_LIBRARIES})
```

**Download and Build ImplicitBoolean**

Click [here to download ImplicitBoolean](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImplicitBoolean.tar) and its *CMakeLists.txt* file.
Once the *tarball ImplicitBoolean.tar* has been downloaded and extracted,
```
cd ImplicitBoolean/build 
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
./ImplicitBoolean
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

