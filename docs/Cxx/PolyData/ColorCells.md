[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/ColorCells

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestColorCells.png?raw=true" width="256" />

### Description
This example shows how to assign specific colors to individual cells of a polydata.

**ColorCells.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkLookupTable.h>
#include <vtkFloatArray.h>
#include <vtkCellData.h>
#include <vtkPolyData.h>
#include <vtkPlaneSource.h>

#include <algorithm>

int main(int , char *[])
{
  // Provide some geometry
  int resolution = 3;
  vtkSmartPointer<vtkPlaneSource> aPlane =
    vtkSmartPointer<vtkPlaneSource>::New();
  aPlane->SetXResolution(resolution);
  aPlane->SetYResolution(resolution);

  // Create cell data
  vtkSmartPointer<vtkFloatArray> cellData =
    vtkSmartPointer<vtkFloatArray>::New();
  for (int i = 0; i < resolution * resolution; i++)
  {
    cellData->InsertNextValue(i + 1);
  }

  // Create a lookup table to map cell data to colors
  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  int tableSize = std::max(resolution*resolution + 1, 10);
  lut->SetNumberOfTableValues(tableSize);
  lut->Build();

  // Fill in a few known colors, the rest will be generated if needed
  lut->SetTableValue(0     , 0     , 0     , 0, 1);  //Black
  lut->SetTableValue(1, 0.8900, 0.8100, 0.3400, 1); // Banana
  lut->SetTableValue(2, 1.0000, 0.3882, 0.2784, 1); // Tomato
  lut->SetTableValue(3, 0.9608, 0.8706, 0.7020, 1); // Wheat
  lut->SetTableValue(4, 0.9020, 0.9020, 0.9804, 1); // Lavender
  lut->SetTableValue(5, 1.0000, 0.4900, 0.2500, 1); // Flesh
  lut->SetTableValue(6, 0.5300, 0.1500, 0.3400, 1); // Raspberry
  lut->SetTableValue(7, 0.9804, 0.5020, 0.4471, 1); // Salmon
  lut->SetTableValue(8, 0.7400, 0.9900, 0.7900, 1); // Mint
  lut->SetTableValue(9, 0.2000, 0.6300, 0.7900, 1); // Peacock

  aPlane->Update(); // Force an update so we can set cell data
  aPlane->GetOutput()->GetCellData()->SetScalars(cellData);

  // Setup actor and mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(aPlane->GetOutputPort());
  mapper->SetScalarRange(0, tableSize - 1);
  mapper->SetLookupTable(lut);

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
 
PROJECT(ColorCells)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ColorCells MACOSX_BUNDLE ColorCells.cxx)
 
target_link_libraries(ColorCells ${VTK_LIBRARIES})
```

**Download and Build ColorCells**

Click [here to download ColorCells](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ColorCells.tar) and its *CMakeLists.txt* file.
Once the *tarball ColorCells.tar* has been downloaded and extracted,
```
cd ColorCells/build 
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
./ColorCells
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

