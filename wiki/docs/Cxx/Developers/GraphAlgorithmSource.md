[VTKExamples](/index/)/[Cxx](/Cxx)/Developers/GraphAlgorithmSource

### Description
This example produces a vtkGraph as output.

**GraphAlgorithmSource.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkGraph.h>
#include <vtkMutableUndirectedGraph.h>

#include "vtkTestGraphAlgorithmSource.h"

int main (int, char *[])
{
  vtkSmartPointer<vtkTestGraphAlgorithmSource> source =
    vtkSmartPointer<vtkTestGraphAlgorithmSource>::New();
  source->Update();
  
  vtkGraph* outputGraph = source->GetOutput();
  
  std::cout << "Output number of vertices: "
            << outputGraph->GetNumberOfVertices() << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GraphAlgorithmSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GraphAlgorithmSource MACOSX_BUNDLE GraphAlgorithmSource.cxx)
 
target_link_libraries(GraphAlgorithmSource ${VTK_LIBRARIES})
```

**Download and Build GraphAlgorithmSource**

Click [here to download GraphAlgorithmSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GraphAlgorithmSource.tar) and its *CMakeLists.txt* file.
Once the *tarball GraphAlgorithmSource.tar* has been downloaded and extracted,
```
cd GraphAlgorithmSource/build 
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
./GraphAlgorithmSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

