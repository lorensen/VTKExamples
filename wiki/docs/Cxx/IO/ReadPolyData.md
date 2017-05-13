[VTKExamples](Home)/[Cxx](Cxx)/IO/ReadPolyData

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/IO/TestReadPolyData.png" width="256" />

### Description
This example reads a polygonal data (.vtp) file.
An example data set can be found at VTKData/Data/SyntheticPolyline.vtp

**ReadPolyData.cxx**
```c++
#include <vtkXMLPolyDataReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main ( int argc, char *argv[] )
{
  // Parse command line arguments
  if(argc != 2)
  {
    std::cerr << "Usage: " << argv[0]
              << " Filename(.vtp)" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];

  // Read all the data from the file
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
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
 
PROJECT(ReadPolyData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadPolyData MACOSX_BUNDLE ReadPolyData.cxx)
 
target_link_libraries(ReadPolyData ${VTK_LIBRARIES})
```

**Download and Build ReadPolyData**

Click [here to download ReadPolyData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ReadPolyData.tar) and its *CMakeLists.txt* file.
Once the *tarball ReadPolyData.tar* has been downloaded and extracted,
```
cd ReadPolyData/build 
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
./ReadPolyData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

