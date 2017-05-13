[VTKExamples](/index/)/[Cxx](/Cxx)/StructuredGrid/StructuredGridOutline

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/StructuredGrid/TestStructuredGridOutline.png?raw=true" width="256" />

### Description
Visualize the outline of a structured grid.

**StructuredGridOutline.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkMath.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkStructuredGridOutlineFilter.h>

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

  //specify the dimensions of the grid
  structuredGrid->SetDimensions(numi, numj, numk);
  structuredGrid->SetPoints(points);

  std::cout << "There are " << structuredGrid->GetNumberOfPoints() << " points." << std::endl;
  std::cout << "There are " << structuredGrid->GetNumberOfCells() << " cells." << std::endl;

  vtkSmartPointer<vtkStructuredGridOutlineFilter> outlineFilter =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  outlineFilter->SetInputConnection(structuredGrid->GetProducerPort());
#else
  outlineFilter->SetInputData(structuredGrid);
#endif
  outlineFilter->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(outlineFilter->GetOutputPort());
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
  //renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(StructuredGridOutline)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(StructuredGridOutline MACOSX_BUNDLE StructuredGridOutline.cxx)
 
target_link_libraries(StructuredGridOutline ${VTK_LIBRARIES})
```

**Download and Build StructuredGridOutline**

Click [here to download StructuredGridOutline](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/StructuredGridOutline.tar) and its *CMakeLists.txt* file.
Once the *tarball StructuredGridOutline.tar* has been downloaded and extracted,
```
cd StructuredGridOutline/build 
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
./StructuredGridOutline
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

