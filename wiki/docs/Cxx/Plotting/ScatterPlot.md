[VTKExamples](Home)/[Cxx](Cxx)/Plotting/ScatterPlot

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Plotting/TestScatterPlot.png" width="256" />

**ScatterPlot.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkChartXY.h>
#include <vtkContextScene.h>
#include <vtkContextView.h>
#include <vtkFloatArray.h>
#include <vtkPlotPoints.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTable.h>

int main(int, char*[])
{
  // Set up a 2D scene, add an XY chart to it
  vtkSmartPointer<vtkContextView> view =
    vtkSmartPointer<vtkContextView>::New();
  view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
  view->GetRenderWindow()->SetSize(400, 300);

  vtkSmartPointer<vtkChartXY> chart =
    vtkSmartPointer<vtkChartXY>::New();
  view->GetScene()->AddItem(chart);
  chart->SetShowLegend(true);

  // Create a table with some points in it...
  vtkSmartPointer<vtkTable> table =
    vtkSmartPointer<vtkTable>::New();

  vtkSmartPointer<vtkFloatArray> arrX =
    vtkSmartPointer<vtkFloatArray>::New();
  arrX->SetName("X Axis");
  table->AddColumn(arrX);

  vtkSmartPointer<vtkFloatArray> arrC =
    vtkSmartPointer<vtkFloatArray>::New();
  arrC->SetName("Cosine");
  table->AddColumn(arrC);

  vtkSmartPointer<vtkFloatArray> arrS =
    vtkSmartPointer<vtkFloatArray>::New();
  arrS->SetName("Sine");
  table->AddColumn(arrS);

  vtkSmartPointer<vtkFloatArray> arrT =
    vtkSmartPointer<vtkFloatArray>::New();
  arrT->SetName("Sine - Cosine");
  table->AddColumn(arrT);

  // Test charting with a few more points...
  int numPoints = 40;
  float inc = 7.5 / (numPoints-1);
  table->SetNumberOfRows(numPoints);
  for (int i = 0; i < numPoints; ++i)
  {
    table->SetValue(i, 0, i * inc);
    table->SetValue(i, 1, cos(i * inc) + 0.0);
    table->SetValue(i, 2, sin(i * inc) + 0.0);
    table->SetValue(i, 3, sin(i * inc) - cos(i * inc));
  }

  // Add multiple scatter plots, setting the colors etc
  vtkPlot *points = chart->AddPlot(vtkChart::POINTS);
#if VTK_MAJOR_VERSION <= 5
  points->SetInput(table, 0, 1);
#else
  points->SetInputData(table, 0, 1);
#endif
  points->SetColor(0, 0, 0, 255);
  points->SetWidth(1.0);
  vtkPlotPoints::SafeDownCast(points)->SetMarkerStyle(vtkPlotPoints::CROSS);

  points = chart->AddPlot(vtkChart::POINTS);
#if VTK_MAJOR_VERSION <= 5
  points->SetInput(table, 0, 2);
#else
  points->SetInputData(table, 0, 2);
#endif
  points->SetColor(0, 0, 0, 255);
  points->SetWidth(1.0);
  vtkPlotPoints::SafeDownCast(points)->SetMarkerStyle(vtkPlotPoints::PLUS);

  points = chart->AddPlot(vtkChart::POINTS);
#if VTK_MAJOR_VERSION <= 5
  points->SetInput(table, 0, 3);
#else
  points->SetInputData(table, 0, 3);
#endif
  points->SetColor(0, 0, 255, 255);
  points->SetWidth(1.0);
  vtkPlotPoints::SafeDownCast(points)->SetMarkerStyle(vtkPlotPoints::CIRCLE);

  //Finally render the scene
  view->GetRenderWindow()->SetMultiSamples(0);
  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ScatterPlot)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ScatterPlot MACOSX_BUNDLE ScatterPlot.cxx)
 
target_link_libraries(ScatterPlot ${VTK_LIBRARIES})
```

**Download and Build ScatterPlot**

Click [here to download ScatterPlot](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ScatterPlot.tar) and its *CMakeLists.txt* file.
Once the *tarball ScatterPlot.tar* has been downloaded and extracted,
```
cd ScatterPlot/build 
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
./ScatterPlot
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

