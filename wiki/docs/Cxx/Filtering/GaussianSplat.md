[VTKExamples](/home/)/[Cxx](/Cxx)/Filtering/GaussianSplat

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestGaussianSplat.png?raw=true" width="256" />

**GaussianSplat.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkContourFilter.h>
#include <vtkGaussianSplatter.h>
#include <vtkSphereSource.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create points on a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(sphereSource->GetOutput()->GetPoints());

  vtkSmartPointer<vtkGaussianSplatter> splatter = 
    vtkSmartPointer<vtkGaussianSplatter>::New();
#if VTK_MAJOR_VERSION <= 5
  splatter->SetInput(polydata);
#else
  splatter->SetInputData(polydata);
#endif
  splatter->SetSampleDimensions(50,50,50);
  splatter->SetRadius(0.5);
  splatter->ScalarWarpingOff();

  vtkSmartPointer<vtkContourFilter> surface = 
    vtkSmartPointer<vtkContourFilter>::New();
  surface->SetInputConnection(splatter->GetOutputPort());
  surface->SetValue(0,0.01);

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(surface->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  // Visualize
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
 
PROJECT(GaussianSplat)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GaussianSplat MACOSX_BUNDLE GaussianSplat.cxx)
 
target_link_libraries(GaussianSplat ${VTK_LIBRARIES})
```

**Download and Build GaussianSplat**

Click [here to download GaussianSplat](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GaussianSplat.tar) and its *CMakeLists.txt* file.
Once the *tarball GaussianSplat.tar* has been downloaded and extracted,
```
cd GaussianSplat/build 
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
./GaussianSplat
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

