[VTKExamples](/index/)/[Cxx](/Cxx)/Qt/RenderWindowUIMultipleInheritanceDriver

### Description

Using a QVTKWidget with the Qt Multiple Inheritance model. In contrast to the single inheritance example the main widget is here derived from QMainWindow as well as the class defining the form (Ui::RenderWindowUIMultipleInheritance).

**RenderWindowUIMultipleInheritanceDriver.cxx**
```c++
#include <QApplication>
#include "RenderWindowUIMultipleInheritance.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  RenderWindowUIMultipleInheritance renderWindowUIMultipleInheritance;
  renderWindowUIMultipleInheritance.show();

  return app.exec();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RenderWindowUIMultipleInheritanceDriver)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RenderWindowUIMultipleInheritanceDriver MACOSX_BUNDLE RenderWindowUIMultipleInheritanceDriver.cxx)
 
target_link_libraries(RenderWindowUIMultipleInheritanceDriver ${VTK_LIBRARIES})
```

**Download and Build RenderWindowUIMultipleInheritanceDriver**

Click [here to download RenderWindowUIMultipleInheritanceDriver](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RenderWindowUIMultipleInheritanceDriver.tar) and its *CMakeLists.txt* file.
Once the *tarball RenderWindowUIMultipleInheritanceDriver.tar* has been downloaded and extracted,
```
cd RenderWindowUIMultipleInheritanceDriver/build 
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
./RenderWindowUIMultipleInheritanceDriver
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

