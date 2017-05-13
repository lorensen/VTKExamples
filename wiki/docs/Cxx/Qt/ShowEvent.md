[VTKExamples](Home)/[Cxx](Cxx)/Qt/ShowEvent

**ShowEvent.cxx**
```c++
#include <iostream>

#include "ShowEvent.h"

ShowEvent::ShowEvent(QWidget *myParent) : QWidget(myParent)
{
  this->setupUi(this);

  // Do not do anything related to VTK display here!
}

void ShowEvent::showEvent(QShowEvent *)
{
  // Instead, do the VTK display things here!
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ShowEvent)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ShowEvent MACOSX_BUNDLE ShowEvent.cxx)
 
target_link_libraries(ShowEvent ${VTK_LIBRARIES})
```

**Download and Build ShowEvent**

Click [here to download ShowEvent](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ShowEvent.tar) and its *CMakeLists.txt* file.
Once the *tarball ShowEvent.tar* has been downloaded and extracted,
```
cd ShowEvent/build 
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
./ShowEvent
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

