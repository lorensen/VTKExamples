[VTKExamples](/home/)/[Cxx](/Cxx)/IO/ReadSTL

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestReadSTL.png?raw=true" width="256" />

**ReadSTL.cxx**
```c++
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main ( int argc, char *argv[] )
{
  if ( argc != 2 )
  {
    cout << "Required parameters: Filename" << endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  vtkSmartPointer<vtkSTLReader> reader =
    vtkSmartPointer<vtkSTLReader>::New();
  reader->SetFileName(inputFilename.c_str());
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
 
PROJECT(ReadSTL)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadSTL MACOSX_BUNDLE ReadSTL.cxx)
 
target_link_libraries(ReadSTL ${VTK_LIBRARIES})
```

**Download and Build ReadSTL**

Click [here to download ReadSTL](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ReadSTL.tar) and its *CMakeLists.txt* file.
Once the *tarball ReadSTL.tar* has been downloaded and extracted,
```
cd ReadSTL/build 
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
./ReadSTL
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

