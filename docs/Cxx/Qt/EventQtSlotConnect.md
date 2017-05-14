[VTKExamples](/index/)/[Cxx](/Cxx)/Qt/EventQtSlotConnect

### Description
<source lang="cpp">
#ifndef EventQtSlotConnect_H
#define EventQtSlotConnect_H

#include "ui_EventQtSlotConnect.h"

#include <QMainWindow>

#include <vtkSmartPointer.h>
class vtkEventQtSlotConnect;

class EventQtSlotConnect : public QMainWindow, private Ui::EventQtSlotConnect
{
  Q_OBJECT
public:

  EventQtSlotConnect();

public slots:

  void slot_clicked(vtkObject*, unsigned long, void*, void*);

private:

  vtkSmartPointer<vtkEventQtSlotConnect> Connections;
};

#endif

</source>

**EventQtSlotConnect.cxx**
```c++
#include "EventQtSlotConnect.h"

#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkEventQtSlotConnect.h>
#include <vtkInteractorStyleTrackballActor.h>

// Constructor
EventQtSlotConnect::EventQtSlotConnect()
{
  this->setupUi(this);

  this->Connections = vtkSmartPointer<vtkEventQtSlotConnect>::New();

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

  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

  this->Connections->Connect(this->qvtkWidget->GetRenderWindow()->GetInteractor(),
  vtkCommand::LeftButtonPressEvent,
  this,
  SLOT(slot_clicked(vtkObject*, unsigned long, void*, void*)));

};

void EventQtSlotConnect::slot_clicked(vtkObject*, unsigned long, void*, void*)
{
  std::cout << "Clicked." << std::endl;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(EventQtSlotConnect)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(EventQtSlotConnect MACOSX_BUNDLE EventQtSlotConnect.cxx)
 
target_link_libraries(EventQtSlotConnect ${VTK_LIBRARIES})
```

**Download and Build EventQtSlotConnect**

Click [here to download EventQtSlotConnect](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/EventQtSlotConnect.tar) and its *CMakeLists.txt* file.
Once the *tarball EventQtSlotConnect.tar* has been downloaded and extracted,
```
cd EventQtSlotConnect/build 
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
./EventQtSlotConnect
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

