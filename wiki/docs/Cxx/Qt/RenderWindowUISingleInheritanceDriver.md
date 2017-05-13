[VTKExamples](Home)/[Cxx](Cxx)/Qt/RenderWindowUISingleInheritanceDriver

### Description

Using a QVTKWidget with the Qt Single Inheritance model

**RenderWindowUISingleInheritanceDriver.cxx**
```c++
#include <QApplication>
#include "RenderWindowUISingleInheritance.h"
 
int main( int argc, char** argv )
{
  // QT Stuff
  QApplication app( argc, argv );
 
  RenderWindowUISingleInheritance renderWindowUISingleInheritance;
  renderWindowUISingleInheritance.show();
 
  return app.exec();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RenderWindowUISingleInheritanceDriver)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RenderWindowUISingleInheritanceDriver MACOSX_BUNDLE RenderWindowUISingleInheritanceDriver.cxx)
 
target_link_libraries(RenderWindowUISingleInheritanceDriver ${VTK_LIBRARIES})
```

**Download and Build RenderWindowUISingleInheritanceDriver**

Click [here to download RenderWindowUISingleInheritanceDriver](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RenderWindowUISingleInheritanceDriver.tar) and its *CMakeLists.txt* file.
Once the *tarball RenderWindowUISingleInheritanceDriver.tar* has been downloaded and extracted,
```
cd RenderWindowUISingleInheritanceDriver/build 
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
./RenderWindowUISingleInheritanceDriver
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

