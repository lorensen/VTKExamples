[VTKExamples](/index/)/[Cxx](/Cxx)/GeometricObjects/PlatonicSolid

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestPlatonicSolid.png?raw=true" width="256" />

**PlatonicSolid.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkPlatonicSolidSource.h>
#include <vtkLookupTable.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
 
int main(int, char *[])
{
  vtkSmartPointer<vtkPlatonicSolidSource> platonicSolidSource = 
    vtkSmartPointer<vtkPlatonicSolidSource>::New();
  platonicSolidSource->SetSolidTypeToOctahedron();

  // Each face has a different cell scalar
  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  lut->SetNumberOfTableValues(8);
  lut->SetTableRange(0.0, 7.0);
  lut->Build();
  lut->SetTableValue(0, 0, 0, 0);
  lut->SetTableValue(1, 0, 0, 1);
  lut->SetTableValue(2, 0, 1, 0);
  lut->SetTableValue(3, 0, 1, 1);
  lut->SetTableValue(4, 1, 0, 0);
  lut->SetTableValue(5, 1, 0, 1);
  lut->SetTableValue(6, 1, 1, 0);
  lut->SetTableValue(7, 1, 1, 1);

  //Create a mapper and actor.
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(platonicSolidSource->GetOutputPort());
  mapper->SetLookupTable(lut);
  mapper->SetScalarRange(0, 7);

  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.1, .2, .3);

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PlatonicSolid)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PlatonicSolid MACOSX_BUNDLE PlatonicSolid.cxx)
 
target_link_libraries(PlatonicSolid ${VTK_LIBRARIES})
```

**Download and Build PlatonicSolid**

Click [here to download PlatonicSolid](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PlatonicSolid.tar) and its *CMakeLists.txt* file.
Once the *tarball PlatonicSolid.tar* has been downloaded and extracted,
```
cd PlatonicSolid/build 
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
./PlatonicSolid
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

