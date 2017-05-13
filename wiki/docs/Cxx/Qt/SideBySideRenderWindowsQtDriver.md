[VTKExamples](Home)/[Cxx](Cxx)/Qt/SideBySideRenderWindowsQtDriver

### Description

Although this example includes ui_SideBySideRenderWindowsQt.h, this file is not distributed, it is created by Qt at compile time.

**SideBySideRenderWindowsQtDriver.cxx**
```c++
#include <QApplication>
#include "SideBySideRenderWindowsQt.h"

int main( int argc, char** argv )
{
  // QT Stuff
  QApplication app( argc, argv );
  
  SideBySideRenderWindowsQt sideBySideRenderWindowsQt;
  sideBySideRenderWindowsQt.show();
  
  return app.exec();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SideBySideRenderWindowsQtDriver)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SideBySideRenderWindowsQtDriver MACOSX_BUNDLE SideBySideRenderWindowsQtDriver.cxx)
 
target_link_libraries(SideBySideRenderWindowsQtDriver ${VTK_LIBRARIES})
```

**Download and Build SideBySideRenderWindowsQtDriver**

Click [here to download SideBySideRenderWindowsQtDriver](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SideBySideRenderWindowsQtDriver.tar) and its *CMakeLists.txt* file.
Once the *tarball SideBySideRenderWindowsQtDriver.tar* has been downloaded and extracted,
```
cd SideBySideRenderWindowsQtDriver/build 
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
./SideBySideRenderWindowsQtDriver
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

