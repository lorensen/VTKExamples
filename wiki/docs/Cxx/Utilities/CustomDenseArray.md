[VTKExamples](/home/)/[Cxx](/Cxx)/Utilities/CustomDenseArray

### Description
The only thing you have to do to enable your class to work with vtkDenseArray is add a single line:   

<source lang="cpp">
operator vtkVariant() const { return vtkVariant(); }
</source>

**CustomDenseArray.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkDenseArray.h>

struct Point
{
  double x,y;
  
  operator vtkVariant() const { return vtkVariant(); }
};

int main(int, char *[])
{
  Point point;
  point.x = 1.0;
  point.y = 2.0;
  
  std::cout << point.x << " " << point.y << std::endl;
      
  vtkSmartPointer<vtkDenseArray<Point> > array = 
    vtkSmartPointer<vtkDenseArray<Point> >::New();
  array->Resize(5,5);
  
  array->SetValue(4,4, point);
  
  Point retrievedPoint = array->GetValue(4,4);
  std::cout << retrievedPoint.x << " " << retrievedPoint.y << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CustomDenseArray)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CustomDenseArray MACOSX_BUNDLE CustomDenseArray.cxx)
 
target_link_libraries(CustomDenseArray ${VTK_LIBRARIES})
```

**Download and Build CustomDenseArray**

Click [here to download CustomDenseArray](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CustomDenseArray.tar) and its *CMakeLists.txt* file.
Once the *tarball CustomDenseArray.tar* has been downloaded and extracted,
```
cd CustomDenseArray/build 
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
./CustomDenseArray
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

