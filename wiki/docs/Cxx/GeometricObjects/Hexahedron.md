[VTKExamples](/home/)/[Cxx](/Cxx)/GeometricObjects/Hexahedron

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestHexahedron.png?raw=true" width="256" />

### Description
This example creates eight points and creates a hexahedron from the points.

**Hexahedron.cxx**
```c++
#include <vtkVersion.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkHexahedron.h>
#include <vtkUnstructuredGrid.h>

#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Setup the coordinates of eight points 
  // (the two faces must be in counter clockwise order as viewd from the outside)
  double P0[3] = {0.0, 0.0, 0.0};
  double P1[3] = {1.0, 0.0, 0.0};
  double P2[3] = {1.0, 1.0, 0.0};
  double P3[3] = {0.0, 1.0, 0.0};
  double P4[3] = {0.0, 0.0, 1.0};
  double P5[3] = {1.0, 0.0, 1.0};
  double P6[3] = {1.0, 1.0, 1.0};
  double P7[3] = {0.0, 1.0, 1.0};
 
 
  // Create the points
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(P0);
  points->InsertNextPoint(P1);
  points->InsertNextPoint(P2);
  points->InsertNextPoint(P3);
  points->InsertNextPoint(P4);
  points->InsertNextPoint(P5);
  points->InsertNextPoint(P6);
  points->InsertNextPoint(P7);
 
  // Create a hexahedron from the points
  vtkSmartPointer<vtkHexahedron> hex = 
    vtkSmartPointer<vtkHexahedron>::New();
  hex->GetPointIds()->SetId(0,0);
  hex->GetPointIds()->SetId(1,1);
  hex->GetPointIds()->SetId(2,2);
  hex->GetPointIds()->SetId(3,3);
  hex->GetPointIds()->SetId(4,4);
  hex->GetPointIds()->SetId(5,5);
  hex->GetPointIds()->SetId(6,6);
  hex->GetPointIds()->SetId(7,7);
 
  // Add the hexahedron to a cell array
  vtkSmartPointer<vtkCellArray> hexs = 
    vtkSmartPointer<vtkCellArray>::New();
  hexs->InsertNextCell(hex);
 
  // Add the points and hexahedron to an unstructured grid
  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  uGrid->SetPoints(points);
  uGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());
 
  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInputConnection(uGrid->GetProducerPort());
#else
  mapper->SetInputData(uGrid);
#endif

  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

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
 
PROJECT(Hexahedron)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Hexahedron MACOSX_BUNDLE Hexahedron.cxx)
 
target_link_libraries(Hexahedron ${VTK_LIBRARIES})
```

**Download and Build Hexahedron**

Click [here to download Hexahedron](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Hexahedron.tar) and its *CMakeLists.txt* file.
Once the *tarball Hexahedron.tar* has been downloaded and extracted,
```
cd Hexahedron/build 
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
./Hexahedron
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

