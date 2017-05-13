[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/DownsamplePointCloud

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestDownsamplePointCloud.png?raw=true" width="256" />

### Description
This example downsamples a point cloud by specifying the minimum distance two points can be from each other. The filter will delete points so that this criterion is met.

**DownsamplePointCloud.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(1000);
  pointSource->SetRadius(1.0);
  pointSource->Update();

  vtkSmartPointer<vtkCleanPolyData> cleanPolyData =
    vtkSmartPointer<vtkCleanPolyData>::New();
  cleanPolyData->SetInputConnection(pointSource->GetOutputPort());
  cleanPolyData->SetTolerance(0.1);
  cleanPolyData->Update();

  vtkSmartPointer<vtkPolyDataMapper> inputMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  inputMapper->SetInputConnection(pointSource->GetOutputPort());
  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->SetMapper(inputMapper);

  vtkSmartPointer<vtkPolyDataMapper> cleanedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cleanedMapper->SetInputConnection(cleanPolyData->GetOutputPort());
  vtkSmartPointer<vtkActor> cleanedActor =
    vtkSmartPointer<vtkActor>::New();
  cleanedActor->SetMapper(cleanedMapper);
  
   // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  // And one interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  leftRenderer->AddActor(inputActor);
  rightRenderer->AddActor(cleanedActor);

  leftRenderer->ResetCamera();
  rightRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DownsamplePointCloud)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DownsamplePointCloud MACOSX_BUNDLE DownsamplePointCloud.cxx)
 
target_link_libraries(DownsamplePointCloud ${VTK_LIBRARIES})
```

**Download and Build DownsamplePointCloud**

Click [here to download DownsamplePointCloud](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DownsamplePointCloud.tar) and its *CMakeLists.txt* file.
Once the *tarball DownsamplePointCloud.tar* has been downloaded and extracted,
```
cd DownsamplePointCloud/build 
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
./DownsamplePointCloud
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

