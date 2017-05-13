[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/IsosurfaceSampling

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestIsosurfaceSampling.png?raw=true" width="256" />

### Description
This example illustrates how to create an isosurface and create point data on that isosurface that is sampled from another dataset. This example creates an isosurface of a sphere and then uses the vtkProbeFilter to compute point data from a sampled cylinder. '''Note''', that all point data is sampled, even the normals. This example restores the original isosurface normals after the probe. The example has one optional command line argument that controls the sample resolution of the sphere and cylinder. The default is 50.

**IsosurfaceSampling.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkSampleFunction.h>
#include <vtkSphere.h>
#include <vtkCylinder.h>
#include <vtkMarchingCubes.h>
#include <vtkProbeFilter.h>

#include <vtkImageData.h>
#include <vtkPointData.h>

#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkUnsignedCharArray.h>

int main(int argc, char *argv[])
{
  int resolution = 50;
  if (argc > 1)
  {
    resolution = atoi(argv[1]);
  }

  // Create a sampled sphere
  vtkSmartPointer<vtkSphere> implicitSphere =
    vtkSmartPointer<vtkSphere>::New();
  double radius = 1.0;
  implicitSphere->SetRadius(radius);

  vtkSmartPointer<vtkSampleFunction> sampledSphere =
    vtkSmartPointer<vtkSampleFunction>::New();
  sampledSphere->SetSampleDimensions(resolution, resolution, resolution);
  double xMin = -radius * 2.0;
  double xMax =  radius * 2.0;
  sampledSphere->SetModelBounds(xMin, xMax,
                                xMin, xMax,
                                xMin, xMax);
  sampledSphere->SetImplicitFunction(implicitSphere);

  vtkSmartPointer<vtkMarchingCubes> isoSphere =
    vtkSmartPointer<vtkMarchingCubes>:: New();
  isoSphere->SetValue(0,1.0);
  isoSphere->SetInputConnection(sampledSphere->GetOutputPort());

  // Create a sampled cylinder
  vtkSmartPointer<vtkCylinder> implicitCylinder =
    vtkSmartPointer<vtkCylinder>::New();
  implicitCylinder->SetRadius(radius/2.0);
  vtkSmartPointer<vtkSampleFunction> sampledCylinder =
    vtkSmartPointer<vtkSampleFunction>::New();
  sampledCylinder->SetSampleDimensions(resolution, resolution, resolution);
  sampledCylinder->SetModelBounds(xMin, xMax,
                                  xMin, xMax,
                                  xMin, xMax);
  sampledCylinder->SetImplicitFunction(implicitCylinder);

  // Probe cylinder with the sphere isosurface
  vtkSmartPointer<vtkProbeFilter> probeCylinder =
    vtkSmartPointer<vtkProbeFilter>::New();
  probeCylinder->SetInputConnection(0, isoSphere->GetOutputPort());
  probeCylinder->SetInputConnection(1, sampledCylinder->GetOutputPort());
  probeCylinder->Update();

  // Restore the original normals
  probeCylinder->GetOutput()->GetPointData()->SetNormals(
    isoSphere->GetOutput()->GetPointData()->GetNormals());

  std::cout << "Scalar range: "
            << probeCylinder->GetOutput()->GetScalarRange()[0] << ", "
            << probeCylinder->GetOutput()->GetScalarRange()[1] << std::endl;

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapSphere =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapSphere->SetInputConnection(probeCylinder->GetOutputPort());
  mapSphere->SetScalarRange(probeCylinder->GetOutput()->GetScalarRange());

  vtkSmartPointer<vtkActor> sphere =
    vtkSmartPointer<vtkActor>::New();
  sphere->SetMapper(mapSphere);

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(sphere);
  renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(IsosurfaceSampling)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(IsosurfaceSampling MACOSX_BUNDLE IsosurfaceSampling.cxx)
 
target_link_libraries(IsosurfaceSampling ${VTK_LIBRARIES})
```

**Download and Build IsosurfaceSampling**

Click [here to download IsosurfaceSampling](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/IsosurfaceSampling.tar) and its *CMakeLists.txt* file.
Once the *tarball IsosurfaceSampling.tar* has been downloaded and extracted,
```
cd IsosurfaceSampling/build 
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
./IsosurfaceSampling
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

