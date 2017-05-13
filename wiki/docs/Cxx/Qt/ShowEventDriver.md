[VTKExamples](/home/)/[Cxx](/Cxx)/Qt/ShowEventDriver

### Description

Small example (not doing anything actually) to show the use of the overwritten QWidget::showEvent() function to initialize the VTK widget when it is actually used, not directly in the constructor.

**ShowEventDriver.cxx**
```c++
#include <QApplication>

#include "ShowEvent.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  ShowEvent showEvent;

  showEvent.show();
  return app.exec();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ShowEventDriver)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ShowEventDriver MACOSX_BUNDLE ShowEventDriver.cxx)
 
target_link_libraries(ShowEventDriver ${VTK_LIBRARIES})
```

**Download and Build ShowEventDriver**

Click [here to download ShowEventDriver](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ShowEventDriver.tar) and its *CMakeLists.txt* file.
Once the *tarball ShowEventDriver.tar* has been downloaded and extracted,
```
cd ShowEventDriver/build 
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
./ShowEventDriver
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

