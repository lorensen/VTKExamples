[VTKExamples](/index/)/[Cxx](/Cxx)/IO/GenericDataObjectReader

**GenericDataObjectReader.cxx**
```c++
#include <vtkGenericDataObjectReader.h>
#include <vtkStructuredGrid.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <string>

int main ( int argc, char *argv[] )
{
  // Ensure a filename was specified
  if(argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " InputFilename" << endl;
    return EXIT_FAILURE;
  }

  // Get the filename from the command line
  std::string inputFilename = argv[1];

  // Get all data from the file
  vtkSmartPointer<vtkGenericDataObjectReader> reader =
      vtkSmartPointer<vtkGenericDataObjectReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  // All of the standard data types can be checked and obtained like this:
  if(reader->IsFilePolyData())
  {
    std::cout << "output is a polydata" << std::endl;
    vtkPolyData* output = reader->GetPolyDataOutput();
    std::cout << "output has " << output->GetNumberOfPoints() << " points." << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GenericDataObjectReader)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GenericDataObjectReader MACOSX_BUNDLE GenericDataObjectReader.cxx)
 
target_link_libraries(GenericDataObjectReader ${VTK_LIBRARIES})
```

**Download and Build GenericDataObjectReader**

Click [here to download GenericDataObjectReader](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GenericDataObjectReader.tar) and its *CMakeLists.txt* file.
Once the *tarball GenericDataObjectReader.tar* has been downloaded and extracted,
```
cd GenericDataObjectReader/build 
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
./GenericDataObjectReader
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

