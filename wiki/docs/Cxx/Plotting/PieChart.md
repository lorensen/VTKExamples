[VTKExamples](Home)/[Cxx](Cxx)/Plotting/PieChart

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Plotting/TestPieChart.png" width="256" />

**PieChart.cxx**
```c++
#include <vtkVersion.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartPie.h>
#include <vtkPlot.h>
#include <vtkPlotPie.h>
#include <vtkTable.h>
#include <vtkIntArray.h>
#include <vtkStringArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkColorSeries.h>

int NUM_ITEMS = 5;
static int data[] = {77938,9109,2070,12806,19514};
//static int data[] = {200,200,200,200,200};
static const char *labels[] = {"Books","New and Popular","Periodical","Audiobook","Video"};

int main(int, char*[])
{
  // Set up a 2D scene, add an XY chart to it
  vtkSmartPointer<vtkContextView> view =
    vtkSmartPointer<vtkContextView>::New();
  view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
  view->GetRenderWindow()->SetSize(600, 350);
  vtkSmartPointer<vtkChartPie> chart =
    vtkSmartPointer<vtkChartPie>::New();
  view->GetScene()->AddItem(chart);

  // Create a table with some points in it...
  vtkSmartPointer<vtkTable> table =
    vtkSmartPointer<vtkTable>::New();

  vtkSmartPointer<vtkIntArray> arrData =
    vtkSmartPointer<vtkIntArray>::New();
  vtkSmartPointer<vtkStringArray> labelArray =
    vtkSmartPointer<vtkStringArray>::New();

  arrData->SetName("2008 Circulation");
  for (int i = 0; i < NUM_ITEMS; i++)
  {
    arrData->InsertNextValue(data[i]);
    labelArray->InsertNextValue(labels[i]);
  }

  table->AddColumn(arrData);

  // Create a color series to use with our stacks.
  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  colorSeries->SetColorScheme(vtkColorSeries::WARM);

  // Add multiple line plots, setting the colors etc
  vtkPlotPie *pie = vtkPlotPie::SafeDownCast(chart->AddPlot(0));
  pie->SetColorSeries(colorSeries);
#if VTK_MAJOR_VERSION <= 5
  pie->SetInput(table);
#else
  pie->SetInputData(table);
#endif
  pie->SetInputArray(0,"2008 Circulation");
  pie->SetLabels(labelArray);

  chart->SetShowLegend(true);

  chart->SetTitle("Circulation 2008");

  //Finally render the scene and compare the image to a reference image
  view->GetRenderWindow()->SetMultiSamples(0);
  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PieChart)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PieChart MACOSX_BUNDLE PieChart.cxx)
 
target_link_libraries(PieChart ${VTK_LIBRARIES})
```

**Download and Build PieChart**

Click [here to download PieChart](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PieChart.tar) and its *CMakeLists.txt* file.
Once the *tarball PieChart.tar* has been downloaded and extracted,
```
cd PieChart/build 
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
./PieChart
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

