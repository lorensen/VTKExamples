[VTKExamples](/home/)/[Cxx](/Cxx)/StructuredGrid/VisualizeStructuredGrid

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/StructuredGrid/TestVisualizeStructuredGrid.png?raw=true" width="256" />

### Description
Visualize the points of a structured grid.

**VisualizeStructuredGrid.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkMath.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkStructuredGridGeometryFilter.h>

int main(int, char *[])
{
  // Create a grid
  vtkSmartPointer<vtkStructuredGrid> structuredGrid =
    vtkSmartPointer<vtkStructuredGrid>::New();

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  unsigned int numi = 2;
  unsigned int numj = 3;
  unsigned int numk = 2;

  for(unsigned int k = 0; k < numk; k++)
  {
    for(unsigned int j = 0; j < numj; j++)
    {
      for(unsigned int i = 0; i < numi; i++)
      {
        points->InsertNextPoint(i, j, k);
      }
    }
  }

  // Specify the dimensions of the grid
  structuredGrid->SetDimensions(numi, numj, numk);
  structuredGrid->SetPoints(points);

  std::cout << "There are " << structuredGrid->GetNumberOfPoints() << " points." << std::endl; // there should be 2*3*2 = 12 points
  std::cout << "There are " << structuredGrid->GetNumberOfCells() << " cells." << std::endl; // The 12 points define the corners of 2 cubes/cells (4 points are shared by both cubes)

  vtkSmartPointer<vtkStructuredGridGeometryFilter> geometryFilter =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  geometryFilter->SetInputConnection(structuredGrid->GetProducerPort());
#else
  geometryFilter->SetInputData(structuredGrid);
#endif
  geometryFilter->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(geometryFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(3);

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
  renderer->SetBackground(.2, .3, .4);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(VisualizeStructuredGrid)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VisualizeStructuredGrid MACOSX_BUNDLE VisualizeStructuredGrid.cxx)
 
target_link_libraries(VisualizeStructuredGrid ${VTK_LIBRARIES})
```

**Download and Build VisualizeStructuredGrid**

Click [here to download VisualizeStructuredGrid](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VisualizeStructuredGrid.tar) and its *CMakeLists.txt* file.
Once the *tarball VisualizeStructuredGrid.tar* has been downloaded and extracted,
```
cd VisualizeStructuredGrid/build 
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
./VisualizeStructuredGrid
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

