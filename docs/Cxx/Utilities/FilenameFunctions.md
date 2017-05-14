[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/FilenameFunctions

### Description
This example gets a list of all files in a directory. It then extracts the file extension and filename from each string.

**FilenameFunctions.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkDirectory.h>
#include <vtksys/SystemTools.hxx>
#include <string>

int main(int argc, char *argv[])
{
  std::string directoryName;
  if(argc < 2)
  {
    directoryName = std::string(".");    
  }
  else
  {
    directoryName = std::string(argv[1]);    
  }

  vtkSmartPointer<vtkDirectory> directory = vtkSmartPointer<vtkDirectory>::New();
  int opened = directory->Open(directoryName.c_str());

  if(!opened)
  {
    std::cout << "Invalid directory!" << std::endl;
    return EXIT_FAILURE;
  }

  int numberOfFiles = directory->GetNumberOfFiles();
  std::cout << "Number of files: " << numberOfFiles << std::endl;

  for (int i = 0; i < numberOfFiles; i++)
  {
    std::string fileString = directoryName;
    fileString += "/";
    fileString += directory->GetFile(i);

    std::string ext = vtksys::SystemTools::GetFilenameLastExtension(fileString);
    std::cout << fileString << " extension: " << ext << std::endl;

    std::string name = vtksys::SystemTools::GetFilenameWithoutLastExtension(fileString);    
    std::cout << "name: " << name << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(FilenameFunctions)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FilenameFunctions MACOSX_BUNDLE FilenameFunctions.cxx)
 
target_link_libraries(FilenameFunctions ${VTK_LIBRARIES})
```

**Download and Build FilenameFunctions**

Click [here to download FilenameFunctions](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/FilenameFunctions.tar) and its *CMakeLists.txt* file.
Once the *tarball FilenameFunctions.tar* has been downloaded and extracted,
```
cd FilenameFunctions/build 
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
./FilenameFunctions
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

