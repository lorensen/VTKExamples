[VTKExamples](/index/)/[Cxx](/Cxx)/Qt/BorderWidgetQtDriver

**BorderWidgetQtDriver.cxx**
```c++
#include <QApplication>
#include "BorderWidgetQt.h"

int main(int argc, char* argv[])
{
  QApplication app( argc, argv );

  BorderWidgetQt borderWidgetQt;
  borderWidgetQt.show();

  return app.exec();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BorderWidgetQtDriver)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BorderWidgetQtDriver MACOSX_BUNDLE BorderWidgetQtDriver.cxx)
 
target_link_libraries(BorderWidgetQtDriver ${VTK_LIBRARIES})
```

**Download and Build BorderWidgetQtDriver**

Click [here to download BorderWidgetQtDriver](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BorderWidgetQtDriver.tar) and its *CMakeLists.txt* file.
Once the *tarball BorderWidgetQtDriver.tar* has been downloaded and extracted,
```
cd BorderWidgetQtDriver/build 
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
./BorderWidgetQtDriver
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

