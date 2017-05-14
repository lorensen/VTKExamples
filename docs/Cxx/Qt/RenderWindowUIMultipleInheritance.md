[VTKExamples](/index/)/[Cxx](/Cxx)/Qt/RenderWindowUIMultipleInheritance

### Description
<source lang="cpp">
#ifndef RenderWindowUIMultipleInheritance_H
#define RenderWindowUIMultipleInheritance_H

#include "ui_RenderWindowUIMultipleInheritance.h"

#include <QMainWindow>

class RenderWindowUIMultipleInheritance : public QMainWindow, private Ui::RenderWindowUIMultipleInheritance
{
  Q_OBJECT
public:

  RenderWindowUIMultipleInheritance();

public slots:

  virtual void slotExit();

};

#endif

</source>

**RenderWindowUIMultipleInheritance.cxx**
```c++
#include "RenderWindowUIMultipleInheritance.h"

#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>

// Constructor
RenderWindowUIMultipleInheritance::RenderWindowUIMultipleInheritance()
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

  // VTK Renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(sphereActor);

  // VTK/Qt wedded
  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

  // Set up action signals and slots
  connect(this->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));

};

void RenderWindowUIMultipleInheritance::slotExit()
{
  qApp->exit();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RenderWindowUIMultipleInheritance)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RenderWindowUIMultipleInheritance MACOSX_BUNDLE RenderWindowUIMultipleInheritance.cxx)
 
target_link_libraries(RenderWindowUIMultipleInheritance ${VTK_LIBRARIES})
```

**Download and Build RenderWindowUIMultipleInheritance**

Click [here to download RenderWindowUIMultipleInheritance](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RenderWindowUIMultipleInheritance.tar) and its *CMakeLists.txt* file.
Once the *tarball RenderWindowUIMultipleInheritance.tar* has been downloaded and extracted,
```
cd RenderWindowUIMultipleInheritance/build 
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
./RenderWindowUIMultipleInheritance
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

