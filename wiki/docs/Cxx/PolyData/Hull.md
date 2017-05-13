[VTKExamples](Home)/[Cxx](Cxx)/PolyData/Hull

**Hull.cxx**
```c++
#include <vtkPoints.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkSmartPointer.h>
#include <vtkHull.h>

int main(int argc, char *argv[])
{
  // Parse command line arguments
  if(argc != 2)
  {
    std::cout << "Required arguments: Filename" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  vtkSmartPointer<vtkHull> hullFilter =
    vtkSmartPointer<vtkHull>::New();
  hullFilter->SetInputConnection(reader->GetOutputPort());
  hullFilter->AddCubeFacePlanes ();
  hullFilter->Update();

  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(hullFilter->GetOutputPort());
  writer->SetFileName("hull.vtp");
  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Hull)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Hull MACOSX_BUNDLE Hull.cxx)
 
target_link_libraries(Hull ${VTK_LIBRARIES})
```

**Download and Build Hull**

Click [here to download Hull](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Hull.tar) and its *CMakeLists.txt* file.
Once the *tarball Hull.tar* has been downloaded and extracted,
```
cd Hull/build 
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
./Hull
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

