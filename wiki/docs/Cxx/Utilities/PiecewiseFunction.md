[VTKExamples](Home)/[Cxx](Cxx)/Utilities/PiecewiseFunction

**PiecewiseFunction.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPiecewiseFunction.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPiecewiseFunction> piecewiseFunction = 
      vtkSmartPointer<vtkPiecewiseFunction>::New();
  piecewiseFunction->AddPoint(0.0, 0.0);
  piecewiseFunction->AddPoint(1.0, 2.0);
  
  double test = piecewiseFunction->GetValue(0.25);

  std::cout << "test: " << test << " (should be 0.5)" << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PiecewiseFunction)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PiecewiseFunction MACOSX_BUNDLE PiecewiseFunction.cxx)
 
target_link_libraries(PiecewiseFunction ${VTK_LIBRARIES})
```

**Download and Build PiecewiseFunction**

Click [here to download PiecewiseFunction](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PiecewiseFunction.tar) and its *CMakeLists.txt* file.
Once the *tarball PiecewiseFunction.tar* has been downloaded and extracted,
```
cd PiecewiseFunction/build 
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
./PiecewiseFunction
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

