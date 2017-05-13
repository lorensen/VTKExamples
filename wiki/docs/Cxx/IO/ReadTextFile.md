[VTKExamples](Home)/[Cxx](Cxx)/IO/ReadTextFile

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/IO/TestReadTextFile.png" width="256" />

### Description
This example takes a plain text file of coordinates and reads them into a vtkPoints, which is then put into a vtkPolyData and displayed on the screen using a vtkVertexGlyphFilter.

An example file may look like:
 1 2 3
 4 5 6 
 7 8 9

**Note:** for a simpler way to read such a file, see [SimplePointsReader](Cxx/IO/SimplePointsReader).

**ReadTextFile.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <sstream>

int main(int argc, char* argv[])
{
  // Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.xyz)" << std::endl;
    return EXIT_FAILURE;
  }
  // Get all data from the file
  std::string filename = argv[1];
  std::ifstream filestream(filename.c_str());

  std::string line;
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  while(std::getline(filestream, line))
  {
    double x, y, z;
    std::stringstream linestream;
    linestream << line;
    linestream >> x >> y >> z;

    points->InsertNextPoint(x, y, z);
  }

  filestream.close();

  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();

  polyData->SetPoints(points);

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  glyphFilter->SetInputConnection(polyData->GetProducerPort());
#else
  glyphFilter->SetInputData(polyData);
#endif
  glyphFilter->Update();

  // Visualize

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyphFilter->GetOutputPort());

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
 
PROJECT(ReadTextFile)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadTextFile MACOSX_BUNDLE ReadTextFile.cxx)
 
target_link_libraries(ReadTextFile ${VTK_LIBRARIES})
```

**Download and Build ReadTextFile**

Click [here to download ReadTextFile](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ReadTextFile.tar) and its *CMakeLists.txt* file.
Once the *tarball ReadTextFile.tar* has been downloaded and extracted,
```
cd ReadTextFile/build 
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
./ReadTextFile
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

