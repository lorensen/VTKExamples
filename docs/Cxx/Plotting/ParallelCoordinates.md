[VTKExamples](/index/)/[Cxx](/Cxx)/Plotting/ParallelCoordinates

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Plotting/TestParallelCoordinates.png?raw=true" width="256" />

**ParallelCoordinates.cxx**
```c++
#include <vtkVersion.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartParallelCoordinates.h>
#include <vtkPlot.h>
#include <vtkTable.h>
#include <vtkFloatArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char*[])
{
  // Set up a 2D scene, add an XY chart to it
  vtkSmartPointer<vtkContextView> view =
    vtkSmartPointer<vtkContextView>::New();
  view->GetRenderer()->SetBackground(.2, .3, .4);
  view->GetRenderWindow()->SetSize(800, 600);
  vtkSmartPointer<vtkChartParallelCoordinates> chart =
    vtkSmartPointer<vtkChartParallelCoordinates>::New();
  view->GetScene()->AddItem(chart);

  // Create a table with some points in it...
  vtkSmartPointer<vtkTable> table =
    vtkSmartPointer<vtkTable>::New();
  vtkSmartPointer<vtkFloatArray> arrX =
    vtkSmartPointer<vtkFloatArray>::New();
  arrX->SetName("Field 1");
  table->AddColumn(arrX);
  vtkSmartPointer<vtkFloatArray> arrC =
    vtkSmartPointer<vtkFloatArray>::New();
  arrC->SetName("Field 2");
  table->AddColumn(arrC);
  vtkSmartPointer<vtkFloatArray> arrS =
    vtkSmartPointer<vtkFloatArray>::New();
  arrS->SetName("Field 3");
  table->AddColumn(arrS);
  vtkSmartPointer<vtkFloatArray> arrS2 =
    vtkSmartPointer<vtkFloatArray>::New();
  arrS2->SetName("Field 4");
  table->AddColumn(arrS2);
  // Test charting with a few more points...

  table->SetNumberOfRows(10);
  for (int i = 0; i < 10; ++i)
  {
    table->SetValue(i, 0, 0 * i);
    table->SetValue(i, 1, 1 * i);
    table->SetValue(i, 2, 2 * i);
    table->SetValue(i, 3, 3 * i);
  }

#if VTK_MAJOR_VERSION <= 5
  chart->GetPlot(0)->SetInput(table);
#else
  chart->GetPlot(0)->SetInputData(table);
#endif

  view->GetRenderWindow()->SetMultiSamples(0);

  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ParallelCoordinates)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ParallelCoordinates MACOSX_BUNDLE ParallelCoordinates.cxx)
 
target_link_libraries(ParallelCoordinates ${VTK_LIBRARIES})
```

**Download and Build ParallelCoordinates**

Click [here to download ParallelCoordinates](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ParallelCoordinates.tar) and its *CMakeLists.txt* file.
Once the *tarball ParallelCoordinates.tar* has been downloaded and extracted,
```
cd ParallelCoordinates/build 
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
./ParallelCoordinates
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

