[VTKExamples](Home)/[Cxx](Cxx)/PolyData/WarpScalar

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/PolyData/TestWarpScalar.png" width="256" />

**WarpScalar.cxx**
```c++
#include <vtkActor.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkWarpScalar.h>
#include <vtkMath.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  // Create Scalars
  vtkSmartPointer<vtkDoubleArray> scalars =
    vtkSmartPointer<vtkDoubleArray>::New();
  int numberOfPoints = sphereSource->GetOutput()->GetNumberOfPoints();
  scalars->SetNumberOfTuples(numberOfPoints);

  vtkMath::RandomSeed(8775070); // for reproducibility
  for(vtkIdType i = 0; i < numberOfPoints; ++i)
  {
    scalars->SetTuple1(i, vtkMath::Random(0.0, 1.0 / 7.0));
  }

  sphereSource->GetOutput()->GetPointData()->SetScalars(scalars);

  vtkSmartPointer<vtkWarpScalar> warpScalar =
    vtkSmartPointer<vtkWarpScalar>::New();
  warpScalar->SetInputConnection(sphereSource->GetOutputPort());
  warpScalar->SetScaleFactor(1); // use the scalars themselves

  // Required for SetNormal to have an effect
  warpScalar->UseNormalOn();
  warpScalar->SetNormal(0, 0, 1);

  warpScalar->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(warpScalar->GetOutputPort());

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
 
PROJECT(WarpScalar)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(WarpScalar MACOSX_BUNDLE WarpScalar.cxx)
 
target_link_libraries(WarpScalar ${VTK_LIBRARIES})
```

**Download and Build WarpScalar**

Click [here to download WarpScalar](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/WarpScalar.tar) and its *CMakeLists.txt* file.
Once the *tarball WarpScalar.tar* has been downloaded and extracted,
```
cd WarpScalar/build 
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
./WarpScalar
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

