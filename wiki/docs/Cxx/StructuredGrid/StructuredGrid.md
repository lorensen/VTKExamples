[VTKExamples](Home)/[Cxx](Cxx)/StructuredGrid/StructuredGrid

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/StructuredGrid/TestStructuredGrid.png" width="256" />

### Description
This example reads and writes points into a structured grid.

Required version: You must have the CVS HEAD of VTK as of 2/17/10.

**StructuredGrid.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create a grid
  vtkSmartPointer<vtkStructuredGrid> structuredGrid =
    vtkSmartPointer<vtkStructuredGrid>::New();

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  double x, y, z;

  x = 0.0;
  y = 0.0;
  z = 0.0;

  for(unsigned int k = 0; k < 2; k++)
  {
    z += 2.0;
    for(unsigned int j = 0; j < 3; j++)
    {
      y += 1.0;
      for(unsigned int i = 0; i < 2; i++)
      {
        x += .5;
        points->InsertNextPoint(x, y, z);
      }
    }
  }

  // Specify the dimensions of the grid
  structuredGrid->SetDimensions(2,3,2);
  structuredGrid->SetPoints(points);

  int* dims = structuredGrid->GetDimensions();

  // Retrieve the entries from the grid and print them to the screen
  unsigned int counter = 0;

  for (int k = 0; k < dims[2]; k++)
  {
    for (int j = 0; j < dims[1]; j++)
    {
      for (int i = 0; i < dims[0]; i++)
      {
        double p[3];
        structuredGrid->GetPoint(counter, p);

        double pNew[3];
        structuredGrid->GetPoint(i, j, k, pNew);

        std::cout << "P   : "
                  << p[0] << " "
                  << p[1] << " "
                  << p[2] << std::endl;
        std::cout << "PNew: "
                  << pNew[0] << " "
                  << pNew[1] << " "
                  << pNew[2] << std::endl;

        counter++;
      }
    }
  }

  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInputConnection(structuredGrid->GetProducerPort());
#else
  mapper->SetInputData(structuredGrid);
#endif

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

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
  renderer->AddActor(actor);
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
 
PROJECT(StructuredGrid)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(StructuredGrid MACOSX_BUNDLE StructuredGrid.cxx)
 
target_link_libraries(StructuredGrid ${VTK_LIBRARIES})
```

**Download and Build StructuredGrid**

Click [here to download StructuredGrid](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/StructuredGrid.tar) and its *CMakeLists.txt* file.
Once the *tarball StructuredGrid.tar* has been downloaded and extracted,
```
cd StructuredGrid/build 
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
./StructuredGrid
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

