[VTKExamples](/home/)/[Cxx](/Cxx)/VisualizationAlgorithms/TubesFromSplines

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/VisualizationAlgorithms/TestTubesFromSplines.png?raw=true" width="256" />

### Description
This example shows how to interpolate a set of points and generate tubes around the resulting polyline. Scalars associated with the points are also interpolated and used to vary the radius of the tube.

'''NOTE:''' This example was inspired by a question asked by ''Adam Sankowski''.

**TubesFromSplines.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkVersion.h>

#include <vtkParametricFunctionSource.h>
#include <vtkTupleInterpolator.h>
#include <vtkTubeFilter.h>
#include <vtkParametricSpline.h>

#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertPoint(0,1,0,0);
  points->InsertPoint(1,2,0,0);
  points->InsertPoint(2,3,1,0);
  points->InsertPoint(3,4,1,0);
  points->InsertPoint(4,5,0,0);
  points->InsertPoint(5,6,0,0);

  // Fit a spline to the points
  vtkSmartPointer<vtkParametricSpline> spline =
    vtkSmartPointer<vtkParametricSpline>::New();
  spline->SetPoints(points);
  vtkSmartPointer<vtkParametricFunctionSource> functionSource =
    vtkSmartPointer<vtkParametricFunctionSource>::New();
  functionSource->SetParametricFunction(spline);
  functionSource->SetUResolution(10 * points->GetNumberOfPoints());
  functionSource->Update();

  // Interpolate the scalars
  double rad;
  vtkSmartPointer<vtkTupleInterpolator> interpolatedRadius =
    vtkSmartPointer<vtkTupleInterpolator> ::New();
  interpolatedRadius->SetInterpolationTypeToLinear();
  interpolatedRadius->SetNumberOfComponents(1);
  rad = .2; interpolatedRadius->AddTuple(0,&rad);
  rad = .2; interpolatedRadius->AddTuple(1,&rad);
  rad = .2; interpolatedRadius->AddTuple(2,&rad);
  rad = .1; interpolatedRadius->AddTuple(3,&rad);
  rad = .1; interpolatedRadius->AddTuple(4,&rad);
  rad = .1; interpolatedRadius->AddTuple(5,&rad);

  // Generate the radius scalars
  vtkSmartPointer<vtkDoubleArray> tubeRadius =
    vtkSmartPointer<vtkDoubleArray>::New();
  unsigned int n = functionSource->GetOutput()->GetNumberOfPoints();
  tubeRadius->SetNumberOfTuples(n);
  tubeRadius->SetName("TubeRadius");
  double tMin = interpolatedRadius->GetMinimumT();
  double tMax = interpolatedRadius->GetMaximumT();
  double r;
  for (unsigned int i = 0; i < n; ++i)
  {
    double t = (tMax - tMin) / (n - 1) * i + tMin;
    interpolatedRadius->InterpolateTuple(t, &r);
    tubeRadius->SetTuple1(i, r);
  }

  // Add the scalars to the polydata
  vtkSmartPointer<vtkPolyData> tubePolyData =
    vtkSmartPointer<vtkPolyData>::New();
  tubePolyData = functionSource->GetOutput();
  tubePolyData->GetPointData()->AddArray(tubeRadius);
  tubePolyData->GetPointData()->SetActiveScalars("TubeRadius");

  // Create the tubes
  vtkSmartPointer<vtkTubeFilter> tuber =
    vtkSmartPointer<vtkTubeFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  tuber->SetInput(tubePolyData);
#else
  tuber->SetInputData(tubePolyData);
#endif
  tuber->SetNumberOfSides(20);
  tuber->SetVaryRadiusToVaryRadiusByAbsoluteScalar();

  //--------------
  // Setup actors and mappers
  vtkSmartPointer<vtkPolyDataMapper> lineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  lineMapper->SetInput(tubePolyData);
#else
  lineMapper->SetInputData(tubePolyData);
#endif
  lineMapper->SetScalarRange(tubePolyData->GetScalarRange());

  vtkSmartPointer<vtkPolyDataMapper> tubeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  tubeMapper->SetInputConnection(tuber->GetOutputPort());
  tubeMapper->SetScalarRange(tubePolyData->GetScalarRange());

  vtkSmartPointer<vtkActor> lineActor = vtkSmartPointer<vtkActor>::New();
  lineActor->SetMapper(lineMapper);
  vtkSmartPointer<vtkActor> tubeActor = vtkSmartPointer<vtkActor>::New();
  tubeActor->SetMapper(tubeMapper);

  // Setup render window, renderer, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(lineActor);
  renderer->AddActor(tubeActor);
  renderer->SetBackground(.4, .5, .6);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TubesFromSplines)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TubesFromSplines MACOSX_BUNDLE TubesFromSplines.cxx)
 
target_link_libraries(TubesFromSplines ${VTK_LIBRARIES})
```

**Download and Build TubesFromSplines**

Click [here to download TubesFromSplines](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TubesFromSplines.tar) and its *CMakeLists.txt* file.
Once the *tarball TubesFromSplines.tar* has been downloaded and extracted,
```
cd TubesFromSplines/build 
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
./TubesFromSplines
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

