[VTKExamples](Home)/[Cxx](Cxx)/Qt/SideBySideRenderWindowsQt

**SideBySideRenderWindowsQt.cxx**
```c++
#include "SideBySideRenderWindowsQt.h"

#include <vtkDataObjectToTable.h>
#include <vtkElevationFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkQtTableView.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkSmartPointer.h>

// Constructor
SideBySideRenderWindowsQt::SideBySideRenderWindowsQt() 
{
  this->setupUi(this);

  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor = 
      vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  
  // Cube
  vtkSmartPointer<vtkCubeSource> cubeSource = 
      vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
  vtkSmartPointer<vtkActor> cubeActor = 
      vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);
  
  // VTK Renderer
  vtkSmartPointer<vtkRenderer> leftRenderer = 
      vtkSmartPointer<vtkRenderer>::New();
  leftRenderer->AddActor(sphereActor);
  
  vtkSmartPointer<vtkRenderer> rightRenderer = 
      vtkSmartPointer<vtkRenderer>::New();

  // Add Actor to renderer
  rightRenderer->AddActor(cubeActor);

  // VTK/Qt wedded
  this->qvtkWidgetLeft->GetRenderWindow()->AddRenderer(leftRenderer);
  this->qvtkWidgetRight->GetRenderWindow()->AddRenderer(rightRenderer);

  // Set up action signals and slots
  connect(this->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
}

void SideBySideRenderWindowsQt::slotExit() 
{
  qApp->exit();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SideBySideRenderWindowsQt)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SideBySideRenderWindowsQt MACOSX_BUNDLE SideBySideRenderWindowsQt.cxx)
 
target_link_libraries(SideBySideRenderWindowsQt ${VTK_LIBRARIES})
```

**Download and Build SideBySideRenderWindowsQt**

Click [here to download SideBySideRenderWindowsQt](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SideBySideRenderWindowsQt.tar) and its *CMakeLists.txt* file.
Once the *tarball SideBySideRenderWindowsQt.tar* has been downloaded and extracted,
```
cd SideBySideRenderWindowsQt/build 
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
./SideBySideRenderWindowsQt
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

