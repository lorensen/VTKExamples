[VTKExamples](/home/)/[Cxx](/Cxx)/RectilinearGrid/RectilinearGrid

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/RectilinearGrid/TestRectilinearGrid.png?raw=true" width="256" />


**RectilinearGrid.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkRectilinearGrid.h>
#include <vtkMath.h>
#include <vtkDoubleArray.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create a grid
  vtkSmartPointer<vtkRectilinearGrid> grid =
    vtkSmartPointer<vtkRectilinearGrid>::New();

  grid->SetDimensions(2,3,1);

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

  grid->SetXCoordinates(xArray);
  grid->SetYCoordinates(yArray);
  grid->SetZCoordinates(zArray);

  std::cout << "There are " << grid->GetNumberOfPoints()
            << " points." << std::endl;
  std::cout << "There are " << grid->GetNumberOfCells()
            << " cells." << std::endl;

  for(vtkIdType id = 0; id < grid->GetNumberOfPoints(); id++)
  {
    double p[3];
    grid->GetPoint(id, p);
    std::cout << "Point " << id
              << " : (" << p[0] << " , " << p[1] << " , " << p[2] << ")" << std::endl;
  }

  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInputConnection(grid->GetProducerPort());
#else
  mapper->SetInputData(grid);
#endif

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
  renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RectilinearGrid)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RectilinearGrid MACOSX_BUNDLE RectilinearGrid.cxx)
 
target_link_libraries(RectilinearGrid ${VTK_LIBRARIES})
```

**Download and Build RectilinearGrid**

Click [here to download RectilinearGrid](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RectilinearGrid.tar) and its *CMakeLists.txt* file.
Once the *tarball RectilinearGrid.tar* has been downloaded and extracted,
```
cd RectilinearGrid/build 
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
./RectilinearGrid
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

