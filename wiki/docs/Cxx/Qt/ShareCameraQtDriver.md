[VTKExamples](/index/)/[Cxx](/Cxx)/Qt/ShareCameraQtDriver

**ShareCameraQtDriver.cxx**
```c++
#include <QApplication>
#include "ShareCameraQt.h"

int main( int argc, char** argv )
{
  // QT Stuff
  QApplication app( argc, argv );
  
  ShareCameraQt shareCameraQt;
  shareCameraQt.show();
  
  return app.exec();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ShareCameraQtDriver)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ShareCameraQtDriver MACOSX_BUNDLE ShareCameraQtDriver.cxx)
 
target_link_libraries(ShareCameraQtDriver ${VTK_LIBRARIES})
```

**Download and Build ShareCameraQtDriver**

Click [here to download ShareCameraQtDriver](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ShareCameraQtDriver.tar) and its *CMakeLists.txt* file.
Once the *tarball ShareCameraQtDriver.tar* has been downloaded and extracted,
```
cd ShareCameraQtDriver/build 
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
./ShareCameraQtDriver
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

