[VTKExamples](/home/)/[Cxx](/Cxx)/Parallel/ExodusIIWriter

### Description
Requires VTK to be built with VTK_USE_PARALLEL.

**ExodusIIWriter.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkExodusIIWriter.h>
#include <vtkTimeSourceExample.h>
 
int main(int, char *[])
{
             
  vtkSmartPointer<vtkTimeSourceExample> timeSource = 
    vtkSmartPointer<vtkTimeSourceExample>::New();
               
  vtkSmartPointer<vtkExodusIIWriter> exodusWriter = 
    vtkSmartPointer<vtkExodusIIWriter>::New();
  exodusWriter->SetFileName("output.exii");
  exodusWriter->SetInputConnection (timeSource->GetOutputPort());
  exodusWriter->WriteAllTimeStepsOn ();
  exodusWriter->Write();
                       
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExodusIIWriter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExodusIIWriter MACOSX_BUNDLE ExodusIIWriter.cxx)
 
target_link_libraries(ExodusIIWriter ${VTK_LIBRARIES})
```

**Download and Build ExodusIIWriter**

Click [here to download ExodusIIWriter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ExodusIIWriter.tar) and its *CMakeLists.txt* file.
Once the *tarball ExodusIIWriter.tar* has been downloaded and extracted,
```
cd ExodusIIWriter/build 
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
./ExodusIIWriter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

