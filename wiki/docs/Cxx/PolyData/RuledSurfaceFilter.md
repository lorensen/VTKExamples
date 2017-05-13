[VTKExamples](Home)/[Cxx](Cxx)/PolyData/RuledSurfaceFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/PolyData/TestRuledSurfaceFilter.png" width="256" />

**RuledSurfaceFilter.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkRuledSurfaceFilter.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCellArray.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkAppendPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkLine.h>

int main(int, char *[])
{

  // Create first line.
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertPoint(0, 0, 0, 1);
  points->InsertPoint(1, 1, 0, 0);
  points->InsertPoint(2, 0, 1, 0);
  points->InsertPoint(3, 1, 1, 1);
  
  vtkSmartPointer<vtkLine> line1 = 
    vtkSmartPointer<vtkLine>::New();
  line1->GetPointIds()->SetId(0,0);
  line1->GetPointIds()->SetId(1,1);
  
  vtkSmartPointer<vtkLine> line2 = 
    vtkSmartPointer<vtkLine>::New();
  line2->GetPointIds()->SetId(0,2);
  line2->GetPointIds()->SetId(1,3);
  
  vtkSmartPointer<vtkCellArray> lines =
    vtkSmartPointer<vtkCellArray>::New();
  lines->InsertNextCell(line1);
  lines->InsertNextCell(line2);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetLines(lines);

  vtkSmartPointer<vtkRuledSurfaceFilter> ruledSurfaceFilter =
    vtkSmartPointer<vtkRuledSurfaceFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  ruledSurfaceFilter->SetInputConnection(polydata->GetProducerPort());
#else
  ruledSurfaceFilter->SetInputData(polydata);
#endif
  ruledSurfaceFilter->SetResolution(21, 21);
  ruledSurfaceFilter->SetRuledModeToResample();

  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
    
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(ruledSurfaceFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(0.89, 0.81, 0.34);
 
  // Add the actors to the renderer, set the background and size
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .4, .5);

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(60);
  renderer->GetActiveCamera()->Elevation(60);
  renderer->GetActiveCamera()->Dolly(1.2);
  renderer->ResetCameraClippingRange();

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RuledSurfaceFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RuledSurfaceFilter MACOSX_BUNDLE RuledSurfaceFilter.cxx)
 
target_link_libraries(RuledSurfaceFilter ${VTK_LIBRARIES})
```

**Download and Build RuledSurfaceFilter**

Click [here to download RuledSurfaceFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RuledSurfaceFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball RuledSurfaceFilter.tar* has been downloaded and extracted,
```
cd RuledSurfaceFilter/build 
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
./RuledSurfaceFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

