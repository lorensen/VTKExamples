[VTKExamples](Home)/[Cxx](Cxx)/RectilinearGrid/VisualizeRectilinearGrid

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/RectilinearGrid/TestVisualizeRectilinearGrid.png" width="256" />


**VisualizeRectilinearGrid.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkRectilinearGrid.h>
#include <vtkMath.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkShrinkFilter.h>
#include <vtkDoubleArray.h>

int main(int, char *[])
{
  // Create a grid
  vtkSmartPointer<vtkRectilinearGrid> grid = 
    vtkSmartPointer<vtkRectilinearGrid>::New();
  
  grid->SetDimensions(2,3,2);
  
  vtkSmartPointer<vtkDoubleArray> xArray = 
    vtkSmartPointer<vtkDoubleArray>::New();
  xArray->InsertNextValue(0.0);
  xArray->InsertNextValue(2.0);
  
  vtkSmartPointer<vtkDoubleArray> yArray = 
    vtkSmartPointer<vtkDoubleArray>::New();
  yArray->InsertNextValue(0.0);
  yArray->InsertNextValue(1.0);
  yArray->InsertNextValue(2.0);
  
  vtkSmartPointer<vtkDoubleArray> zArray = 
    vtkSmartPointer<vtkDoubleArray>::New();
  zArray->InsertNextValue(0.0);
  zArray->InsertNextValue(5.0);
  
  grid->SetXCoordinates(xArray);
  grid->SetYCoordinates(yArray);
  grid->SetZCoordinates(zArray);
  
  vtkSmartPointer<vtkShrinkFilter> shrinkFilter = 
    vtkSmartPointer<vtkShrinkFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  shrinkFilter->SetInputConnection(grid->GetProducerPort());
#else
  shrinkFilter->SetInputData(grid);
#endif
  shrinkFilter->SetShrinkFactor(.8);
  
  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(shrinkFilter->GetOutputPort());

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
 
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(VisualizeRectilinearGrid)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VisualizeRectilinearGrid MACOSX_BUNDLE VisualizeRectilinearGrid.cxx)
 
target_link_libraries(VisualizeRectilinearGrid ${VTK_LIBRARIES})
```

**Download and Build VisualizeRectilinearGrid**

Click [here to download VisualizeRectilinearGrid](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VisualizeRectilinearGrid.tar) and its *CMakeLists.txt* file.
Once the *tarball VisualizeRectilinearGrid.tar* has been downloaded and extracted,
```
cd VisualizeRectilinearGrid/build 
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
./VisualizeRectilinearGrid
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

