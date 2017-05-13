[VTKExamples](/index/)/[Cxx](/Cxx)/IO/ReadUnstructuredGrid

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestReadUnstructuredGrid.png?raw=true" width="256" />

### Description
This examples demonstrates how to read an unstructured grid (VTU) file. 

An example data file (.vtu) for testing can be found in VTKData/Data/quadraticTetra01.vtu.

**ReadUnstructuredGrid.cxx**
```c++
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main ( int argc, char *argv[] )
{
  //parse command line arguments
  if(argc != 2)
  {
    std::cerr << "Usage: " << argv[0]
              << " Filename(.vtu)" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];

  //read all the data from the file
  vtkSmartPointer<vtkXMLUnstructuredGridReader> reader =
    vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  //Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ReadUnstructuredGrid)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadUnstructuredGrid MACOSX_BUNDLE ReadUnstructuredGrid.cxx)
 
target_link_libraries(ReadUnstructuredGrid ${VTK_LIBRARIES})
```

**Download and Build ReadUnstructuredGrid**

Click [here to download ReadUnstructuredGrid](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ReadUnstructuredGrid.tar) and its *CMakeLists.txt* file.
Once the *tarball ReadUnstructuredGrid.tar* has been downloaded and extracted,
```
cd ReadUnstructuredGrid/build 
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
./ReadUnstructuredGrid
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

