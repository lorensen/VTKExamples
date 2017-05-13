[VTKExamples](Home)/[Cxx](Cxx)/Qt/QImageToImageSource

### Description
This example demonstrates the use of vtkQImageToImageSource.

See also the [ImageDataToQImage](Cxx/Qt/ImageDataToQImage) example.

**QImageToImageSource.cxx**
```c++
#include <QApplication>
#include <QPixmap>

#include "vtkSmartPointer.h"
#include "vtkQImageToImageSource.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  
  QPixmap pixmap(10,10);
  QColor color(10,20,30);
  pixmap.fill(color);
  
  vtkSmartPointer<vtkQImageToImageSource> qimageToImageSource =
    vtkSmartPointer<vtkQImageToImageSource>::New();
  QImage qimage = pixmap.toImage();
  qimageToImageSource->SetQImage(&qimage);
  qimageToImageSource->Update();

//  vtkImageData* image = qimageToImageSource->GetOutput();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(QImageToImageSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(QImageToImageSource MACOSX_BUNDLE QImageToImageSource.cxx)
 
target_link_libraries(QImageToImageSource ${VTK_LIBRARIES})
```

**Download and Build QImageToImageSource**

Click [here to download QImageToImageSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/QImageToImageSource.tar) and its *CMakeLists.txt* file.
Once the *tarball QImageToImageSource.tar* has been downloaded and extracted,
```
cd QImageToImageSource/build 
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
./QImageToImageSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

