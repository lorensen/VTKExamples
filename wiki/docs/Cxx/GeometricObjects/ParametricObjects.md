[VTKExamples](/home/)/[Cxx](/Cxx)/GeometricObjects/ParametricObjects

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestParametricObjects.png?raw=true" width="256" />

### Description
See [Parametric Equations for Surfaces](http://www.vtk.org/VTK/img/ParametricSurfaces.pdf) by Andrew Maclean for an excellent description of these beautiful parametric surfaces.

You can edit the following code by selecting any one of the functions and the corresponding object will be displayed.

**ParametricObjects.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkParametricFunctionSource.h>

// Select one of the following:
#include <vtkParametricTorus.h>
//#include <vtkParametricBoy.h>
//#include <vtkParametricConicSpiral.h>
//#include <vtkParametricCrossCap.h>
//#include <vtkParametricDini.h>
//#include <vtkParametricEllipsoid.h>
//#include <vtkParametricEnneper.h>
//#include <vtkParametricFigure8Klein.h>
//#include <vtkParametricKlein.h>
//#include <vtkParametricMobius.h>
//#include <vtkParametricRandomHills.h>
//#include <vtkParametricRoman.h>
//#include <vtkParametricSpline.h>
//#include <vtkParametricSuperEllipsoid.h>
//#include <vtkParametricSuperToroid.h>
//#include <vtkParametricTorus.h>

int main(int, char *[])
{
  // Select one of the following (matching the selection above)
  vtkSmartPointer<vtkParametricTorus> parametricObject = vtkSmartPointer<vtkParametricTorus>::New();
  //vtkSmartPointer<vtkParametricBoy> parametricObject = vtkSmartPointer<vtkParametricBoy>::New();
  //vtkSmartPointer<vtkParametricConicSpiral> parametricObject = vtkSmartPointer<vtkParametricConicSpiral>::New();
  //vtkSmartPointer<vtkParametricCrossCap> parametricObject = vtkSmartPointer<vtkParametricCrossCap>::New();
  //vtkSmartPointer<vtkParametricDini> parametricObject = vtkSmartPointer<vtkParametricDini>::New();
  //vtkSmartPointer<vtkParametricEllipsoid> parametricObject = vtkSmartPointer<vtkParametricEllipsoid>::New();
  //vtkSmartPointer<vtkParametricEnneper> parametricObject = vtkSmartPointer<vtkParametricEnneper>::New();
  //vtkSmartPointer<vtkParametricFigure8Klein> parametricObject = vtkSmartPointer<vtkParametricFigure8Klein>::New();
  //vtkSmartPointer<vtkParametricKlein> parametricObject = vtkSmartPointer<vtkParametricKlein>::New();
  //vtkSmartPointer<vtkParametricMobius> parametricObject = vtkSmartPointer<vtkParametricMobius>::New();
  //vtkSmartPointer<vtkParametricRandomHills> parametricObject = vtkSmartPointer<vtkParametricRandomHills>::New();
  //vtkSmartPointer<vtkParametricRoman> parametricObject = vtkSmartPointer<vtkParametricRoman>::New();
  //vtkSmartPointer<vtkParametricSpline> parametricObject = vtkSmartPointer<vtkParametricSpline>::New();
  //vtkSmartPointer<vtkParametricSuperEllipsoid> parametricObject = vtkSmartPointer<vtkParametricSuperEllipsoid>::New();
  //vtkSmartPointer<vtkParametricSuperToroid> parametricObject = vtkSmartPointer<vtkParametricSuperToroid>::New();
  //vtkSmartPointer<vtkParametricTorus> parametricObject = vtkSmartPointer<vtkParametricTorus>::New();
  
  vtkSmartPointer<vtkParametricFunctionSource> parametricFunctionSource =
    vtkSmartPointer<vtkParametricFunctionSource>::New();
  parametricFunctionSource->SetParametricFunction(parametricObject);
  parametricFunctionSource->Update();
  
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(parametricFunctionSource->GetOutputPort());
  
  // Create an actor for the contours
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white
  
  renderWindow->Render();
  interactor->Start();
    
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ParametricObjects)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ParametricObjects MACOSX_BUNDLE ParametricObjects.cxx)
 
target_link_libraries(ParametricObjects ${VTK_LIBRARIES})
```

**Download and Build ParametricObjects**

Click [here to download ParametricObjects](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ParametricObjects.tar) and its *CMakeLists.txt* file.
Once the *tarball ParametricObjects.tar* has been downloaded and extracted,
```
cd ParametricObjects/build 
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
./ParametricObjects
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

