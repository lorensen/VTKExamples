[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/SelectVisiblePoints

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestSelectVisiblePoints.png?raw=true" width="256" />

### Description
This example demonstrates how to determine which objects are visible.

**SelectVisiblePoints.cxx**
```c++
#include <vtkPolyData.h>
#include <vtkPointSource.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkSelectVisiblePoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
 
class MyInteractor : public vtkInteractorStyleTrackballCamera
{
  public:

    static MyInteractor* New();
    vtkTypeMacro(MyInteractor, vtkInteractorStyleTrackballCamera);
    
    virtual void OnLeftButtonDown() 
    {
      this->VisibleFilter->Update();
      std::cout << "There are currently: " << this->VisibleFilter->GetOutput()->GetNumberOfPoints() 
                << " visible." << std::endl;
      // Forward events
      vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
      
    }
    
    void SetVisibleFilter(vtkSmartPointer<vtkSelectVisiblePoints> vis) {this->VisibleFilter = vis;}
  private:
    vtkSmartPointer<vtkSelectVisiblePoints> VisibleFilter;
};

vtkStandardNewMacro(MyInteractor);

int main(int, char *[])
{ 
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(5.0, 0, 0);
  sphereSource->Update();
    
  vtkSmartPointer<vtkPointSource> pointSource = 
      vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetRadius(2.0);
  pointSource->SetNumberOfPoints(200);
  pointSource->Update();
    
  // Create an actor and mapper
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
 
  vtkSmartPointer<vtkActor> sphereActor = 
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
 
  vtkSmartPointer<vtkPolyDataMapper> pointsMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pointsMapper->SetInputConnection(pointSource->GetOutputPort());
 
  vtkSmartPointer<vtkActor> pointsActor = 
    vtkSmartPointer<vtkActor>::New();
  pointsActor->SetMapper(pointsMapper);
 
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  
  // Add the actors to the scene
  renderer->AddActor(sphereActor);
  renderer->AddActor(pointsActor);
  
  vtkSmartPointer<vtkSelectVisiblePoints> selectVisiblePoints = 
    vtkSmartPointer<vtkSelectVisiblePoints>::New();
  selectVisiblePoints->SetInputConnection(pointSource->GetOutputPort());
  selectVisiblePoints->SetRenderer(renderer);
  selectVisiblePoints->Update();
   
  vtkSmartPointer<MyInteractor> style = 
    vtkSmartPointer<MyInteractor>::New();
  renderWindowInteractor->SetInteractorStyle( style );
  style->SetVisibleFilter(selectVisiblePoints);
  
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SelectVisiblePoints)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SelectVisiblePoints MACOSX_BUNDLE SelectVisiblePoints.cxx)
 
target_link_libraries(SelectVisiblePoints ${VTK_LIBRARIES})
```

**Download and Build SelectVisiblePoints**

Click [here to download SelectVisiblePoints](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SelectVisiblePoints.tar) and its *CMakeLists.txt* file.
Once the *tarball SelectVisiblePoints.tar* has been downloaded and extracted,
```
cd SelectVisiblePoints/build 
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
./SelectVisiblePoints
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

