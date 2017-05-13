[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/ColorCellsWithRGB

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestColorCellsWithRGB.png?raw=true" width="256" />

### Description
This example shows how to assign specific colors to individual cells of a polydata. This example stores the cell data as rgb triples.

**ColorCellsWithRGB.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkMath.h>
#include <vtkUnsignedCharArray.h>
#include <vtkCellData.h>
#include <vtkPolyData.h>
#include <vtkPlaneSource.h>

int main(int , char *[])
{
  // Provide some geometry
  int resolutionX = 5;
  int resolutionY = 3;

  vtkSmartPointer<vtkPlaneSource> aPlane =
    vtkSmartPointer<vtkPlaneSource>::New();
  aPlane->SetXResolution(resolutionX);
  aPlane->SetYResolution(resolutionY);
  aPlane->Update();

  // Create cell data
  vtkMath::RandomSeed(8775070); // for reproducibility
  vtkSmartPointer<vtkUnsignedCharArray> cellData =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  cellData->SetNumberOfComponents(3);
  cellData->SetNumberOfTuples(aPlane->GetOutput()->GetNumberOfCells());
  for (int i = 0; i < aPlane->GetOutput()->GetNumberOfCells(); i++)
  {
    float rgb[3];
    rgb[0] = vtkMath::Random(64, 255);
    rgb[1] = vtkMath::Random(64, 255);
    rgb[2] = vtkMath::Random(64, 255);
    cellData->InsertTuple(i, rgb);
  }

  aPlane->GetOutput()->GetCellData()->SetScalars(cellData);

  // Setup actor and mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(aPlane->GetOutputPort());

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
  renderer->SetBackground(.1,.2,.3);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ColorCellsWithRGB)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ColorCellsWithRGB MACOSX_BUNDLE ColorCellsWithRGB.cxx)
 
target_link_libraries(ColorCellsWithRGB ${VTK_LIBRARIES})
```

**Download and Build ColorCellsWithRGB**

Click [here to download ColorCellsWithRGB](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ColorCellsWithRGB.tar) and its *CMakeLists.txt* file.
Once the *tarball ColorCellsWithRGB.tar* has been downloaded and extracted,
```
cd ColorCellsWithRGB/build 
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
./ColorCellsWithRGB
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

