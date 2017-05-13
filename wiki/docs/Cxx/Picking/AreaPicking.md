[VTKExamples](/home/)/[Cxx](/Cxx)/Picking/AreaPicking

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Picking/TestAreaPicking.png?raw=true" width="256" />

### Description
This example creates 3 points+vertices. Currently, the address of the picked prop is 0 (this is not correct). A red bounding box is drawn around every picked prop.

- For '''vtkInteractorStyleTrackballCamera''' - use 'p' to pick at the current mouse position

- For '''vtkInteractorStyleRubberBandPick''' - use 'r' and left-mouse to draw a selection box used to pick

**AreaPicking.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleRubberBandPick.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleTrackball.h>
#include <vtkAreaPicker.h>
#include <vtkCallbackCommand.h>
#include <vtkProp3DCollection.h>

void PickCallbackFunction ( vtkObject* caller, long unsigned int eventId, void* clientData, void* callData );

int main(int, char *[])
{
  // Create a set of points
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> vertices =
    vtkSmartPointer<vtkCellArray>::New();
  vtkIdType pid[1];
  pid[0] = points->InsertNextPoint ( 1.0, 0.0, 0.0 );
  vertices->InsertNextCell ( 1,pid );
  pid[0] = points->InsertNextPoint ( 0.0, 0.0, 0.0 );
  vertices->InsertNextCell ( 1,pid );
  pid[0] = points->InsertNextPoint ( 0.0, 1.0, 0.0 );
  vertices->InsertNextCell ( 1,pid );

  // Create a polydata
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints ( points );
  polydata->SetVerts ( vertices );

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInput(polydata);
#else
  mapper->SetInputData(polydata);
#endif
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkAreaPicker> areaPicker =
    vtkSmartPointer<vtkAreaPicker>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->SetPicker(areaPicker);

  renderer->AddActor(actor);
  renderer->SetBackground(0,0,0.2); // Background color dark blue

  renderWindow->Render();

  // For vtkInteractorStyleRubberBandPick - use 'r' and left-mouse to draw a selection box used to pick
  //vtkSmartPointer<vtkInteractorStyleRubberBandPick> style =
    //vtkSmartPointer<vtkInteractorStyleRubberBandPick>::New();

  // For vtkInteractorStyleTrackballCamera - use 'p' to pick at the current mouse position
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New(); //like paraview
  style->SetCurrentRenderer(renderer);
  renderWindowInteractor->SetInteractorStyle( style );

  vtkSmartPointer<vtkCallbackCommand> pickCallback =
    vtkSmartPointer<vtkCallbackCommand>::New();
  pickCallback->SetCallback ( PickCallbackFunction );

  areaPicker->AddObserver ( vtkCommand::EndPickEvent, pickCallback );

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}


void PickCallbackFunction(vtkObject* caller,
                          long unsigned int vtkNotUsed(eventId),
                          void* vtkNotUsed(clientData),
                          void* vtkNotUsed(callData))
{
  std::cout << "Pick." << std::endl;
  vtkAreaPicker* areaPicker = static_cast<vtkAreaPicker*>(caller);
  vtkProp3DCollection* props = areaPicker->GetProp3Ds();

  for(vtkIdType i = 0; i < props->GetNumberOfItems(); i++)
  {
    vtkProp3D* prop = props->GetNextProp3D();
    std::cout << "Picked prop: " << prop << std::endl;
  }
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(AreaPicking)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(AreaPicking MACOSX_BUNDLE AreaPicking.cxx)
 
target_link_libraries(AreaPicking ${VTK_LIBRARIES})
```

**Download and Build AreaPicking**

Click [here to download AreaPicking](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/AreaPicking.tar) and its *CMakeLists.txt* file.
Once the *tarball AreaPicking.tar* has been downloaded and extracted,
```
cd AreaPicking/build 
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
./AreaPicking
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

