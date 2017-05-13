[VTKExamples](/home/)/[Cxx](/Cxx)/InfoVis/XGMLReader

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/InfoVis/TestXGMLReader.png?raw=true" width="256" />

### Description
This example reads and displays the graph from a gml file. You can test this with VTKData/Data/Infovis/fsm.gml.

**XGMLReader.cxx**
```c++
#include <vtkPolyData.h>
#include <vtkXGMLReader.h>
#include <vtkSmartPointer.h>
#include <vtkUndirectedGraph.h>
#include <vtkGraphLayoutStrategy.h>
#include <vtkGraphLayoutView.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSimple2DLayoutStrategy.h>

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cout << "Required parameters: Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  vtkSmartPointer<vtkXGMLReader> reader =
    vtkSmartPointer<vtkXGMLReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  vtkUndirectedGraph* g = reader->GetOutput();

  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(g);
  graphLayoutView->SetLayoutStrategy("Simple 2D");
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();

  graphLayoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(XGMLReader)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(XGMLReader MACOSX_BUNDLE XGMLReader.cxx)
 
target_link_libraries(XGMLReader ${VTK_LIBRARIES})
```

**Download and Build XGMLReader**

Click [here to download XGMLReader](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/XGMLReader.tar) and its *CMakeLists.txt* file.
Once the *tarball XGMLReader.tar* has been downloaded and extracted,
```
cd XGMLReader/build 
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
./XGMLReader
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

