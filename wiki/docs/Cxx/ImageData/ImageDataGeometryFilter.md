[VTKExamples](/home/)/[Cxx](/Cxx)/ImageData/ImageDataGeometryFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/ImageData/TestImageDataGeometryFilter.png?raw=true" width="256" />

### Description
Convert a vtkImageData to a vtkPolyData.

**ImageDataGeometryFilter.cxx**
```c++
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageDataGeometryFilter.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> source1 = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source1->SetScalarTypeToUnsignedChar();
  source1->SetNumberOfScalarComponents(3);
  source1->SetExtent(0, 100, 0, 100, 0, 0);
  source1->SetDrawColor(0,0,0,1);
  source1->FillBox(0, 100, 0, 100);
  source1->SetDrawColor(255,0,0,1);
  source1->FillBox(10, 20, 10, 20);
  source1->FillBox(40, 50, 20, 30);
  source1->Update();
  
  // Convert the image to a polydata
  vtkSmartPointer<vtkImageDataGeometryFilter> imageDataGeometryFilter = 
    vtkSmartPointer<vtkImageDataGeometryFilter>::New();
  imageDataGeometryFilter->SetInputConnection(source1->GetOutputPort());
  imageDataGeometryFilter->Update();
  
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(imageDataGeometryFilter->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
      vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  // Visualization
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white
 
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
 
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageDataGeometryFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageDataGeometryFilter MACOSX_BUNDLE ImageDataGeometryFilter.cxx)
 
target_link_libraries(ImageDataGeometryFilter ${VTK_LIBRARIES})
```

**Download and Build ImageDataGeometryFilter**

Click [here to download ImageDataGeometryFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageDataGeometryFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageDataGeometryFilter.tar* has been downloaded and extracted,
```
cd ImageDataGeometryFilter/build 
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
./ImageDataGeometryFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

