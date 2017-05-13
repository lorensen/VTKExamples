[VTKExamples](/index/)/[Cxx](/Cxx)/Interaction/RubberBand2DObserver

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Interaction/TestRubberBand2DObserver.png?raw=true" width="256" />

**RubberBand2DObserver.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleRubberBand2D.h>
#include <vtkCallbackCommand.h>

void SelectionChangedCallbackFunction( vtkObject* caller, 
  long unsigned int eventId, void* clientData, void* callData );

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white
  renderWindow->Render();
  
  vtkSmartPointer<vtkCallbackCommand> selectionChangedCallback = 
    vtkSmartPointer<vtkCallbackCommand>::New();
  selectionChangedCallback->SetCallback ( SelectionChangedCallbackFunction );
  
  vtkSmartPointer<vtkInteractorStyleRubberBand2D> style = 
    vtkSmartPointer<vtkInteractorStyleRubberBand2D>::New();
  style->AddObserver ( vtkCommand::SelectionChangedEvent, selectionChangedCallback );
  renderWindowInteractor->SetInteractorStyle( style );
    
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}


void SelectionChangedCallbackFunction ( vtkObject* vtkNotUsed(caller), 
  long unsigned int vtkNotUsed(eventId), void* vtkNotUsed(clientData), void* callData )
{
  std::cout << "SelectionChanged callback" << std::endl;
  
  unsigned int* rect = reinterpret_cast<unsigned int*> ( callData );
  unsigned int pos1X = rect[0];
  unsigned int pos1Y = rect[1];
  unsigned int pos2X = rect[2];
  unsigned int pos2Y = rect[3];
 
  std::cout << "Start x: " << pos1X << " Start y: " << pos1Y 
            << " End x: " << pos2X << " End y: " << pos2Y << std::endl;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RubberBand2DObserver)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RubberBand2DObserver MACOSX_BUNDLE RubberBand2DObserver.cxx)
 
target_link_libraries(RubberBand2DObserver ${VTK_LIBRARIES})
```

**Download and Build RubberBand2DObserver**

Click [here to download RubberBand2DObserver](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RubberBand2DObserver.tar) and its *CMakeLists.txt* file.
Once the *tarball RubberBand2DObserver.tar* has been downloaded and extracted,
```
cd RubberBand2DObserver/build 
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
./RubberBand2DObserver
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

