[VTKExamples](/index/)/[Cxx](/Cxx)/IO/SimplePointsReader

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestSimplePointsReader.png?raw=true" width="256" />

### Description
A file of XYZ coordinates is a very easy format that can be used for
simple storage from many applications. This example demonstrates how
to read this type of file into a polydata object. An example file of
three points would look like this:

`
 0.0 0.0 0.0
 1.0 0.0 0.0
 0.0 1.0 0.0
`

As a demo, save the above three lines to a file called simple.xyz and
call the executable resulting from the code below with

`
 ./SimplePointsReader simple.xyz
`

from the build directory.

**Note:** For the reverse operation, writing a points file, see the [SimplePointsWriter](Cxx/IO/SimplePointsWriter) example.

**SimplePointsReader.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSimplePointsReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main(int argc, char* argv[])
{
  // Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.xyz)" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the file
  vtkSmartPointer<vtkSimplePointsReader> reader =
    vtkSmartPointer<vtkSimplePointsReader>::New();
  reader->SetFileName ( argv[1] );
  reader->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(4);

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
 
PROJECT(SimplePointsReader)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SimplePointsReader MACOSX_BUNDLE SimplePointsReader.cxx)
 
target_link_libraries(SimplePointsReader ${VTK_LIBRARIES})
```

**Download and Build SimplePointsReader**

Click [here to download SimplePointsReader](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SimplePointsReader.tar) and its *CMakeLists.txt* file.
Once the *tarball SimplePointsReader.tar* has been downloaded and extracted,
```
cd SimplePointsReader/build 
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
./SimplePointsReader
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

