[VTKExamples](Home)/[Cxx](Cxx)/Visualization/ScalarBarActor

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestScalarBarActor.png" width="256" />

### Description
This example demonstrates how to make a color bar to that reflects the range 
of values associated with a data set.

**ScalarBarActor.cxx**
```c++
#include <vtkVersion.h>
#include <vtkActor.h>
#include <vtkFloatArray.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkScalarBarActor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

int main (int, char *[])
{
  // Create a sphere for some geometry
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetCenter(0,0,0);
  sphere->SetRadius(1);
  sphere->Update();

  // Create scalar data to associate with the vertices of the sphere
  int numPts = sphere->GetOutput()->GetPoints()->GetNumberOfPoints();
  vtkSmartPointer<vtkFloatArray> scalars =
    vtkSmartPointer<vtkFloatArray>::New();
  scalars->SetNumberOfValues( numPts );
  for( int i = 0; i < numPts; ++i )
  {
    scalars->SetValue(i,static_cast<float>(i)/numPts);
  }
  vtkSmartPointer<vtkPolyData> poly =
    vtkSmartPointer<vtkPolyData>::New();
  poly->DeepCopy(sphere->GetOutput());
  poly->GetPointData()->SetScalars(scalars);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInput(poly);
#else
  mapper->SetInputData(poly);
#endif
  mapper->ScalarVisibilityOn();
  mapper->SetScalarModeToUsePointData();
  mapper->SetColorModeToMapScalars();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkScalarBarActor> scalarBar =
    vtkSmartPointer<vtkScalarBarActor>::New();
  scalarBar->SetLookupTable(mapper->GetLookupTable());
  scalarBar->SetTitle("Title");
  scalarBar->SetNumberOfLabels(4);

  // Create a lookup table to share between the mapper and the scalarbar
  vtkSmartPointer<vtkLookupTable> hueLut =
    vtkSmartPointer<vtkLookupTable>::New();
  hueLut->SetTableRange (0, 1);
  hueLut->SetHueRange (0, 1);
  hueLut->SetSaturationRange (1, 1);
  hueLut->SetValueRange (1, 1);
  hueLut->Build();

  mapper->SetLookupTable( hueLut );
  scalarBar->SetLookupTable( hueLut );

  // Create a renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  renderer->GradientBackgroundOn();
  renderer->SetBackground(1,1,1);
  renderer->SetBackground2(0,0,0);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Create an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->AddActor2D(scalarBar);

  // Render the scene (lights and cameras are created automatically)
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ScalarBarActor)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ScalarBarActor MACOSX_BUNDLE ScalarBarActor.cxx)
 
target_link_libraries(ScalarBarActor ${VTK_LIBRARIES})
```

**Download and Build ScalarBarActor**

Click [here to download ScalarBarActor](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ScalarBarActor.tar) and its *CMakeLists.txt* file.
Once the *tarball ScalarBarActor.tar* has been downloaded and extracted,
```
cd ScalarBarActor/build 
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
./ScalarBarActor
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

