[VTKExamples](Home)/[Cxx](Cxx)/Graphs/RandomGraphSource

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Graphs/TestRandomGraphSource.png" width="256" />

**RandomGraphSource.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkGraphLayoutView.h>
#include <vtkGraphWriter.h>
#include <vtkRandomGraphSource.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkRandomGraphSource> randomGraphSource = 
    vtkSmartPointer<vtkRandomGraphSource>::New();
  randomGraphSource->SetNumberOfVertices(5);
  randomGraphSource->SetNumberOfEdges(4);
  randomGraphSource->SetSeed(0); // This ensures repeatable results for testing. Turn this off for real use.
  randomGraphSource->Update();
  
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(
    randomGraphSource->GetOutput());
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();
     
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RandomGraphSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RandomGraphSource MACOSX_BUNDLE RandomGraphSource.cxx)
 
target_link_libraries(RandomGraphSource ${VTK_LIBRARIES})
```

**Download and Build RandomGraphSource**

Click [here to download RandomGraphSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RandomGraphSource.tar) and its *CMakeLists.txt* file.
Once the *tarball RandomGraphSource.tar* has been downloaded and extracted,
```
cd RandomGraphSource/build 
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
./RandomGraphSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

