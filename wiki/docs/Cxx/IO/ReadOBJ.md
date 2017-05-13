[VTKExamples](/index/)/[Cxx](/Cxx)/IO/ReadOBJ

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestReadOBJ.png?raw=true" width="256" />

### Description
This example demonstrates how to read a [.obj file|Wavefront OBJ]]([wikipedia:Wavefront) file. The result is displayed.

**ReadOBJ.cxx**
```c++
#include <vtkOBJReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <string>

int main(int argc, char* argv[])
{
  // Parse command line arguments
  if(argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " Filename(.obj)" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];
  vtkSmartPointer<vtkOBJReader> reader =
    vtkSmartPointer<vtkOBJReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ReadOBJ)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadOBJ MACOSX_BUNDLE ReadOBJ.cxx)
 
target_link_libraries(ReadOBJ ${VTK_LIBRARIES})
```

**Download and Build ReadOBJ**

Click [here to download ReadOBJ](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ReadOBJ.tar) and its *CMakeLists.txt* file.
Once the *tarball ReadOBJ.tar* has been downloaded and extracted,
```
cd ReadOBJ/build 
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
./ReadOBJ
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

