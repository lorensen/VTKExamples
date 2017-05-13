[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/Coordinate

### Description
There are many possible coordinate conversions. This example demonstrates NormalizedDisplay->Display.

**Coordinate.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCoordinate.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkRenderWindow> rendererWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  rendererWindow->AddRenderer(renderer);
  rendererWindow->Render();
  
  vtkSmartPointer<vtkCoordinate> coordinate = 
    vtkSmartPointer<vtkCoordinate>::New();
  coordinate->SetCoordinateSystemToNormalizedDisplay();
  coordinate->SetValue(.5,.5,0);
  std::cout << *coordinate << std::endl;
  std::cout << coordinate->GetCoordinateSystemAsString() << std::endl;
  
  int* val;
  val = coordinate->GetComputedDisplayValue(renderer);
  std::cout << "Val: " << val[0] << " " << val[1] << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Coordinate)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Coordinate MACOSX_BUNDLE Coordinate.cxx)
 
target_link_libraries(Coordinate ${VTK_LIBRARIES})
```

**Download and Build Coordinate**

Click [here to download Coordinate](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Coordinate.tar) and its *CMakeLists.txt* file.
Once the *tarball Coordinate.tar* has been downloaded and extracted,
```
cd Coordinate/build 
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
./Coordinate
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

