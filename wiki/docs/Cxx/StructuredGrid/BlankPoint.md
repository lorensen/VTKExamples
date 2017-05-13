[VTKExamples](/home/)/[Cxx](/Cxx)/StructuredGrid/BlankPoint

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/StructuredGrid/TestBlankPoint.png?raw=true" width="256" />

**BlankPoint.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkIdList.h>
#include <vtkProperty.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkMath.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLStructuredGridWriter.h>

int main(int, char *[])
{
  // Create a grid
  vtkSmartPointer<vtkStructuredGrid> structuredGrid =
    vtkSmartPointer<vtkStructuredGrid>::New();

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  unsigned int gridSize = 8;
  unsigned int counter = 0;
  // Create a 5x5 grid of points
  for(unsigned int j = 0; j < gridSize; j++)
  {
    for(unsigned int i = 0; i < gridSize; i++)
    {
      if(i == 3 && j == 3) // Make one point higher than the rest
      {
        points->InsertNextPoint(i, j, 2);
	std::cout << "The different point is number " << counter << std::endl;
      }
      else
      {
        points->InsertNextPoint(i, j, 0); // Make most of the points the same height
      }
      counter++;
    }
  }

  // Specify the dimensions of the grid
  structuredGrid->SetDimensions(gridSize,gridSize,1);

  structuredGrid->SetPoints(points);

  structuredGrid->BlankPoint(27);
  structuredGrid->Modified();

  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> gridMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  gridMapper->SetInputConnection(structuredGrid->GetProducerPort());
#else
  gridMapper->SetInputData(structuredGrid);
#endif

  vtkSmartPointer<vtkActor> gridActor =
    vtkSmartPointer<vtkActor>::New();
  gridActor->SetMapper(gridMapper);
  gridActor->GetProperty()->EdgeVisibilityOn();
  gridActor->GetProperty()->SetEdgeColor(0,0,1);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(gridActor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BlankPoint)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BlankPoint MACOSX_BUNDLE BlankPoint.cxx)
 
target_link_libraries(BlankPoint ${VTK_LIBRARIES})
```

**Download and Build BlankPoint**

Click [here to download BlankPoint](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BlankPoint.tar) and its *CMakeLists.txt* file.
Once the *tarball BlankPoint.tar* has been downloaded and extracted,
```
cd BlankPoint/build 
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
./BlankPoint
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

