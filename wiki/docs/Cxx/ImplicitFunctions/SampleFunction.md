[VTKExamples](/index/)/[Cxx](/Cxx)/ImplicitFunctions/SampleFunction

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/ImplicitFunctions/TestSampleFunction.png?raw=true" width="256" />

**SampleFunction.cxx**
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

#include <vtkSphere.h>

int main (int, char *[])
{
  vtkSmartPointer<vtkSphere> sphere = 
    vtkSmartPointer<vtkSphere>::New();
  
  // Sample the function
  vtkSmartPointer<vtkSampleFunction> sample = 
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(50,50,50);
  sample->SetImplicitFunction(sphere);
  double value = 2.0;
  double xmin = -value, xmax = value, ymin = -value, ymax = value, zmin = -value, zmax = value;
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
  contourMapper->SetScalarRange(0.0, 1.2);
  
  // Create an actor for the contours
  vtkSmartPointer<vtkActor> contourActor = 
    vtkSmartPointer<vtkActor>::New();
  contourActor->SetMapper(contourMapper);
  
  // -- create a box around the function to indicate the sampling volume --
  
  // Create outline
  vtkSmartPointer<vtkOutlineFilter> outline = 
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(sample->GetOutputPort());
  
  // Map it to graphics primitives
  vtkSmartPointer<vtkPolyDataMapper> outlineMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());
  
  // Create an actor for it
  vtkSmartPointer<vtkActor> outlineActor = 
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(0,0,0);
  
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
  renderer->AddActor(outlineActor);
  renderer->SetBackground(1,1,1); // Background color white
  
  renderWindow->Render();
  interactor->Start();
    
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SampleFunction)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SampleFunction MACOSX_BUNDLE SampleFunction.cxx)
 
target_link_libraries(SampleFunction ${VTK_LIBRARIES})
```

**Download and Build SampleFunction**

Click [here to download SampleFunction](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SampleFunction.tar) and its *CMakeLists.txt* file.
Once the *tarball SampleFunction.tar* has been downloaded and extracted,
```
cd SampleFunction/build 
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
./SampleFunction
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

