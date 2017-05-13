[VTKExamples](Home)/[Cxx](Cxx)/IO/ReadRectilinearGrid

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/IO/TestReadRectilinearGrid.png" width="256" />

### Description
This example reads a rectilinear grid (.vtr) file. An example file can be found at VTKData/Data/cth.vtr

**ReadRectilinearGrid.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkXMLRectilinearGridReader.h>
#include <vtkRectilinearGridGeometryFilter.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  // Verify input arguments
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0]
              << " Filename.vtr" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse arguments
  std::string inputFilename = argv[1];

  // Read the file
  vtkSmartPointer<vtkXMLRectilinearGridReader> reader =
    vtkSmartPointer<vtkXMLRectilinearGridReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();
/*
  vtkSmartPointer<vtkRectilinearGridGeometryFilter> geometryFilter =
    vtkSmartPointer<vtkRectilinearGridGeometryFilter>::New();
  geometryFilter->SetInputConnection(reader->GetOutputPort());
  geometryFilter->Update();
*/
  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  //mapper->SetInputConnection(geometryFilter->GetOutputPort());
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetRepresentationToWireframe();

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
 
PROJECT(ReadRectilinearGrid)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadRectilinearGrid MACOSX_BUNDLE ReadRectilinearGrid.cxx)
 
target_link_libraries(ReadRectilinearGrid ${VTK_LIBRARIES})
```

**Download and Build ReadRectilinearGrid**

Click [here to download ReadRectilinearGrid](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ReadRectilinearGrid.tar) and its *CMakeLists.txt* file.
Once the *tarball ReadRectilinearGrid.tar* has been downloaded and extracted,
```
cd ReadRectilinearGrid/build 
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
./ReadRectilinearGrid
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

