[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/LinearExtrusion

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestLinearExtrusion.png?raw=true" width="256" />

### Description
This example creates some text, extrudes it to make it 3D.

**LinearExtrusion.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkVectorText.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkTriangleFilter.h>

#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create vector text
  vtkSmartPointer<vtkVectorText> vecText = 
    vtkSmartPointer<vtkVectorText>::New();
  vecText->SetText("Text!");
    
  // Apply linear extrusion 
  vtkSmartPointer<vtkLinearExtrusionFilter> extrude = 
    vtkSmartPointer<vtkLinearExtrusionFilter>::New();
  extrude->SetInputConnection( vecText->GetOutputPort());
  extrude->SetExtrusionTypeToNormalExtrusion();
  extrude->SetVector(0, 0, 1 );
  extrude->SetScaleFactor (0.5);
    
  vtkSmartPointer<vtkTriangleFilter> triangleFilter =
    vtkSmartPointer<vtkTriangleFilter>::New();
  triangleFilter->SetInputConnection(extrude->GetOutputPort());
    
  vtkSmartPointer<vtkDataSetMapper> mapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(triangleFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(0.8900, 0.8100, 0.3400);
    
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(.4, .5, .7);

  renderWindow->AddRenderer(renderer);

  renderer->AddActor(actor);
  
  renderer->ResetCamera();
    // Generate an interesting view
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.0);
  renderer->ResetCameraClippingRange();

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(LinearExtrusion)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(LinearExtrusion MACOSX_BUNDLE LinearExtrusion.cxx)
 
target_link_libraries(LinearExtrusion ${VTK_LIBRARIES})
```

**Download and Build LinearExtrusion**

Click [here to download LinearExtrusion](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/LinearExtrusion.tar) and its *CMakeLists.txt* file.
Once the *tarball LinearExtrusion.tar* has been downloaded and extracted,
```
cd LinearExtrusion/build 
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
./LinearExtrusion
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

