[VTKExamples](Home)/[Cxx](Cxx)/PolyData/DataBounds

### Description
This examples gets the bounds of a dataset. Note that Update() must be applied to create the output of the filter.

**DataBounds.cxx**
```c++
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();

  if (argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName ( argv[1] );
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> modelSource =
      vtkSmartPointer<vtkSphereSource>::New();
    modelSource->Update();
    polyData = modelSource->GetOutput();
  }

  double bounds[6];
  polyData->GetBounds(bounds);

  std::cout  << "xmin: " << bounds[0] << " "
             << "xmax: " << bounds[1] << std::endl
             << "ymin: " << bounds[2] << " "
             << "ymax: " << bounds[3] << std::endl
             << "zmin: " << bounds[4] << " "
             << "zmax: " << bounds[5] << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DataBounds)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DataBounds MACOSX_BUNDLE DataBounds.cxx)
 
target_link_libraries(DataBounds ${VTK_LIBRARIES})
```

**Download and Build DataBounds**

Click [here to download DataBounds](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DataBounds.tar) and its *CMakeLists.txt* file.
Once the *tarball DataBounds.tar* has been downloaded and extracted,
```
cd DataBounds/build 
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
./DataBounds
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

