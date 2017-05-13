[VTKExamples](/home/)/[Cxx](/Cxx)/IO/StructuredPointsReader

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestStructuredPointsReader.png?raw=true" width="256" />

### Description
An example input file can be found at <VTKData>/Data/ironProt.vtk.

**StructuredPointsReader.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkStructuredPointsReader.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  // Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.jpeg)" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  // Read the file
  vtkSmartPointer<vtkStructuredPointsReader> reader =
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  vtkSmartPointer<vtkImageDataGeometryFilter> geometryFilter =
    vtkSmartPointer<vtkImageDataGeometryFilter>::New();
  geometryFilter->SetInputConnection(reader->GetOutputPort());
  geometryFilter->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(geometryFilter->GetOutputPort());

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
 
PROJECT(StructuredPointsReader)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(StructuredPointsReader MACOSX_BUNDLE StructuredPointsReader.cxx)
 
target_link_libraries(StructuredPointsReader ${VTK_LIBRARIES})
```

**Download and Build StructuredPointsReader**

Click [here to download StructuredPointsReader](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/StructuredPointsReader.tar) and its *CMakeLists.txt* file.
Once the *tarball StructuredPointsReader.tar* has been downloaded and extracted,
```
cd StructuredPointsReader/build 
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
./StructuredPointsReader
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

