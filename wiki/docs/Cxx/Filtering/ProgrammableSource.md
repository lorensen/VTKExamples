[VTKExamples](/index/)/[Cxx](/Cxx)/Filtering/ProgrammableSource

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestProgrammableSource.png?raw=true" width="256" />

### Description
Use a programmable source to generate the points for the [Lorenz System](https://en.wikipedia.org/wiki/Lorenz_system)

**ProgrammableSource.cxx**
```c++
#include <vtkVersion.h>

#include "vtkSmartPointer.h"
#include "vtkProgrammableSource.h"
#include "vtkPolyData.h"
#include "vtkVertexGlyphFilter.h"
#include "vtkPoints.h"

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

// https://en.wikipedia.org/wiki/Lorenz_system
static void Lorenz(void *arg)
{
  double sigma = 10.0;	/* The Lorenz paramaters */
  double beta = 8.0 / 3.0;
  double rho = 28.0;
  double h = .001;      /* Integration step size */

  double x, y, z;
  double xx, yy, zz;
  x = 0.1;
  y = 0.1;
  z = 0.1;
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  // Get to a stable starting point
  for (int i = 0; i < 1000; ++i)
  {
    xx = x + h * sigma * (y - x);
    yy = y + h * (x * (rho - z) - y);
    zz = z + h * (x * y - (beta * z));
    x = xx; y = yy; z = zz;
  }
  for (int i = 0; i < 500000; ++i)
  {
    xx = x + h * sigma * (y - x);
    yy = y + h * (x * (rho - z) - y);
    zz = z + h * (x * y - (beta * z));
    points->InsertNextPoint(xx, yy, zz);
    x = xx; y = yy; z = zz;
  }
  vtkSmartPointer<vtkPolyData> pointsPolydata =
    vtkSmartPointer<vtkPolyData>::New();
  pointsPolydata->SetPoints(points);
  vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  vertexFilter->SetInputConnection(pointsPolydata->GetProducerPort());
#else
  vertexFilter->SetInputData(pointsPolydata);
#endif
  vertexFilter->Update();
  vtkProgrammableSource * ps =
    static_cast<vtkProgrammableSource *>(arg);
  vtkPolyData *output = ps->GetPolyDataOutput();
  output->DeepCopy(vertexFilter->GetOutput());
}

int main (int, char *[])
{
  vtkSmartPointer<vtkProgrammableSource> source =
    vtkSmartPointer<vtkProgrammableSource>::New();
  source->SetExecuteMethod(Lorenz, source);
  source->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInput(source->GetPolyDataOutput());
#else
  mapper->SetInputData(source->GetPolyDataOutput());
#endif
  
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Setup render window, renderer, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(actor);
  renderer->SetBackground(.4, .5, .7);
  renderWindow->Render();
  renderWindowInteractor->Start();

 return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ProgrammableSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ProgrammableSource MACOSX_BUNDLE ProgrammableSource.cxx)
 
target_link_libraries(ProgrammableSource ${VTK_LIBRARIES})
```

**Download and Build ProgrammableSource**

Click [here to download ProgrammableSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ProgrammableSource.tar) and its *CMakeLists.txt* file.
Once the *tarball ProgrammableSource.tar* has been downloaded and extracted,
```
cd ProgrammableSource/build 
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
./ProgrammableSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

