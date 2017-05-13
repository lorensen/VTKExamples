[VTKExamples](Home)/[Cxx](Cxx)/Interaction/DoubleClick

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Interaction/TestDoubleClick.png" width="256" />

**DoubleClick.cxx**
```c++
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkPointPicker.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>

// Define interaction style
class MouseInteractorStyleDoubleClick : public vtkInteractorStyleTrackballCamera
{
  public:

    static MouseInteractorStyleDoubleClick* New();
    vtkTypeMacro(MouseInteractorStyleDoubleClick, vtkInteractorStyleTrackballCamera);

    MouseInteractorStyleDoubleClick() : NumberOfClicks(0), ResetPixelDistance(5)
    {
      this->PreviousPosition[0] = 0;
      this->PreviousPosition[1] = 0;
    }

    virtual void OnLeftButtonDown()
    {
      //std::cout << "Pressed left mouse button." << std::endl;
      this->NumberOfClicks++;
      //std::cout << "NumberOfClicks = " << this->NumberOfClicks << std::endl;
      int pickPosition[2];
      this->GetInteractor()->GetEventPosition(pickPosition);

      int xdist = pickPosition[0] - this->PreviousPosition[0];
      int ydist = pickPosition[1] - this->PreviousPosition[1];

      this->PreviousPosition[0] = pickPosition[0];
      this->PreviousPosition[1] = pickPosition[1];

      int moveDistance = (int)sqrt((double)(xdist*xdist + ydist*ydist));

      // Reset numClicks - If mouse moved further than resetPixelDistance
      if(moveDistance > this->ResetPixelDistance)
      {
        this->NumberOfClicks = 1;
      }


      if(this->NumberOfClicks == 2)
      {
        std::cout << "Double clicked." << std::endl;
        this->NumberOfClicks = 0;
      }
      // forward events
      vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

  private:
    unsigned int NumberOfClicks;
    int PreviousPosition[2];
    int ResetPixelDistance;
};
vtkStandardNewMacro(MouseInteractorStyleDoubleClick);

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(1,1,1); // Background color white
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow ( renderWindow );

  vtkSmartPointer<MouseInteractorStyleDoubleClick> style =
    vtkSmartPointer<MouseInteractorStyleDoubleClick>::New();
  renderWindowInteractor->SetInteractorStyle( style );

  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DoubleClick)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DoubleClick MACOSX_BUNDLE DoubleClick.cxx)
 
target_link_libraries(DoubleClick ${VTK_LIBRARIES})
```

**Download and Build DoubleClick**

Click [here to download DoubleClick](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DoubleClick.tar) and its *CMakeLists.txt* file.
Once the *tarball DoubleClick.tar* has been downloaded and extracted,
```
cd DoubleClick/build 
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
./DoubleClick
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

