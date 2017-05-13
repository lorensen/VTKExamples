[VTKExamples](/home/)/[Cxx](/Cxx)/Utilities/BrownianPoints

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Utilities/TestBrownianPoints.png?raw=true" width="256" />

**BrownianPoints.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkArrowSource.h>
#include <vtkBrownianPoints.h>
#include <vtkCamera.h>
#include <vtkGlyph3D.h>
#include <vtkMath.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  
  // Generate random vectors
  vtkMath::RandomSeed(5070); // for testing
  vtkSmartPointer<vtkBrownianPoints> brownianPoints =
    vtkSmartPointer<vtkBrownianPoints>::New();
  brownianPoints->SetInputConnection(sphereSource->GetOutputPort());
  
  vtkSmartPointer<vtkArrowSource> arrowSource =
    vtkSmartPointer<vtkArrowSource>::New();
  
  vtkSmartPointer<vtkGlyph3D> glyph3D =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph3D->SetSourceConnection(arrowSource->GetOutputPort());
  glyph3D->SetInputConnection(brownianPoints->GetOutputPort());
  glyph3D->SetScaleFactor(.3);
  
  // Create a mapper and actor for sphere
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->GetProperty()->SetInterpolationToFlat();
  actor->SetMapper(mapper);

  // Create a mapper and actor for glyphs
  vtkSmartPointer<vtkPolyDataMapper> glyphMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyphMapper->SetInputConnection(glyph3D->GetOutputPort());

  vtkSmartPointer<vtkActor> glyphActor =
    vtkSmartPointer<vtkActor>::New();
  glyphActor->GetProperty()->SetColor(0.89,0.81,0.34); // banana
  glyphActor->SetMapper(glyphMapper);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actor to the scene
  renderer->AddActor(actor);
  renderer->AddActor(glyphActor);

  // Create a nice view
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.4);
  renderer->ResetCameraClippingRange();

  renderer->SetBackground(.3, .4, .5);
  
  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BrownianPoints)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BrownianPoints MACOSX_BUNDLE BrownianPoints.cxx)
 
target_link_libraries(BrownianPoints ${VTK_LIBRARIES})
```

**Download and Build BrownianPoints**

Click [here to download BrownianPoints](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BrownianPoints.tar) and its *CMakeLists.txt* file.
Once the *tarball BrownianPoints.tar* has been downloaded and extracted,
```
cd BrownianPoints/build 
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
./BrownianPoints
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

