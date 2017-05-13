[VTKExamples](Home)/[Cxx](Cxx)/Qt/RenderWindowUISingleInheritance

### Description
<source lang="cpp">
#ifndef RenderWindowUISingleInheritance_H
#define RenderWindowUISingleInheritance_H
 
#include <vtkSmartPointer.h>

#include <QMainWindow>
 
// Forward Qt class declarations
class Ui_RenderWindowUISingleInheritance;
 
class RenderWindowUISingleInheritance : public QMainWindow
{
  Q_OBJECT
public:
 
  // Constructor/Destructor
  RenderWindowUISingleInheritance(); 
  ~RenderWindowUISingleInheritance() {};
 
public slots:
 
  virtual void slotExit();

private:
 
  // Designer form
  Ui_RenderWindowUISingleInheritance *ui;
};
 
#endif
</source>

**RenderWindowUISingleInheritance.cxx**
```c++
#include "RenderWindowUISingleInheritance.h"

// This is included here because it is forward declared in
// RenderWindowUISingleInheritance.h
#include "ui_RenderWindowUISingleInheritance.h"

#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
 
// Constructor
RenderWindowUISingleInheritance::RenderWindowUISingleInheritance() 
{
  this->ui = new Ui_RenderWindowUISingleInheritance;
  this->ui->setupUi(this);
 
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
  this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
 
  // Set up action signals and slots
  connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
 
}
 
void RenderWindowUISingleInheritance::slotExit() 
{
  qApp->exit();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RenderWindowUISingleInheritance)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RenderWindowUISingleInheritance MACOSX_BUNDLE RenderWindowUISingleInheritance.cxx)
 
target_link_libraries(RenderWindowUISingleInheritance ${VTK_LIBRARIES})
```

**Download and Build RenderWindowUISingleInheritance**

Click [here to download RenderWindowUISingleInheritance](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RenderWindowUISingleInheritance.tar) and its *CMakeLists.txt* file.
Once the *tarball RenderWindowUISingleInheritance.tar* has been downloaded and extracted,
```
cd RenderWindowUISingleInheritance/build 
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
./RenderWindowUISingleInheritance
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

