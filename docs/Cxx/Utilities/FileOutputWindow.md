[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/FileOutputWindow

### Description
This example shows how to pipe error output to a text file instead of the usual vtk pop-up window.

**FileOutputWindow.cxx**
```c++
#include <vtkFileOutputWindow.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkFileOutputWindow> fileOutputWindow = 
      vtkSmartPointer<vtkFileOutputWindow>::New();
  fileOutputWindow->SetFileName( "output.txt" );

  // Note that the SetInstance function is a static member of vtkOutputWindow.
  vtkOutputWindow::SetInstance(fileOutputWindow);

  // This causes an error intentionally (file name not specified) - this error will be written to the file output.txt
  vtkSmartPointer<vtkXMLPolyDataReader> reader = 
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->Update();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(FileOutputWindow)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FileOutputWindow MACOSX_BUNDLE FileOutputWindow.cxx)
 
target_link_libraries(FileOutputWindow ${VTK_LIBRARIES})
```

**Download and Build FileOutputWindow**

Click [here to download FileOutputWindow](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/FileOutputWindow.tar) and its *CMakeLists.txt* file.
Once the *tarball FileOutputWindow.tar* has been downloaded and extracted,
```
cd FileOutputWindow/build 
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
./FileOutputWindow
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

