[VTKExamples](/home/)/[Cxx](/Cxx)/IO/ConvertFile

### Description
This example demonstrates how to read a file and then write it to a different type of file. In this example, we read a vtp file and write a ply file, but simply by changing the reader/writer classes instantiated, different behavior can be achieved.

**ConvertFile.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPLYWriter.h>
	
int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    std::cerr << "Required arguments: input.vtp output.ply" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFileName = argv[1];
  std::string outputFileName = argv[2];

  vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(inputFileName.c_str());
  reader->Update();

  vtkSmartPointer<vtkPLYWriter> writer = vtkSmartPointer<vtkPLYWriter>::New();
  writer->SetFileName(outputFileName.c_str());
  writer->SetInputConnection(reader->GetOutputPort());
  writer->Update();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ConvertFile)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ConvertFile MACOSX_BUNDLE ConvertFile.cxx)
 
target_link_libraries(ConvertFile ${VTK_LIBRARIES})
```

**Download and Build ConvertFile**

Click [here to download ConvertFile](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ConvertFile.tar) and its *CMakeLists.txt* file.
Once the *tarball ConvertFile.tar* has been downloaded and extracted,
```
cd ConvertFile/build 
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
./ConvertFile
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

