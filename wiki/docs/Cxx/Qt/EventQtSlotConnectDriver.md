[VTKExamples](Home)/[Cxx](Cxx)/Qt/EventQtSlotConnectDriver

**EventQtSlotConnectDriver.cxx**
```c++
#include <QApplication>
#include "EventQtSlotConnect.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  EventQtSlotConnect eventQtSlotConnect;
  eventQtSlotConnect.show();

  return app.exec();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(EventQtSlotConnectDriver)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(EventQtSlotConnectDriver MACOSX_BUNDLE EventQtSlotConnectDriver.cxx)
 
target_link_libraries(EventQtSlotConnectDriver ${VTK_LIBRARIES})
```

**Download and Build EventQtSlotConnectDriver**

Click [here to download EventQtSlotConnectDriver](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/EventQtSlotConnectDriver.tar) and its *CMakeLists.txt* file.
Once the *tarball EventQtSlotConnectDriver.tar* has been downloaded and extracted,
```
cd EventQtSlotConnectDriver/build 
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
./EventQtSlotConnectDriver
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

