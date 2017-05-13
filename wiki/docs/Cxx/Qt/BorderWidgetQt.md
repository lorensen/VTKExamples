[VTKExamples](/home/)/[Cxx](/Cxx)/Qt/BorderWidgetQt

**BorderWidgetQt.cxx**
```c++
#include "BorderWidgetQt.h"

#include <vtkBorderWidget.h>
#include <vtkCommand.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

class BorderCallback : public vtkCommand
{
  public:
    BorderCallback(){}

    static BorderCallback *New()
    {
      return new BorderCallback;
    }

  virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long, void*)
  {
//      vtkBorderWidget *borderWidget =
//          reinterpret_cast<vtkBorderWidget*>(caller);
  }

};

// Constructor
BorderWidgetQt::BorderWidgetQt()
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

  // Connect VTK with Qt
  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

  // Add a border widget to the right renderer
  this->BorderWidget = vtkSmartPointer<vtkBorderWidget>::New();
  this->BorderWidget->SetInteractor(this->qvtkWidget->GetInteractor());
  this->BorderWidget->On();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BorderWidgetQt)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BorderWidgetQt MACOSX_BUNDLE BorderWidgetQt.cxx)
 
target_link_libraries(BorderWidgetQt ${VTK_LIBRARIES})
```

**Download and Build BorderWidgetQt**

Click [here to download BorderWidgetQt](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BorderWidgetQt.tar) and its *CMakeLists.txt* file.
Once the *tarball BorderWidgetQt.tar* has been downloaded and extracted,
```
cd BorderWidgetQt/build 
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
./BorderWidgetQt
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

