[VTKExamples](Home)/[Cxx](Cxx)/Visualization/HedgeHog

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestHedgeHog.png" width="256" />

**HedgeHog.cxx**
```c++
#include <vtkVersion.h>
#include "vtkSmartPointer.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkFloatArray.h"
#include "vtkHedgeHog.h"
#include "vtkMath.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkStructuredGrid.h"

static void CreateData(vtkStructuredGrid* sgrid);

int main(int, char*[])
{
  // Create the structured grid.
  vtkSmartPointer<vtkStructuredGrid> sgrid =
    vtkSmartPointer<vtkStructuredGrid>::New();
  CreateData(sgrid);

  // We create a simple pipeline to display the data.
  vtkSmartPointer<vtkHedgeHog> hedgehog =
    vtkSmartPointer<vtkHedgeHog>::New();
#if VTK_MAJOR_VERSION <= 5
  hedgehog->SetInput(sgrid);
#else
  hedgehog->SetInputData(sgrid);
#endif
  hedgehog->SetScaleFactor(0.1);

  vtkSmartPointer<vtkPolyDataMapper> sgridMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sgridMapper->SetInputConnection(hedgehog->GetOutputPort());

  vtkSmartPointer<vtkActor> sgridActor =
    vtkSmartPointer<vtkActor>::New();
  sgridActor->SetMapper(sgridMapper);
  sgridActor->GetProperty()->SetColor(0,0,0);

  // Create the usual rendering stuff
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  renderer->AddActor(sgridActor);
  renderer->SetBackground(1,1,1);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Elevation(60.0);
  renderer->GetActiveCamera()->Azimuth(30.0);
  renderer->GetActiveCamera()->Zoom(1.25);
  renWin->SetSize(300,300);

  // interact with data
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}

void CreateData(vtkStructuredGrid* sgrid)
{
  int i, j, k, kOffset, jOffset, offset;
  float x[3], v[3], rMin=0.5, rMax=1.0, deltaRad, deltaZ;
  float radius, theta;
  static int dims[3]={13,11,11};
  sgrid->SetDimensions(dims);

  // We also create the points and vectors. The points
  // form a hemi-cylinder of data.
  vtkSmartPointer<vtkFloatArray> vectors =
    vtkSmartPointer<vtkFloatArray>::New();
  vectors->SetNumberOfComponents(3);
  vectors->SetNumberOfTuples(dims[0]*dims[1]*dims[2]);

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->Allocate(dims[0]*dims[1]*dims[2]);

  deltaZ = 2.0 / (dims[2]-1);
  deltaRad = (rMax-rMin) / (dims[1]-1);
  v[2]=0.0;
  for ( k=0; k<dims[2]; k++)
  {
    x[2] = -1.0 + k*deltaZ;
    kOffset = k * dims[0] * dims[1];
    for (j=0; j<dims[1]; j++)
    {
      radius = rMin + j*deltaRad;
      jOffset = j * dims[0];
      for (i=0; i<dims[0]; i++)
      {
        theta = i * vtkMath::RadiansFromDegrees(15.0);
        x[0] = radius * cos(theta);
        x[1] = radius * sin(theta);
        v[0] = -x[1];
        v[1] = x[0];
        offset = i + jOffset + kOffset;
        points->InsertPoint(offset,x);
        vectors->InsertTuple(offset,v);
      }
    }
  }
  sgrid->SetPoints(points);

  sgrid->GetPointData()->SetVectors(vectors);
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(HedgeHog)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(HedgeHog MACOSX_BUNDLE HedgeHog.cxx)
 
target_link_libraries(HedgeHog ${VTK_LIBRARIES})
```

**Download and Build HedgeHog**

Click [here to download HedgeHog](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/HedgeHog.tar) and its *CMakeLists.txt* file.
Once the *tarball HedgeHog.tar* has been downloaded and extracted,
```
cd HedgeHog/build 
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
./HedgeHog
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

