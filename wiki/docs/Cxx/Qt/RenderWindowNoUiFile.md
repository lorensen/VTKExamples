[VTKExamples](/home/)/[Cxx](/Cxx)/Qt/RenderWindowNoUiFile

### Description

This is a very basic example that shows how to create a Qt window. Typically, one would want to design a form in the QtDesigner (this is shown in RenderWindowUi)

**RenderWindowNoUiFile.cxx**
```c++
#include <QApplication>

#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

#include <QVTKWidget.h>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  QVTKWidget widget;
  widget.resize( 256, 256 );

  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();

  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection( sphereSource->GetOutputPort() );

  vtkSmartPointer<vtkActor> sphereActor =
      vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper( sphereMapper );

  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor( sphereActor );
 
  widget.GetRenderWindow()->AddRenderer( renderer );
  widget.show();

  app.exec();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RenderWindowNoUiFile)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RenderWindowNoUiFile MACOSX_BUNDLE RenderWindowNoUiFile.cxx)
 
target_link_libraries(RenderWindowNoUiFile ${VTK_LIBRARIES})
```

**Download and Build RenderWindowNoUiFile**

Click [here to download RenderWindowNoUiFile](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RenderWindowNoUiFile.tar) and its *CMakeLists.txt* file.
Once the *tarball RenderWindowNoUiFile.tar* has been downloaded and extracted,
```
cd RenderWindowNoUiFile/build 
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
./RenderWindowNoUiFile
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

