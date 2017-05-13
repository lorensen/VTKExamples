[VTKExamples](Home)/[Cxx](Cxx)/IO/WriteSTL

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/IO/TestWriteSTL.png" width="256" />

### Description
An [(file format)|STL file]]([wikipedia:STL) describes a triangulated three-dimensional surface by the unit normal and vertices (ordered by the right-hand rule) of the triangles. This example saves a 3D geometric data stored in a {{class|vtkPolyData}} to an STL file using {{class|vtkSTLWriter}}.

**WriteSTL.cxx**
```c++
#include <vtkPolyData.h>
#include <vtkSTLWriter.h>
#include <vtkSTLReader.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cout << "Required parameters: filename.stl" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];

  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkSTLWriter> stlWriter =
    vtkSmartPointer<vtkSTLWriter>::New();
  stlWriter->SetFileName(filename.c_str());
  stlWriter->SetInputConnection(sphereSource->GetOutputPort());
  stlWriter->Write();

  // Read and display for verification
  vtkSmartPointer<vtkSTLReader> reader =
    vtkSmartPointer<vtkSTLReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

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
 
PROJECT(WriteSTL)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(WriteSTL MACOSX_BUNDLE WriteSTL.cxx)
 
target_link_libraries(WriteSTL ${VTK_LIBRARIES})
```

**Download and Build WriteSTL**

Click [here to download WriteSTL](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/WriteSTL.tar) and its *CMakeLists.txt* file.
Once the *tarball WriteSTL.tar* has been downloaded and extracted,
```
cd WriteSTL/build 
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
./WriteSTL
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

